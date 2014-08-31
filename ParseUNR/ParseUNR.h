// ============================================================================
//  ParseUNR.h
// ============================================================================
#pragma once
#include "ParseUNR/Types.h"
#include "ParseUNR/Exception.h"


// adds file name and line number to memory leak reports
#ifdef _DEBUG
    #ifdef __WXMSW__
	    #undef WXDEBUG_NEW
	    #define WXDEBUG_NEW new(__FILE__,__LINE__)
	    #include <crtdbg.h>

	    // this define works around a bug with inline declarations of new, see
	    // http://support.microsoft.com/support/kb/articles/Q140/8/58.asp
        #define new  new( _NORMAL_BLOCK, __FILE__, __LINE__)
    #endif
#endif


namespace Unrilities {
	// ============================================================================
	// Forward declarations in Unrilities ns
	// ============================================================================
	class unConfig;
	class unContainer;
	class unDatabase;
	class unDataType;
	class unElement;
	class unElements;
	class unExpression;
	class unExpressions;
	class unFile;
	class unFileGuard;
	class unFileMarker;
	class unFlag;
	class unFlagItem;
	class unFlags;
	class unFlow;
	class unOffsetGuard;
	class unPackage;
	class unPrimitive;
	class unPrimitives;
}
