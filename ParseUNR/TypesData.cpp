// ============================================================================
//	TypesData
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/TypesData.h"
#include "ParseUNR/Package.h"
#include "ParseUNR/TypesFlow.h"
#include "ParseUNR/Element.h"

namespace Unrilities {

	// ============================================================================
	//	unINDEX
	// ============================================================================
	void unINDEX::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
		byte B0;
		Value = 0;
		file.Read(&B0, sizeof(B0));
		if( B0 & 0x40 )
		{
			byte B1;
			file.Read(&B1, sizeof(B1));
			if( B1 & 0x80 )
			{
				byte B2;
				file.Read(&B2, sizeof(B2));
				if( B2 & 0x80 )
				{
					byte B3;
					file.Read(&B3, sizeof(B3));
					if( B3 & 0x80 )
					{
						byte B4;
						file.Read(&B4, sizeof(B4));
						Value = B4;
					}
					Value = (Value << 7) + (B3 & 0x7f);
				}
				Value = (Value << 7) + (B2 & 0x7f);
			}
			Value = (Value << 7) + (B1 & 0x7f);
		}
		Value = (Value << 6) + (B0 & 0x3f);

		if( B0 & 0x80 )
			Value = -Value;
	}

	bool unINDEX::GetBoolValue() const
	{
		return Value != 0;
	}

	Unrilities::qword unINDEX::GetIntValue() const
	{
		return static_cast<qword>(Value);
	}

	wxString unINDEX::GetStringValue() const
	{
		return wxString::Format(wxT("%d"), Value);
	}

	int unINDEX::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushinteger(luaState, GetIntValue());
		return 1;
	}

	// ============================================================================
	//	unPARRAY
	// ============================================================================
	void unPARRAY::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
		byte B0;
		Value = 0;
		file.Read(&B0, sizeof(B0));
		if( (B0 & 0x80) == 0 )
		{
			Value = static_cast<dword>(B0);
		}
		else if( (B0 & 0xC0) == 0x80 ) // <= 0x3FFF
		{
			byte B1;
			file.Read(&B1, sizeof(B1));
			Value = (static_cast<dword>(B0 & 0x7F) << 0x08) 
				  +  static_cast<dword>(B1);
		}
		else
		{
			byte B1;
			byte B2;
			byte B3;
			file.Read(&B1, sizeof(B1));
			file.Read(&B2, sizeof(B2));
			file.Read(&B3, sizeof(B3));
			Value = (static_cast<dword>(B0 & 0x3F) << 24) 
				  + (static_cast<dword>(B1) << 16) 
				  + (static_cast<dword>(B2) << 8) 
				  +  static_cast<dword>(B3);
		}
	}

	bool unPARRAY::GetBoolValue() const
	{
		return Value != 0;
	}

	Unrilities::qword unPARRAY::GetIntValue() const
	{
		return static_cast<qword>(Value);
	}

	wxString unPARRAY::GetStringValue() const
	{
		return wxString::Format(wxT("%d"), Value);
	}

	int unPARRAY::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushinteger(luaState, GetIntValue());
		return 1;
	}

	// ============================================================================
	//	unGUID
	// ============================================================================
	void unGUID::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
		file.Read(&A, sizeof(A));
		file.Read(&B, sizeof(B));
		file.Read(&C, sizeof(C));
		file.Read(&D, sizeof(D));
	}

	bool unGUID::GetBoolValue() const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	Unrilities::qword unGUID::GetIntValue() const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	wxString unGUID::GetStringValue() const
	{
		return wxString::Format(wxT("0x%.8x:0x%.8x:0x%.8x:0x%.8x"),A,B,C,D);
	}

	int unGUID::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushstring(luaState, GetStringValue().ToUTF8());
		return 1;
	}

	// ============================================================================
	// unASCIIZ
	// ============================================================================
	void unASCIIZ::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
		vector<char> chars;
		char c;
		do		{ file.Read(&c, sizeof(c)); chars.push_back(c); }
		while	( c != 0 );
		Value = chars.empty() ? wxT("") : wxString(&chars[0], wxConvUTF8);
	}

	bool unASCIIZ::GetBoolValue() const
	{
		return !Value.IsEmpty();
	}

	Unrilities::qword unASCIIZ::GetIntValue() const
	{
		qword IntValue = 0;
		if( !Value.ToULongLong(&IntValue, 0) )
			throw unException( wxT("Not a number! '%s'"), Value.c_str() );
		return IntValue;
	}

	wxString unASCIIZ::GetStringValue() const
	{
		return Value;
	}

	int unASCIIZ::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushstring(luaState, GetStringValue().ToUTF8());
		return 1;
	}

	// ============================================================================
	// unNUMBER
	// ============================================================================
	void unNUMBER::Initialize( unElement* Element, unPrimitive* Parent )
	{
		unPrimitive::Initialize(Element, Parent);
		Value = Element->GetInteger();
	}

	void unNUMBER::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
	}

	bool unNUMBER::GetBoolValue() const
	{
		return GetIntValue() != 0;
	}

	Unrilities::qword unNUMBER::GetIntValue() const
	{
		if( Parent->IsBitField() )
		{
			unBITFIELD* bitfield = static_cast<unBITFIELD*>(Parent);
			qword bitvalue = bitfield->Children.front()->GetIntValue();
			return static_cast<qword>(bitvalue & Value);
		}
		else
		{
			return static_cast<qword>(Value);
		}
	}

	wxString unNUMBER::GetStringValue() const
	{
		wxString s;
		s << GetIntValue();
		return s;
	}

	int unNUMBER::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushinteger(luaState, GetIntValue());
		return 1;
	}

}