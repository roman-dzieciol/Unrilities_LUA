// ============================================================================
//	Primitive
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Primitive.h"
#include "ParseUNR/TypesData.h"
#include "ParseUNR/Package.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/TypesFlow.h"
#include "ParseUNR/Expression.h"
#include "ParseUNR/Lua.h"

namespace Unrilities {
	// ============================================================================
	// unFlow
	// ============================================================================
	unFlow::unFlow()
	{
	}

	unFlow::~unFlow()
	{
		//if( Expression != LUA_NOREF )
		//	luaL_unref(GLuaState(), LUA_REGISTRYINDEX, Expression);
	}

	void unFlow::Initialize( unElement* Element, unPrimitive* Parent )
	{
		unPrimitive::Initialize(Element, Parent);
		//InitChunk(Element->GetName());
		FindName = GNameNone();
	}

	void unFlow::Read( unPackage& /*file*/ )
	{
		if( Element->GetExpression() != LUA_NOREF )
			ExecChunk();
	}

	void unFlow::ExecChunk()
	{
		struct finalizer {
			finalizer(const unPrimitive* flow) { GLua().SetContext(flow); }
			~finalizer() { GLua().SetContext(NULL); }
		} finally(GetContext());

		// Get stack size
		int stackSize = lua_gettop(GLuaState());

		// Push compiled result onto the stack
		lua_rawgeti(GLuaState(), LUA_REGISTRYINDEX, Element->GetExpression());

		// Execute expression
		//lua_call(GLuaState(), 0, LUA_MULTRET);
		if( lua_pcall(GLuaState(), 0, LUA_MULTRET, 0) != 0 )
			throw unException( wxT("Expression did not execute: %s"), GLua().PopString(-1).c_str() );

		// Get stack size difference
		int stackDiff = lua_gettop(GLuaState()) - stackSize;

		// Let primitive handle results
		ParseChunk(stackSize, stackDiff);

		// Pop results off stack
		lua_pop(GLuaState(), stackDiff);
	}

	void unFlow::CheckParamCount( const int ParamCount, const int StackNum )
	{
		if( StackNum < ParamCount )
			throw unException( wxT("Not enough parameters for: %s"), Print().c_str() );
	}

	void unFlow::ParseChunk( int /*StackIdx*/, int /*StackNum*/ )
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	bool unFlow::IsFlow() const
	{
		return true;
	}

	bool unFlow::GetBoolValue() const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	Unrilities::qword unFlow::GetIntValue() const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	wxString unFlow::GetStringValue() const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	int unFlow::PushLuaValue( lua_State* /*luaState*/ ) const
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	void unFlow::Log(const wxString& prefix) const
	{
		wxLogMessage(wxT("%s%s\t%s -- %s")
			, prefix.c_str()
			, Element ? Element->GetType().c_str() : wxT("")
			, Print().c_str()
			, Element ? Element->GetName().c_str() : wxT("")
			);
	}

	const unPrimitive* unFlow::GetContext() const
	{
		return this;
	}

	// ============================================================================
	//	unFlowReadPrinter
	// ============================================================================
	unFlowReadPrinter::unFlowReadPrinter( unPrimitive* Primitive, unPackage& File )
		: Primitive(Primitive), File(File), Begin(File.Tell())
	{
	}

	unFlowReadPrinter::~unFlowReadPrinter()
	{
		Primitive->Log( wxString::Format(wxT("           ")) );
	}
}