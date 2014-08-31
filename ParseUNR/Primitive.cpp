// ============================================================================
//	Primitive
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Primitive.h"
#include "ParseUNR/TypesData.h"
#include "ParseUNR/Package.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/TypesFlow.h"
#include "ParseUNR/Expression.h"

namespace Unrilities {
	// ============================================================================
	//	unPrimitive
	// ============================================================================
	unPrimitive::unPrimitive() : Element(NULL), Parent(NULL), FindName(GNameNone()), bInline(FALSE), bIsArray(FALSE)
	{
	}

	void unPrimitive::Initialize( unElement* Element, unPrimitive* Parent )
	{
		this->Element = Element;
		this->Parent = Parent;
		this->FindName = Element->GetNameID();
	}

	unPrimitive::~unPrimitive()
	{
		for( unPrimitiveChildren::iterator it=Children.begin(); it!=Children.end(); ++it )
			delete (*it);
	}

	void unPrimitive::PushOffset(unPackage& /*File*/, wxFileOffset /*OffsetFrom*/, wxFileOffset /*OffsetTo*/)
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	unPrimitive* unPrimitive::FindChild( unNameID ElementName ) const
	{
		// Find among children
		unPrimitiveChildren::const_iterator it = Children.begin();
		unPrimitiveChildren::const_iterator itEnd = Children.end();
		for(; it!=itEnd; ++it )
		{
			unPrimitive* p = (*it);
			if( p->bInline )
			{
				unPrimitive* result = p->FindChild(ElementName);
				if( result )
					return result;
			}
			else if( ElementName == p->FindName )
			{
				return p;
			}
		}

		return NULL;
	}

	unPrimitive* unPrimitive::FindAncestorChild( unNameID ElementName ) const
	{
		// Find among siblings or any ancestors siblings
		const unPrimitive* ancestor = Parent;
		const unPrimitive* current = this;
		while( ancestor )
		{
			if( !ancestor->bIsArray )
			{
				// Find among children
				unPrimitiveChildren::const_iterator it = ancestor->Children.begin();
				unPrimitiveChildren::const_iterator itEnd = ancestor->Children.end();
				for(; it!=itEnd; ++it )
				{
					unPrimitive* p = (*it);
					if( p->bInline && p != current )
					{
						unPrimitive* result = p->FindChild(ElementName);
						if( result )
							return result;
					}
					else if( ElementName == p->FindName )
					{
						return p;
					}
				}
			}

			current = ancestor;
			ancestor = ancestor->Parent;
		}

		return NULL;

		/*// Find among siblings or any ancestors siblings
		const unPrimitive* ancestor = Parent;
		while( ancestor )
		{
			unPrimitive* child = ancestor->FindChild(ElementName);
			if( child )
				return child;

			ancestor = ancestor->Parent;
		}

		return NULL;*/
	}

	unPrimitive* unPrimitive::GetChildByIndex( size_t index ) const
	{
		if( index >= 0 && index < Children.size() )
		{
			unPrimitiveChildren::const_iterator it = Children.begin();
			advance(it, index);
			return *it;
		}
		else
			throw unException( wxT("Invalid child primitive index: %s[%d]"), FindName->c_str(), (int)index );
	}

	bool unPrimitive::IsFlow() const
	{
		return false;
	}

	bool unPrimitive::IsArray() const
	{
		return false;
	}

	bool unPrimitive::IsBitField() const
	{
		return false;
	}

	wxString unPrimitive::Print() const
	{
		return GetStringValue();
	}

	void unPrimitive::Log(const wxString& prefix) const
	{
		wxLogMessage(wxT("%s%s\t%s = %s")
			, prefix.c_str()
			, Element ? Element->GetType().c_str() : wxT("")
			, Element ? Element->GetName().c_str() : wxT("")
			, Print().c_str()
			);
	}

	unPrimitive* unPrimitive::GetRoot()
	{
		if( Parent )
			return Parent->GetRoot();
		return this;
	}

	// ============================================================================
	// unPrimitives
	// ============================================================================
	unPrimitives& unPrimitives::Global()
	{
		// Create on first use
		static unPrimitives p;
		return p;
	}

	unPrimitives::~unPrimitives()
	{
	}

