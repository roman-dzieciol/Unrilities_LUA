// ============================================================================
//	Element
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/Database.h"
#include "ParseUNR/File.h"
#include "ParseUNR/Primitive.h"
#include "ParseUNR/TypesFlow.h"
#include "ParseUNR/Lua.h"

namespace Unrilities {
	// ============================================================================
	//	unElement
	// ============================================================================
	unElement::unElement( unNameID Type, unNameID Name, unNameID FriendlyName, unNameID PrintFormat ) 
		: Type(Type)
		, Name(Name)
		, FriendlyName(FriendlyName)
		, PrintFormat(PrintFormat)
		, Expression(LUA_NOREF)
		, bIsInteger(false)
		, Value(0)
	{
		// Try to interpret as number
		if( Type->wx_str().ToULongLong(&Value, 0) )
			bIsInteger = true;

		if( Type != GNameNone() && Type->wx_str().Lower().IsSameAs(Type->wx_str()) )
			Expression = CompileChunk();
	}

	unElement::~unElement()
	{
		for( vector<unElement*>::iterator it=Elements.begin(); it!=Elements.end(); ++it )
			delete (*it);
	}

	void unElement::AddChild( unElement* Child )
	{
		//wxLogMessage(wxT("%s.%s"), GetSafeName().c_str(), Child->GetSafeName().c_str());
		Elements.push_back(Child);
	}

	wxString unElement::GetSafeName() const
	{
		if( !Name->IsEmpty() )
			return Name->wx_str();
		else if( !Type->IsEmpty() )
			return Type->wx_str();
		else
			return wxT("Null Element");
	}

	int unElement::CompileChunk()
	{
		// Skip if no script
		if( Name == GNameNone() )
			return LUA_NOREF;

		// Setup expression
		const wxString luaText = wxString(wxT("return ")).Append(Name->wx_str());

		// Compile expression
		if( luaL_loadstring(GLuaState(), luaText.ToUTF8()) != 0 )
			throw unException( wxT("Expression did not compile: %s"), GLua().PopString(-1).c_str() );

		// Pop compiled result off the stack and store in registry
		int expression = luaL_ref(GLuaState(), LUA_REGISTRYINDEX);
		if( expression == LUA_REFNIL )
			throw unException( wxT("Expression compiled to nil result: %s"), luaText.c_str() );

		return expression;
	}


	// ============================================================================
	//	unElements
	// ============================================================================
	unElements& unElements::Global()
	{
		// Create on first use
		static unElements p;
		return p;
	}

	unElements::~unElements()
	{
		WX_CLEAR_HASH_MAP(unElementMap, ElementsByType);
	}

	void unElements::Load(unDatabase& database)
	{
		database.Execute(wxT("SELECT Parent,Type,Name,FriendlyName,PrintFormat FROM Elements"), unElements::OnLoadElement, this);
	}

	int unElements::OnLoadElement( void* elementsPtr, int /*argc*/, char** argv, char** /*azColName*/ )
	{
		// Get reference to caller
		unElements* caller = static_cast<unElements*>(elementsPtr);

		// Get parent element
		unNameID parentName = GName(wxString(argv[0], wxConvUTF8));
		unElement* parent = caller->GetElementByType(parentName, true);
		if( !parent )
		{
			parent = new unElement(parentName, GNameNone(), parentName, GNameNone());
			caller->AddElement(parent);
			//wxLogMessage(wxT("%s"), parent->Type.c_str());
		}

		// Add child to parent
		parent->AddChild(new unElement
			( GName(wxString(argv[1], wxConvUTF8))
			, GName(wxString(argv[2], wxConvUTF8))
			, GName(wxString(argv[3], wxConvUTF8))
			, GName(wxString(argv[4], wxConvUTF8))));

		return SQLITE_OK;
	}

	void unElements::AddElement( unElement* p )
	{
		if( !p )
			throw unException( wxT("NULL Element added!") );

		unElementMap::iterator it = ElementsByType.find(p->GetTypeID());
		if( it != ElementsByType.end() )
		{
			delete p;
			throw unException( wxT("Element with this type already exists: %s"), p->GetType().c_str() );
		}

		ElementsByType[p->GetTypeID()] = p;
	}

	unElement* unElements::GetElementByType( unNameID name, bool bCanFail/*=false */ )
	{
		unElementMap::iterator it = ElementsByType.find(name);
		if( it != ElementsByType.end() )
			return (*it).second;
		else if( bCanFail )
			return NULL;
		else
			throw unException( wxT("Unknown element requested, type: %s"), name->c_str() );
	}

	unElement* unElements::GetElementNumbered( const wxString& name, qword number, bool bCanFail/*=false */ )
	{
		unElementMap::iterator it = ElementsByType.find(GName(wxString::Format(wxT("%s.0x%.2llx"),name.c_str(), number)));
		if( it == ElementsByType.end() )
		{
			it = ElementsByType.find(GName(wxString::Format(wxT("%s.0x%.4llx"),name.c_str(), number)));
			if( it == ElementsByType.end() )
			{
				it = ElementsByType.find(GName(wxString::Format(wxT("%s.0x%.8llx"),name.c_str(), number)));
				if( it == ElementsByType.end() )
				{
					it = ElementsByType.find(GName(wxString::Format(wxT("%s.0x%.16llx"),name.c_str(), number)));
				}
			}
		}

		if( it != ElementsByType.end() )
			return (*it).second;
		else if( bCanFail )
			return NULL;
		else
			throw unException( wxT("Unknown element requested: %s"), name.c_str() );
		
	}
}