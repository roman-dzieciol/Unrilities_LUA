// ============================================================================
// Lua
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// unLua
	// ============================================================================
	extern void stackDump (lua_State *L);

	// ============================================================================
	// unLua
	// ============================================================================
	class unLua
	{
	public:
		typedef struct ContextData
		{
			const unPrimitive* Context;
		} ContextData;

	private:
		lua_State* LuaState;
		const unPrimitive* Context;

	public:
		static unLua& Global();
		static lua_State* GlobalState();
		unLua();
		~unLua();

	public:
		void Init();
		void SetContext(const unPrimitive* flow);
		const unPrimitive* GetContext() const;

	public:
		void Load(unDatabase& database);

	private:
		static int OnLoad(void* data, int argc, char** argv, char** azColName);

	public:
		void RegisterFunction(const char* name, lua_CFunction func);
		int PushLuaContext(lua_State* state, const unPrimitive* context);

	public:
		wxString ToString(int index, bool bStrict=true);
		bool ToBoolean(int index, bool bStrict=true);
		double ToNumber(int index, bool bStrict=true);
		qword ToInteger(int index, bool bStrict=true);

	public:
		template<class T>
		void ReadStack(int stackIndex, int paramType, T& param);

	public:
		wxString PopString(int index);
		void Pop(int num);
	};

	// ============================================================================
	//	unLua utilities
	// ============================================================================
	inline unLua& GLua()
	{
		return unLua::Global();
	}

	inline lua_State* GLuaState()
	{
		return unLua::GlobalState();
	}
}