	unPrimitives::unPrimitives()
	{
		// Primitive Types
		AddPrimitive( GName(wxT("BYTE")), CreatePrimitive< unPOD<byte> > );
		AddPrimitive( GName(wxT("WORD")), CreatePrimitive< unPOD<word> > );
		AddPrimitive( GName(wxT("DWORD")), CreatePrimitive< unPOD<dword> > );
		AddPrimitive( GName(wxT("QWORD")), CreatePrimitive< unPOD<qword> > );
		AddPrimitive( GName(wxT("INT32")), CreatePrimitive< unPOD<int32> > );
		AddPrimitive( GName(wxT("FLOAT")), CreatePrimitive< unPOD<float> > );
		AddPrimitive( GName(wxT("DOUBLE")), CreatePrimitive< unPOD<double> > );
		AddPrimitive( GName(wxT("INDEX")), CreatePrimitive< unINDEX > );
		AddPrimitive( GName(wxT("PARRAY")), CreatePrimitive< unPARRAY > );
		AddPrimitive( GName(wxT("GUID")), CreatePrimitive< unGUID > );
		AddPrimitive( GName(wxT("ASCIIZ")), CreatePrimitive< unASCIIZ > );
		AddPrimitive( GName(wxT("BASCII")), CreatePrimitive< unTASCII< unPOD<byte> > > );
		AddPrimitive( GName(wxT("WASCII")), CreatePrimitive< unTASCII< unPOD<word> > > );
		AddPrimitive( GName(wxT("DASCII")), CreatePrimitive< unTASCII< unPOD<dword> > > );
		AddPrimitive( GName(wxT("IASCII")), CreatePrimitive< unTASCII< unINDEX > > );

		// Flow Types
		AddPrimitive( GName(wxT("object")), CreatePrimitive< unOBJECT > );
		AddPrimitive( GName(wxT("array")), CreatePrimitive< unARRAY > );
		AddPrimitive( GName(wxT("assert")), CreatePrimitive< unASSERT > );
		//AddPrimitive( GName(wxT("extern")), CreatePrimitive< unEXTERN > );
		//AddPrimitive( GName(wxT("objvar")), CreatePrimitive< unEXTERN > );
		AddPrimitive( GName(wxT("include")), CreatePrimitive< unINCLUDE > );
		AddPrimitive( GName(wxT("offset")), CreatePrimitive< unOFFSET > );
		AddPrimitive( GName(wxT("bitfield")), CreatePrimitive< unBITFIELD > );
		AddPrimitive( GName(wxT("loop")), CreatePrimitive< unLOOP > );
		AddPrimitive( GName(wxT("break")), CreatePrimitive< unBREAK > );
		//AddPrimitive( GName(wxT("bpoint")), CreatePrimitive< unBREAKPOINT > );
		//AddPrimitive( GName(wxT("PSIZE")), CreatePrimitive< unPSIZE > );
		AddPrimitive( GName(wxT("switch")), CreatePrimitive< unSWITCH > );
		AddPrimitive( GName(wxT("delay")), CreatePrimitive< unDELAY > );
		AddPrimitive( GName(wxT("data")), CreatePrimitive< unDATA > );
		AddPrimitive( GName(wxT("log")), CreatePrimitive< unLOG > );
		AddPrimitive( GName(wxT("skip")), CreatePrimitive< unSKIP > );
	}

	void unPrimitives::AddPrimitive( unNameID Name, unPrimitiveCreator primitive )
	{
		Primitives[Name] = primitive;
	}

	unPrimitive* unPrimitives::CreatePrimitive( unNameID Name, unElement* Element, unPrimitive* Parent, bool bCanFail/*=false */ ) const
	{
		// Try to interpret as number
		if( Element && Element->IsInteger() )
		{
			auto_ptr<unPrimitive> primitive( new unNUMBER );
			primitive->Initialize(Element,Parent);
			return primitive.release();
		}

		unPrimitiveMap::const_iterator it = Primitives.find(Name->GetPtr());
		if( it != Primitives.end() )
		{
			auto_ptr<unPrimitive> primitive( ((*it).second)() );
			primitive->Initialize(Element,Parent);
			return primitive.release();
		}
		else if( bCanFail )
			return NULL;
		else
			throw unException( wxT("Unknown primitive requested: %s"), Name->c_str() );
	}

	template<class T> unPrimitive* unPrimitives::CreatePrimitive()
	{
		return new T;
	}

	bool unPrimitives::Exists( unNameID Name ) const
	{
		// Try to interpret as bitmask
		qword IntValue;
		if( Name->wx_str().ToULongLong(&IntValue, 0) )
			return true;

		unPrimitiveMap::const_iterator it = Primitives.find(Name->GetPtr());
		if( it != Primitives.end() )
			return true;

		return false;
	}

	// ============================================================================
	//	unPrimitiveReadPrinter
	// ============================================================================
	unPrimitiveReadPrinter::unPrimitiveReadPrinter( unPrimitive* Primitive, unPackage& File )
		: Primitive(Primitive), File(File), Begin(File.Tell())
	{
	}

	unPrimitiveReadPrinter::~unPrimitiveReadPrinter()
	{
		Primitive->Log( wxString::Format(wxT("0x%.8llx "), Begin) );
	}
}