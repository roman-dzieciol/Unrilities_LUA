// ============================================================================
// Expression
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// unExpression
	// ============================================================================
	class unExpression
	{
	public:
		bool GetBoolValue(unFlow* Context) const;
		qword GetIntValue(unFlow* Context) const;
		wxString GetStringValue(unFlow* Context) const;
	};
}