// ============================================================================
//	Config
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Config.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/Flag.h"
#include "ParseUNR/Lua.h"

namespace Unrilities {
	// ============================================================================
	//	unConfig
	// ============================================================================
	unConfig& unConfig::Global()
	{
		// Create on first use
		static unConfig p;
		return p;
	}

	void unConfig::Load( const wxString& filename )
	{
		unDatabase::Load(filename);
		GLua().Load(*this);
		GFlags().Load(*this);
		GElements().Load(*this);
	}

	unConfig::unConfig() : bVerboseLog(true)
	{

	}
}