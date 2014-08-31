// ============================================================================
//	Name
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Name.h"

namespace Unrilities {
	// ============================================================================
	//	unName
	// ============================================================================
	unName::unName(const wxString& Name) : Name(Name)
	{

	}

	// ============================================================================
	//	unNames
	// ============================================================================
	unNames::unNames() : NameNone(new unName(wxEmptyString))
	{
	}

	unNames::~unNames()
	{
		WX_CLEAR_HASH_MAP(unNamesMap, NamesMap);
	}

	unNames& unNames::Global()
	{
		// Create on first use
		static unNames p;
		return p;
	}

	const unName* unNames::Get( const wxString& Name )
	{
		if( Name.IsEmpty() )
			return NameNone;

		unNamesMap::const_iterator it = NamesMap.find(Name);
		if( it != NamesMap.end() )
		{
			return (*it).second;
		}

		unName* namePtr = new unName(Name);
		NamesMap[Name] = namePtr;
		return namePtr;
	}

}