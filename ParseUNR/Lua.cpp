// ============================================================================
//	Lua
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Lua.h"
#include "ParseUNR/Flow.h"
#include "ParseUNR/Flag.h"
#include "ParseUNR/Element.h"



namespace Unrilities {
	// ============================================================================
	//	Custom Lua C functions
	// ============================================================================
	void stackDump (lua_State *L) {
		int i;
		int top = lua_gettop(L);
		for (i = 1; i <= top; i++) {  /* repeat for each level */
			int t = lua_type(L, i);


			switch (t) {

		  case LUA_TSTRING:  /* strings */
			  printf("`%s'", lua_tostring(L, i));
			  break;

		  case LUA_TBOOLEAN:  /* booleans */
			  printf(lua_toboolean(L, i) ? "true" : "false");
			  break;

		  case LUA_TNUMBER:  /* numbers */
			  printf("%g", lua_tonumber(L, i));
			  break;

		  case LUA_TINT:  /* numbers */
			  printf("%lld", lua_tointeger(L, i));
			  break;

		  default:  /* other values */
			  printf("%s", lua_typename(L, t));
			  break;

			}
			printf("  ");  /* put a separator */
		}
		printf("\n");  /* end the listing */
	}

	//static int Lua_GetPrimitiveIntValue(lua_State* state) 
	//{
	//	// get argument
	//	wxString pname = wxString::FromUTF8(lua_tostring(state, 1));  

	//	// return int value of specified primitive
	//	unFlow* context = GLua().GetContext();
	//	qword result = context->FindAncestorChild(pname)->GetIntValue();

	//	// push results, return number of results
	//	lua_pushnumber(state, result);
	//	return 1;
	//}

	//static int Lua_GetPrimitiveBoolValue(lua_State* state) 
	//{
	//	// get argument
	//	wxString pname = wxString::FromUTF8(lua_tostring(state, 1));  

	//	// return int value of specified primitive
	//	unFlow* context = GLua().GetContext();
	//	BOOL result = context->FindAncestorChild(pname)->GetBoolValue() ? TRUE : FALSE;

	//	// push results, return number of results
	//	lua_pushboolean(state, result);
	//	return 1;
	//}

	static int Lua_GetFlagInteger(lua_State* state) 
	{
		// get argument
		wxString flagType = wxString::FromUTF8(lua_tostring(state, 1));  
		wxString flagName = wxString::FromUTF8(lua_tostring(state, 2));  

		qword result = GFlags().GetFlag(flagType)->GetFlagByName(flagName)->Mask;

		// push results, return number of results
		lua_pushinteger(state, result);
		return 1;
	}

	static int Lua_GetFlagMask(lua_State* state) 
	{
		// get argument
		qword flagValue = lua_tointeger(state, 1);  
		qword flagMask = lua_tointeger(state, 2);  

		qword result = flagValue & flagMask;

		// push results, return number of results
		lua_pushinteger(state, result);
		return 1;
	}

	static int Lua_GetFlagName(lua_State* state) 
	{
		// get argument
		qword flagMask = lua_tointeger(state, -1);  
		wxString flagType = wxString::FromUTF8(lua_tostring(state, -2));  
		wxString result = GFlags().GetFlag(flagType)->GetFlagByMask(flagMask)->Name;

		// push results, return number of result
		lua_pushstring(state, result.ToUTF8());
		return 1;
	}

	static int Lua_TypeExists(lua_State* state) 
	{
		// get argument
		wxString typeName = wxString::FromUTF8(lua_tostring(state, -1));  

		BOOL bResult = GElements().GetElementByType(GName(typeName), true) != NULL;

		// push results, return number of result
		lua_pushboolean(state, bResult);
		return 1;
	}

	static int Lua_GlobalIndex(lua_State* state) 
	{
		//wxLogMessage(wxT("global:"));
		//stackDump(state);

		wxString undefinedVar = wxString::FromUTF8(lua_tostring(state, -1));  

		// return value of specified primitive
		const unPrimitive* context = GLua().GetContext();

		// Try to find a primitive first
		unPrimitive* primitive = context->FindAncestorChild(GName(undefinedVar));
		if( primitive )
			return primitive->PushLuaValue(state);

		// error
		throw unException(wxT("undefined lua global: %s"), undefinedVar.c_str());
	}

