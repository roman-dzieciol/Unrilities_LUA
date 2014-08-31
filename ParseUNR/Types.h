// ============================================================================
// Types
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// POD
	// ============================================================================
	typedef unsigned __int8		byte;
	typedef unsigned __int16	word;
	typedef unsigned __int32	dword;
	typedef unsigned __int64	qword;

	typedef signed __int8		int8;
	typedef signed __int16		int16;
	typedef signed __int32		int32;
	typedef signed __int64		int64;

	typedef unsigned int		uint;
	typedef const char*			cstr;

}

#define  UP_AT(num)	[num]