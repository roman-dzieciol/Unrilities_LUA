// ============================================================================
// Flow
// ============================================================================
#pragma once
#include "ParseUNR/Primitive.h"

namespace Unrilities {
	// ============================================================================
	// unFlow
	// ============================================================================
	class unFlow : public unPrimitive
	{
	public:
		unFlow();
		~unFlow();

	public:
		virtual void Initialize(unElement* Element, unPrimitive* Parent);
		virtual void Read(unPackage& file);
		virtual void Log(const wxString& prefix) const;

	public:
		void ExecChunk();
		void CheckParamCount(const int ParamCount, const int StackNum);
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual const unPrimitive* GetContext() const;

	public:
		virtual bool IsFlow() const;

	public:
		virtual bool GetBoolValue() const;
		virtual qword GetIntValue() const;
		virtual wxString GetStringValue() const;
		virtual int PushLuaValue(lua_State* luaState) const;
	};

	// ============================================================================
	// unFlowBreak
	// ============================================================================
	class unFlowBreak
	{

	};

	// ============================================================================
	//	unFlowReadPrinter
	// ============================================================================
	class unFlowReadPrinter
	{
	public:
		unPrimitive* Primitive;
		unPackage& File;
		wxFileOffset Begin;

	public:
		unFlowReadPrinter(unPrimitive* Primitive, unPackage& File);
		~unFlowReadPrinter();
	};
}

#if _DEBUG
#define UNR_FLOW_READ_DEBUG unFlowReadPrinter ReadPrinter(this,file);
#define UNR_FLOW_READ_DEBUG_NOW { UNR_FLOW_READ_DEBUG }
#else
#define UNR_FLOW_READ_DEBUG 
#define UNR_FLOW_READ_DEBUG_NOW { UNR_FLOW_READ_DEBUG }
#endif