	static int Lua_ContextIndex(lua_State* state) 
	{
		//wxLogMessage(wxT("context:"));

		if( lua_isnumber(state,-1) )
		{
			//stackDump(state);
			int intParam = lua_tointeger(state, -1);  

			unLua::ContextData* ud = (unLua::ContextData*)luaL_checkudata(state, -2, "ContextData");
			if( ud == NULL || ud->Context == NULL )
				throw unException(wxT("invalid lua context: [%d]"), intParam);

			unPrimitive* primitive = ud->Context->GetChildByIndex(intParam);
			if( primitive )
				return primitive->PushLuaValue(state);

			// error
			throw unException(wxT("undefined lua context: [%d]"), intParam);
		}
		else if( lua_isstring(state,-1) )
		{
			//stackDump(state);
			wxString undefinedVar = wxString::FromUTF8(lua_tostring(state, -1));  

			unLua::ContextData* ud = (unLua::ContextData*)luaL_checkudata(state, -2, "ContextData");
			if( ud == NULL || ud->Context == NULL )
				throw unException(wxT("invalid lua context: %s"), undefinedVar.c_str());

			unPrimitive* primitive = ud->Context->FindChild(GName(undefinedVar));
			if( primitive )
				return primitive->PushLuaValue(state);

			// error
			throw unException(wxT("undefined lua context: %s"), undefinedVar.c_str());
		}
		else
		{
			// error
			throw unException(wxT("unknown lua context type: %d"), lua_type(state, -1));
		}

	}

	int unLua::PushLuaContext( lua_State* state, const unPrimitive* context )
	{
		//wxLogMessage(wxT("PushLuaContext"));

		//stackDump(LuaState);
		size_t nbytes = sizeof(unLua::ContextData);
		unLua::ContextData* data = (unLua::ContextData*)lua_newuserdata(state, nbytes);
		data->Context = context;

		//stackDump(state);
		luaL_newmetatable(state, "ContextData");
		//stackDump(state);      
		lua_pushstring(state, "__index");
		lua_pushcfunction(state, Lua_ContextIndex);
		//stackDump(state);      
		lua_settable(state, -3); // metatable.__index = Lua_ContextIndex
		//stackDump(state);      
		lua_setmetatable(state, -2);
		//stackDump(state);
		return 1;
	}

	// ============================================================================
	//	unLua
	// ============================================================================
	unLua& unLua::Global()
	{
		// Create on first use
		static unLua p;
		return p;
	}

	lua_State* unLua::GlobalState()
	{
		return Global().LuaState;
	}

	unLua::unLua() : LuaState(NULL), Context(NULL)
	{
	
	}

	unLua::~unLua()
	{
		if( LuaState )   
			lua_close( LuaState );
	}


	void unLua::Load( unDatabase& database )
	{
		Init();
		database.Execute(wxT("SELECT Snippet FROM Snippets"), unLua::OnLoad, this);
	}

	int unLua::OnLoad( void* /*data*/, int /*argc*/, char** argv, char** /*azColName*/ )
	{
		// Get reference to caller
		//unLua* caller = static_cast<unLua*>(data);

		// Get snippet
		wxString snippet = wxString(argv[0], wxConvUTF8);

		// Compile expression
		if( luaL_loadstring(GLuaState(), snippet.ToUTF8()) != 0 )
			throw unException( wxT("Snippet did not compile: %s"), GLua().PopString(-1).c_str() );

		// Execute expression
		if( lua_pcall(GLuaState(), 0, LUA_MULTRET, 0) != 0 )
			throw unException( wxT("Snippet did not execute: %s"), GLua().PopString(-1).c_str() );

		return SQLITE_OK;
	}

