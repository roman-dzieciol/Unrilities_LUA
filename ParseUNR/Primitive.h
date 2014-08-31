// ============================================================================
// Primitive
// ============================================================================
#pragma once
#include "ParseUNR/Name.h"

namespace Unrilities {
	// ============================================================================
	// unPrimitive
	// ============================================================================
	class unPrimitive
	{
	public:
		// REQ: iterator must not be invalidated by insertion
		typedef vector<unPrimitive*> unPrimitiveChildren; 

	public:
		unElement* Element;
		unPrimitive* Parent;
		unPrimitiveChildren Children;
		unNameID FindName;
		BOOL bInline;
		BOOL bIsArray;

	public:
		unPrimitive();
		virtual void Initialize(unElement* Element, unPrimitive* Parent);
		virtual ~unPrimitive();

	public:
		virtual void Read(unPackage& file) = 0;
		virtual wxString Print() const;
		virtual void Log(const wxString& prefix) const;
		virtual void PushOffset(unPackage& File, wxFileOffset OffsetFrom, wxFileOffset OffsetTo);
		virtual bool IsFlow() const;
		virtual bool IsArray() const;
		virtual bool IsBitField() const;
		//virtual bool IsInline() const;

	public:
		virtual bool GetBoolValue() const = 0;
		virtual qword GetIntValue() const = 0;
		virtual wxString GetStringValue() const = 0;
		virtual int PushLuaValue(lua_State* luaState) const = 0;

	public:
		unPrimitive* FindChild( unNameID ElementName ) const;
		unPrimitive* FindAncestorChild( unNameID ElementName ) const;
		unPrimitive* GetRoot();
		unPrimitive* GetChildByIndex(size_t index) const;
	};

	// ============================================================================
	// unPrimitives
	// ============================================================================
	class unPrimitives
	{
	private:
		typedef unPrimitive* (*unPrimitiveCreator)();
		WX_DECLARE_HASH_MAP( unName*, unPrimitiveCreator, wxPointerHash, wxPointerEqual, unPrimitiveMap );
		unPrimitiveMap Primitives;

	public:
		static unPrimitives& Global();
		unPrimitives();
		~unPrimitives();

	public:
		bool Exists(unNameID Name) const;
		unPrimitive* CreatePrimitive( unNameID Name, unElement* Element, unPrimitive* Parent, bool bCanFail=false ) const;

	private: 
		void AddPrimitive( unNameID Name, unPrimitiveCreator primitive );
		template<class T> static unPrimitive* CreatePrimitive();
	};


	// ============================================================================
	//	unPrimitives utilities
	// ============================================================================
	inline unPrimitives& GPrimitives()
	{
		return unPrimitives::Global();
	}

	// ============================================================================
	//	unPrimitiveReadPrinter
	// ============================================================================
	class unPrimitiveReadPrinter
	{
	public:
		unPrimitive* Primitive;
		unPackage& File;
		wxFileOffset Begin;

	public:
		unPrimitiveReadPrinter(unPrimitive* Primitive, unPackage& File);
		~unPrimitiveReadPrinter();
	};
}
#if _DEBUG
#define UNR_PRIMITIVE_READ_DEBUG unPrimitiveReadPrinter ReadPrinter(this,file);
#define UNR_PRIMITIVE_READ_DEBUG_NOW { UNR_PRIMITIVE_READ_DEBUG }
#else
#define UNR_PRIMITIVE_READ_DEBUG
#define UNR_PRIMITIVE_READ_DEBUG_NOW { UNR_PRIMITIVE_READ_DEBUG }
#endif