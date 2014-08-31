// ============================================================================
// Config
// ============================================================================
#pragma once
#include "ParseUNR/Database.h"

namespace Unrilities {
	// ============================================================================
	// unConfig
	// ============================================================================
	class unConfig : public unDatabase
	{
	public:
		bool bVerboseLog;

	public:
		static unConfig& Global();
		unConfig();

	public:
		void Load(const wxString& filename);
	};


	// ============================================================================
	//	unConfig utilities
	// ============================================================================
	inline unConfig& GConfig(){
		return unConfig::Global();
	}
}