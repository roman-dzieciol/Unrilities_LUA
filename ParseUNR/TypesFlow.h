// ============================================================================
// TypesFlow
// ============================================================================
#pragma once
#include "ParseUNR/Flow.h"
#include "ParseUNR/Name.h"

namespace Unrilities {
	// ============================================================================
	// unContainer
	// ============================================================================
	class unContainer : public unFlow
	{
	public:
		unNameID ElementType;
		qword ItemCount;
		wxFileOffset RevertOffset;

	public:
		unContainer();
		virtual void Initialize(unElement* Element, unPrimitive* Parent);
		virtual void PushOffset(unPackage& File, wxFileOffset OffsetFrom, wxFileOffset OffsetTo);
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
		virtual wxString Print() const;
		virtual void Log(const wxString& prefix) const;
		virtual int PushLuaValue(lua_State* luaState) const; 
		void SetElementType(unNameID ElementType);

	public:
		virtual void PopulateContainer(unPackage& file, unElement* elementType);
		virtual void ReadContainer(unPackage& file, unElement* elementType);
		virtual bool IsSkipped() const;
	};

	// ============================================================================
	// unOBJECT
	// ============================================================================
	class unOBJECT : public unContainer
	{
	public:
		unOBJECT();
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void PopulateContainer(unPackage& file, unElement* elementType);
		virtual wxString Print() const;
		virtual void Log(const wxString& prefix) const;
	};

	// ============================================================================
	// unINCLUDE
	// ============================================================================
	class unINCLUDE : public unOBJECT
	{
	public:
		unINCLUDE();
		//virtual bool IsInline() const;
		virtual wxString Print() const;
		virtual void Log(const wxString& prefix) const;
	};

	// ============================================================================
	// unDELAY
	// ============================================================================
	class unDELAY : public unINCLUDE
	{
	public:
		virtual void PopulateContainer(unPackage& file, unElement* elementType);
	};

	// ============================================================================
	// unBITFIELD
	// ============================================================================
	class unBITFIELD : public unINCLUDE
	{
	public:
		virtual void ReadContainer(unPackage& file, unElement* elementType);
		virtual bool IsBitField() const;
	};

	// ============================================================================
	// unSWITCH
	// ============================================================================
	class unSWITCH : public unINCLUDE
	{
	public:
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
	};

	// ============================================================================
	// unARRAY
	// ============================================================================
	class unARRAY : public unContainer
	{
	public:
		unARRAY();
		virtual void PopulateContainer(unPackage& file, unElement* elementType);
		virtual bool IsArray() const;
	};

	// ============================================================================
	// unLOOP
	// ============================================================================
	class unLOOP : public unContainer
	{
	public:
		unLOOP();
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void PopulateContainer(unPackage& file, unElement* elementType);
		virtual void ReadContainer(unPackage& file, unElement* elementType);
		virtual void Log(const wxString& prefix) const;
		virtual bool IsArray() const;
	};

	// ============================================================================
	// unBREAK
	// ============================================================================
	class unBREAK : public unFlow
	{
	protected:
		bool bCondition;

	public:
		unBREAK();
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
		virtual wxString Print() const;
		virtual void Log(const wxString& prefix) const;
	};

	// ============================================================================
	// unSKIP
	// ============================================================================
	class unSKIP : public unBREAK
	{
	protected:
		wxFileOffset SkipOffset;

	public:
		unSKIP();
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
	};

	// ============================================================================
	// unASSERT
	// ============================================================================
	class unASSERT : public unFlow
	{
	private:
		bool bCondition;

	public:
		unASSERT();
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
		virtual wxString Print() const;
	};

	// ============================================================================
	// unOFFSET
	// ============================================================================
	class unOFFSET : public unFlow
	{
	private:
		wxFileOffset OffsetFrom;
		wxFileOffset OffsetTo;

	public:
		unOFFSET();
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
		virtual wxString Print() const;
	};

	// ============================================================================
	// unDATA
	// ============================================================================
	class unDATA : public unFlow
	{
	private:
		wxString DataName;
		int64 DataSize;
		vector<byte> RawData;

	public:
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
		virtual wxString Print() const;
	};

	// ============================================================================
	// unLOG
	// ============================================================================
	class unLOG : public unFlow
	{
	private:
		wxString Text;

	public:
		virtual void ParseChunk(int StackIdx, int StackNum);
		virtual void Read(unPackage& file);
		virtual void Log(const wxString& prefix) const;
	};
}