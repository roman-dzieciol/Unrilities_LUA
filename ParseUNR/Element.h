// ============================================================================
// Element
// ============================================================================
#pragma once
#include "ParseUNR/Name.h"

namespace Unrilities {
	// ============================================================================
	// unElement
	// ============================================================================
	class unElement
	{
	private:
		unNameID Type;
		unNameID Name;
		unNameID FriendlyName;
		unNameID PrintFormat;
		int Expression;
		bool bIsInteger;
		qword Value;
		vector<unElement*> Elements;

	public:
		explicit unElement(unNameID Type, unNameID Name, unNameID FriendlyName, unNameID PrintFormat);
		~unElement();

	public:
		void AddChild(unElement* Child);
		wxString GetSafeName() const;
		wxString GetType() const { return Type->wx_str(); }
		wxString GetName() const { return Name->wx_str(); }
		wxString GetFriendlyName() const { return FriendlyName->wx_str(); }
		wxString GetPrintFormat() const { return PrintFormat->wx_str(); }
		unNameID GetTypeID() const { return Type; }
		unNameID GetNameID() const { return Name; }
		unNameID GetFriendlyNameID() const { return FriendlyName; }
		unNameID GetPrintFormatID() const { return PrintFormat; }
		int GetExpression() const { return Expression; }
		vector<unElement*>& GetElements() { return Elements; }
		int CompileChunk();
		bool IsInteger() const { return bIsInteger; }
		qword GetInteger() const { return Value; }
	};


	// ============================================================================
	// unElements
	// ============================================================================
	class unElements
	{
	private:
		//WX_DECLARE_STRING_HASH_MAP( unElement*, unElementMap );
		WX_DECLARE_HASH_MAP( unName*, unElement*, wxPointerHash, wxPointerEqual, unElementMap );
		unElementMap ElementsByType; // holds base elements

	public:
		static unElements& Global();
		~unElements();

	public:
		void Load(unDatabase& database);

	private:
		static int OnLoadElement(void* elementsPtr, int argc, char** argv, char** azColName);

	private:
		void AddElement( unElement* p );

	public:
		unElement* GetElementByType( unNameID name, bool bCanFail=false );
		unElement* GetElementNumbered( const wxString& name, qword number, bool bCanFail=false );
	};


	// ============================================================================
	//	unElements utilities
	// ============================================================================
	inline unElements& GElements()
	{
		return unElements::Global();
	}
}