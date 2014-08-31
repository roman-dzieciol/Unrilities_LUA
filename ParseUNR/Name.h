// ============================================================================
// Name
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// unName
	// ============================================================================
	class unName
	{
	private:
		const wxString Name;

	public:
		unName(const wxString& Name);

	public:
		const wxString wx_str() const { return Name; }
		const wxChar* c_str() const { return Name.c_str(); }
		bool IsEmpty() const { return Name.IsEmpty(); }
		const unName* GetPtr() const { return this; }
	};

	// ============================================================================
	// unNameID
	// ============================================================================
	typedef const unName* unNameID;

	// ============================================================================
	// unNames
	// ============================================================================
	class unNames
	{
	private:
		WX_DECLARE_STRING_HASH_MAP( unName*, unNamesMap );
		unNamesMap NamesMap;

	public:
		unNameID NameNone;
		 
	public:
		static unNames& Global();
		unNames();
		~unNames();

	public:
		unNameID Get(const wxString& Name);
	};


	// ============================================================================
	//	unNames utilities
	// ============================================================================
	inline unNames& GNames(){
		return unNames::Global();
	}
	inline unNameID GName(const wxString& Name){
		return unNames::Global().Get(Name);
	}
	inline unNameID GNameNone(){
		return unNames::Global().NameNone;
	}
}