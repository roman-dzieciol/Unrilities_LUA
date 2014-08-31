// ============================================================================
//	Expression
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Expression.h"
#include "ParseUNR/Primitive.h"
#include "ParseUNR/Element.h"

namespace Unrilities {
	// ============================================================================
	//	unExpression
	// ============================================================================

	bool unExpression::GetBoolValue( unFlow* /*Context*/ ) const
	{	
		UNR_THROW_NOT_IMPLEMENTED;
	}

	Unrilities::qword unExpression::GetIntValue( unFlow* /*Context*/ ) const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	wxString unExpression::GetStringValue( unFlow* /*Context*/ ) const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}
}