	void unLua::Init()
	{
		LuaState = lua_open();

		// a list of libs to expose for use in scripts
		static const luaL_Reg luaLibs[] = {
			{"", luaopen_base},
			//{LUA_LOADLIBNAME, luaopen_package},
			{LUA_TABLIBNAME, luaopen_table},
			//{LUA_IOLIBNAME, luaopen_io},
			//{LUA_OSLIBNAME, luaopen_os},
			{LUA_STRLIBNAME, luaopen_string},
			{LUA_MATHLIBNAME, luaopen_math},
			//{LUA_DBLIBNAME, luaopen_debug},
			{NULL, NULL}
		};

		for(const luaL_reg* lib=luaLibs; lib->func; ++lib ) 
		{
			lua_pushcfunction(LuaState, lib->func);
			lua_pushstring(LuaState, lib->name);
			lua_call(LuaState, 1, 0);
		}

		// Init our functions
		static const struct luaL_reg myFunctions[] = {
			//{"Int", Lua_GetPrimitiveIntValue},
			//{"Bool", Lua_GetPrimitiveBoolValue},
			{"Flag", Lua_GetFlagInteger},
			{"FlagMask", Lua_GetFlagMask},
			{"FlagName", Lua_GetFlagName},
			{"TypeExists", Lua_TypeExists},
			//{"__index", Lua_GlobalIndex},
			{NULL, NULL}
		};

		//luaL_register(LuaState, "myFunctions", myFunctions);
		for(const luaL_reg* lib=myFunctions; lib->func; ++lib ) 
		{
			lua_pushcfunction(LuaState, lib->func);
			lua_setglobal(LuaState, lib->name);
		}

		// metatable stuff
		//stackDump(LuaState);
		luaL_newmetatable(LuaState, "test");
		//stackDump(LuaState);
		lua_pushstring(LuaState, "__index");
		lua_pushcfunction(LuaState, Lua_GlobalIndex);
		//stackDump(LuaState);
		lua_settable(LuaState, -3);       // metatable.__index = Lua_GlobalIndex
		//stackDump(LuaState);
		lua_setmetatable(LuaState, LUA_GLOBALSINDEX);
		//stackDump(LuaState);
	}

	void unLua::RegisterFunction( const char* name, lua_CFunction func )
	{
		lua_pushcfunction(LuaState, func);
		lua_setglobal(LuaState, name);
	}

	wxString unLua::ToString( int index, bool bStrict/*=true*/ )
	{
		if( lua_isstring(LuaState, index) == TRUE || !bStrict )
			return wxString::FromUTF8(lua_tostring(LuaState, index));

		throw unException( wxT("lua_isstring: not a string!"));
	}

	bool unLua::ToBoolean( int index, bool bStrict/*=true*/ )
	{
		if( lua_isboolean(LuaState, index) == TRUE || !bStrict )
			return lua_toboolean(LuaState, index) == TRUE;

		throw unException( wxT("lua_isboolean: not a bool!"));
	}

	double unLua::ToNumber( int index, bool bStrict/*=true*/ )
	{
		if( lua_isnumber(LuaState, index) == TRUE || !bStrict )
			return lua_tonumber(LuaState, index);

		throw unException( wxT("lua_isnumber: not a number!"));
	}

	qword unLua::ToInteger( int index, bool bStrict/*=true*/ )
	{
		if( lua_isinteger(LuaState, index) == TRUE || !bStrict )
			return lua_tointeger(LuaState, index);

		throw unException( wxT("lua_isinteger: not a integer!"));
	}

	wxString unLua::PopString( int index )
	{
		wxString result = wxString::FromUTF8(lua_tostring(LuaState, index));
		Pop(1);
		return result;
	}

	void unLua::Pop( int num )
	{
		lua_pop(LuaState, num);
	}

	template<class T>
	void unLua::ReadStack( int stackIndex, int paramType, T& param )
	{
		switch(paramType)
		{
		case LUA_TINT:	param = ToInteger(stackIndex); return;
		case LUA_TNUMBER:	param = ToNumber(stackIndex); return;
		case LUA_TBOOLEAN:	param = ToBoolean(stackIndex); return;
		case LUA_TSTRING:	param = ToString(stackIndex); return;
		case LUA_TNIL:
		case LUA_TTABLE:
		case LUA_TFUNCTION:
		case LUA_TUSERDATA:
		case LUA_TTHREAD:
		case LUA_TLIGHTUSERDATA:
		default:
		}
		throw unException( wxT("Unsupported lua type: %d"), paramType);
	}

	void unLua::SetContext( const unPrimitive* flow )
	{
		Context = flow;
	}

	const unPrimitive* unLua::GetContext() const
	{
		if( Context )
			return Context;
		throw unException( wxT("Lua context not found"));
	}
}