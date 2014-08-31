// ============================================================================
//	Flag
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Flag.h"
#include "ParseUNR/Flag.h"

namespace Unrilities {
	// ============================================================================
	//	unFlagItem
	// ============================================================================
	unFlagItem::unFlagItem( qword Mask, const wxString& Name, const wxString& Description ) 
		: Mask(Mask)
		, Name(Name)
		, Description(Description)
	{
	}

	// ============================================================================
	//	unFlag
	// ============================================================================
	unFlag::unFlag( const wxString& Name ) 
		: Name(Name)
	{
	}

	unFlag::~unFlag()
	{
		for( vector<unFlagItem*>::iterator it=Items.begin(); it!=Items.end(); ++it )
			delete (*it);
	}

	void unFlag::AddItem( unFlagItem* Item )
	{
		Items.push_back(Item);
		FlagsByName[Item->Name] = Item;
		FlagsByMask.insert(make_pair(Item->Mask,Item));
	}

	unFlagItem* unFlag::GetFlagByName( const wxString& Name, bool bCanFail/*=false*/ )
	{
		unFlagNameMap::iterator it = FlagsByName.find(Name);
		if( it != FlagsByName.end() )
			return (*it).second;
		else if( bCanFail )
			return NULL;
		else
			throw unException( wxT("Unknown Flag requested: %s.%s"), (*this).Name.c_str(), Name.c_str() );
	}

	unFlagItem* unFlag::GetFlagByMask( qword Mask, bool bCanFail/*=false*/ )
	{
		unFlagMaskMap::iterator it = FlagsByMask.find(Mask);
		if( it != FlagsByMask.end() )
			return (*it).second;
		else if( bCanFail )
			return NULL;
		else
			throw unException( wxT("Unknown Flag requested: %s.%s"), (*this).Name.c_str(), Mask );
	}

	// ============================================================================
	//	unFlags
	// ============================================================================
	unFlags& unFlags::Global()
	{
		// Create on first use
		static unFlags p;
		return p;
	}

	unFlags::~unFlags()
	{
		WX_CLEAR_HASH_MAP(unFlagMap, Flags);
	}

	void unFlags::Load(unDatabase& database)
	{
		database.Execute(wxT("SELECT Type,Mask,Name,Description FROM Flags"), unFlags::OnLoadFlag, this);
	}

	int unFlags::OnLoadFlag( void* data, int /*argc*/, char** argv, char** /*azColName*/ )
	{
		// Get reference to caller
		unFlags* caller = static_cast<unFlags*>(data);

		// Get parent element
		wxString type = wxString(argv[0], wxConvUTF8);
		unFlag* flag = caller->GetFlag(type, true);
		if( !flag )
		{
			flag = new unFlag(type);
			caller->AddFlag(flag);
		}

		wxString binaryStr = wxString(argv[1], wxConvUTF8);
		qword mask = 0;
		if( !binaryStr.ToULongLong(&mask, 0) )
			throw unException( wxT("Flag mask is not a number! '%hs' '%hs' '%hs' '%hs'"), argv[0], argv[1], argv[2], argv[3] );

		// Add child to parent
		flag->AddItem(new unFlagItem
			( mask
			, wxString(argv[2], wxConvUTF8)
			, wxString(argv[3], wxConvUTF8)));

		return SQLITE_OK;
	}

	void unFlags::AddFlag( unFlag* p )
	{
		if( !p )
			throw unException( wxT("NULL Flag added!") );

		unFlagMap::iterator it = Flags.find(p->Name);
		if( it != Flags.end() )
		{
			delete p;
			throw unException( wxT("Flag with this name already exists: %s"), p->Name.c_str() );
		}

		Flags[p->Name] = p;
	}

	unFlag* unFlags::GetFlag( const wxString& name, bool bCanFail/*=false */ )
	{
		unFlagMap::iterator it = Flags.find(name);
		if( it != Flags.end() )
			return (*it).second;
		else if( bCanFail )
			return NULL;
		else
			throw unException( wxT("Unknown Flag requested: %s"), name.c_str() );
	}
}