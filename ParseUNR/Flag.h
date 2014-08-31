// ============================================================================
// Flag
// ============================================================================
#pragma once
#include "ParseUNR/Database.h"

namespace Unrilities {
	// ============================================================================
	// unFlagItem
	// ============================================================================
	class unFlagItem
	{
	public:
		qword Mask;
		wxString Name;
		wxString Description;

	public:
		explicit unFlagItem(qword Mask, const wxString& Name, const wxString& Description);
	};

	// ============================================================================
	// unFlag
	// ============================================================================
	class unFlag
	{
	private:
		WX_DECLARE_STRING_HASH_MAP( unFlagItem*, unFlagNameMap );        
		typedef tr1::unordered_multimap<qword, unFlagItem*> unFlagMaskMap;
		unFlagNameMap FlagsByName;
		unFlagMaskMap FlagsByMask;
		vector<unFlagItem*> Items;

	public:
		wxString Name;

	public:
		explicit unFlag(const wxString& Name);
		~unFlag();

	public:
		void AddItem(unFlagItem* Item);
		unFlagItem* GetFlagByName(const wxString& Name, bool bCanFail=false);
		unFlagItem* GetFlagByMask(qword Mask, bool bCanFail=false);
	};

	// ============================================================================
	// unFlags
	// ============================================================================
	class unFlags
	{
	private:
		WX_DECLARE_STRING_HASH_MAP( unFlag*, unFlagMap );
		unFlagMap Flags;

	public:
		static unFlags& Global();
		~unFlags();

	public:
		void Load(unDatabase& database);

	private:
		static int OnLoadFlag(void* data, int argc, char** argv, char** azColName);

	private:
		void AddFlag( unFlag* p );

	public:
		unFlag* GetFlag( const wxString& name, bool bCanFail=false );
	};


	// ============================================================================
	//	unFlags utilities
	// ============================================================================
	inline unFlags& GFlags(){
		return unFlags::Global();
	}
}