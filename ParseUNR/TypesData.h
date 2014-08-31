// ============================================================================
// TypesData
// ============================================================================
#pragma once
#include "ParseUNR/Primitive.h"

namespace Unrilities {
	// ============================================================================
	// unPOD
	// ============================================================================
	template<class T>
	class unPOD : public unPrimitive
	{
	public:
		T Value;

	public:
		virtual void Read(unPackage& file);

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};

	template<class T>
	void unPOD<T>::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
		file.Read(&Value, sizeof(Value));
	}

	template<class T>
	bool unPOD<T>::GetBoolValue() const
	{
		return Value != 0;
	}

	template<class T>
	qword unPOD<T>::GetIntValue() const
	{
		return static_cast<qword>(Value);
	}

	template<class T>
	wxString unPOD<T>::GetStringValue() const
	{
		wxString s;
		s << Value;
		return s;
	}

	template<class T>
	int unPOD<T>::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushinteger(luaState, GetIntValue());
		return 1;
	}


	// ============================================================================
	// unINDEX
	// ============================================================================
	class unINDEX : public unPrimitive
	{
	public:
		int32 Value;

	public:
		virtual void Read(unPackage& file);

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};


	// ============================================================================
	// unPARRAY
	// ============================================================================
	class unPARRAY : public unPrimitive
	{
	public:
		dword Value;

	public:
		virtual void Read(unPackage& file);

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};


	// ============================================================================
	// unGUID
	// ============================================================================
	class unGUID : public unPrimitive
	{
	public:
		dword A,B,C,D;

	public:
		virtual void Read(unPackage& file);

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};


	// ============================================================================
	// unASCIIZ
	// ============================================================================
	class unASCIIZ : public unPrimitive
	{
	public:
		wxString Value;

	public:
		virtual void Read(unPackage& file);

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};


	// ============================================================================
	// unTASCII
	// ============================================================================
	template<class T>
	class unTASCII : public T
	{
	public:
		wxString Text;
		bool bSkipLog;

	public:
		virtual void Read(unPackage& file);
		virtual void Log(const wxString& prefix) const;

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};

	// ============================================================================
	// unTASCII implementation
	// ============================================================================
	template<class T>
	void unTASCII<T>::Log( const wxString& prefix ) const
	{
		if( !bSkipLog )
		{
			wxLogMessage(wxT("%s%s\t%s = %s")
				, prefix.c_str()
				, Element ? Element->GetType().c_str() : wxT("")
				, Element ? Element->GetName().c_str() : wxT("")
				, Print().c_str()
				);
		}
		else
		{
			/*wxLogMessage(wxT("%s%s\t%s = %d (string length)")
			, prefix.c_str()
			, Element ? Element->GetType.c_str() : wxT("")
			, Element ? Element->GetName().c_str() : wxT("")
			, static_cast<dword>(Value)
			);*/
		}
	}

	template<class T>
	void unTASCII<T>::Read( unPackage& file )
	{
		UNR_PRIMITIVE_READ_DEBUG;
		bSkipLog = true;
		T::Read(file);
		bSkipLog = false;
		if( Value > 0 && Value < file.Length() )
		{
			vector<char> chars;
			chars.reserve(Value);
			chars.resize(Value);
			file.Read( &chars[0], Value );
			Text = wxString(&chars[0], wxConvUTF8);
		}
		else
			throw unException(wxT("Invalid string length at 0x%.8x"), static_cast<dword>(file.Tell()));
	}

	template<class T>
	bool unTASCII<T>::GetBoolValue() const
	{
		return !Text.IsEmpty();
	}

	template<class T>
	qword unTASCII<T>::GetIntValue() const
	{
		qword IntValue = 0;
		if( !Text.ToULongLong(&IntValue, 0) )
			throw unException( wxT("Not a number! '%s'"), Text.c_str() );
		return IntValue;
	}

	template<class T>
	wxString unTASCII<T>::GetStringValue() const
	{
		return Text;
	}

	template<class T>
	int Unrilities::unTASCII<T>::PushLuaValue( lua_State* luaState ) const
	{
		lua_pushstring(luaState, GetStringValue().ToUTF8());
		return 1;
	}

	// ============================================================================
	// unNUMBER
	// ============================================================================
	class unNUMBER : public unPrimitive
	{
	public:
		qword Value;

	public:
		virtual void Initialize(unElement* Element, unPrimitive* Parent);
		virtual void Read(unPackage& file);

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};
}