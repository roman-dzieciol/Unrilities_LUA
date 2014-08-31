// ============================================================================
//	Package
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Package.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/TypesFlow.h"
#include "ParseUNR/Lua.h"

namespace Unrilities {
	// ============================================================================
	//	unPackage
	// ============================================================================
	static int Lua_GetFileOffset(lua_State* state) 
	{
		unPackage* package = (unPackage*)lua_touserdata(state, lua_upvalueindex(1));
		qword result = package->Tell();

		// push results, return number of results
		lua_pushinteger(state, result);
		return 1;
	}

	// ============================================================================
	//	unPackage
	// ============================================================================
	unPackage::unPackage( unFile& file ) : File(file) , bDelayLoading(false)
	{

	}

	void unPackage::ReadFile()
	{      

		lua_pushlightuserdata(GLuaState(), this);
		lua_pushcclosure(GLuaState(), Lua_GetFileOffset, 1);
		//lua_pushcfunction(GLuaState(), Lua_GetFileOffset);
		lua_setglobal(GLuaState(), "GetOffset");


		// Create dummy root element
		RootElement.reset( new unElement(GName(wxT("File")), GNameNone(), GName(wxT("File")), GNameNone()) );

		// Create root primitive
		RootPrimitive.reset( GPrimitives().CreatePrimitive(GName(wxT("object")), RootElement.get(), NULL) );
		static_cast<unOBJECT*>(RootPrimitive.get())->SetElementType(RootElement->GetTypeID());

		// Read root primitive
		RootPrimitive->Read(*this);

		// Delay loading
		bDelayLoading = true;
		for( vector<unPrimitive*>::iterator it=DelayLoaded.begin(); it!=DelayLoaded.end(); ++it )
		{
			(*it)->Read(*this);
		}
	}

	bool unPackage::IsDelayLoading() const
	{
		return bDelayLoading;
	}

	void unPackage::RegisterDelayLoaded( unPrimitive* primitive )
	{
		DelayLoaded.push_back(primitive);
	}
}