// ============================================================================
//	TypesFlow
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/TypesFlow.h"
#include "ParseUNR/Package.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/Expression.h"
#include "ParseUNR/Lua.h"
#include "ParseUNR/Config.h"

namespace Unrilities {
	// ============================================================================
	// unContainer
	// ============================================================================
	unContainer::unContainer() : ItemCount(0), ElementType(GNameNone())
	{
	}

	void unContainer::Initialize( unElement* Element, unPrimitive* Parent )
	{
		unFlow::Initialize(Element, Parent);
		//if( Element )
		//	SetElementType(Element->GetNameID());
	}

	void unContainer::PushOffset( unPackage& File, wxFileOffset OffsetFrom, wxFileOffset OffsetTo )
	{
		if( RevertOffset == -1 )
		{
			RevertOffset = File.Tell();
			File.PushGuard(OffsetFrom, OffsetTo != -1 ? OffsetTo : File.Length());
		}
		File.Seek(OffsetFrom);
	}

	void unContainer::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(2, StackNum);
		SetElementType(GName(GLua().ToString(++StackIdx)));
		ItemCount = GLua().ToInteger(++StackIdx);
	}

	void unContainer::Read( unPackage& file )
	{
		unFlow::Read(file);

		UNR_FLOW_READ_DEBUG_NOW;

		if( ItemCount > 0 )
		{
			// Init offset
			RevertOffset = -1;

			// Check length
			if( ItemCount > (qword)file.Length() )
				throw unException(wxT("Excessive array size: %lld"), ItemCount);

			// Get container element type
			unElement* element = GElements().GetElementByType(ElementType);

			// Populate container
			PopulateContainer(file, element);

			// Read container
			ReadContainer(file, element);

			// Revert offset
			if( RevertOffset != -1 )
			{
				file.PopGuard();
				file.Seek(RevertOffset);
			}
		}
	}

	void unContainer::ReadContainer( unPackage& file, unElement* /*elementType*/ )
	{
		try 
		{
			// Read children
			for( unPrimitiveChildren::iterator it=Children.begin(); it!=Children.end(); ++it )
			{
				(*it)->Read(file);
			}
		}
		catch(unFlowBreak&) 
		{ 
			// if this container is a wrapper for array item, re-throw
			if( Parent && Parent->IsArray() )
				throw;
		}
		catch(...) { throw; } // Re-throw everything else
	}

	void unContainer::PopulateContainer( unPackage& /*file*/, unElement* /*elementType*/ )
	{
		UNR_THROW_NOT_IMPLEMENTED;
	}

	wxString unContainer::Print() const
	{
		return wxString::Format(wxT("%s[%u]"), ElementType->c_str(), ItemCount);
	}

	bool unContainer::IsSkipped() const
	{
		return ItemCount <= 0;
	}

	int unContainer::PushLuaValue( lua_State* luaState ) const
	{
		//wxLogMessage(wxT("flow:"));
		return GLua().PushLuaContext(luaState, this);
	}

	void unContainer::Log( const wxString& prefix ) const
	{
		wxLogMessage(wxT(""));
		unFlow::Log(prefix);
	}

	void unContainer::SetElementType( unNameID ElementType )
	{
		this->ElementType = ElementType;
		FindName = ElementType;
	}

	// ============================================================================
	// unOBJECT
	// ============================================================================
	unOBJECT::unOBJECT()
	{
		// Not skipped by default
		ItemCount = 1;
	}

	void unOBJECT::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(1, StackNum);
		SetElementType(GName(GLua().ToString(++StackIdx)));
		ItemCount = StackNum > 1 ? static_cast<int>(GLua().ToBoolean(++StackIdx)) : 1;
	}

	void unOBJECT::PopulateContainer( unPackage& /*file*/, unElement* elementType )
	{
		// Add elements
		vector<unElement*> elements = elementType->GetElements();
		//Children.reserve(elements.size());
		for( vector<unElement*>::iterator it=elements.begin(); it!=elements.end(); ++it )
		{
			unPrimitive* child = GPrimitives().CreatePrimitive((*it)->GetTypeID(), (*it), this);
			Children.push_back(child);
		}
	}

	wxString unOBJECT::Print() const
	{
		return wxString::Format(wxT("%s%s"), ElementType->c_str(), ItemCount > 0 ? wxT("") : wxT(" SKIPPED") );
	}

	void unOBJECT::Log( const wxString& prefix ) const
	{
		if( !GConfig().bVerboseLog && ItemCount <= 0 )
			return;

		if( Element && Element->GetName().IsEmpty() )
		{
			wxLogMessage(wxT(""));
			if( Parent && Parent->IsArray() )
			{
				int index = -1;
				unPrimitiveChildren::iterator thisIt = find(Parent->Children.begin(), Parent->Children.end(), this);
				if( thisIt != Parent->Children.end() )
					index = distance(Parent->Children.begin(), thisIt);

				wxLogMessage(wxT("%s[%d]\t%s")
					, prefix.c_str()
					, index
					, ElementType->c_str()
					);
			}
			else
			{
				wxLogMessage(wxT("%s%s")
					, prefix.c_str()
					, ElementType->c_str()
					);
			}

		}
		else
		{
			return unContainer::Log(prefix);
		}
		/*wxLogMessage(wxT("%s%s\t\"%s\" = %s")
			, prefix.c_str()
			, Element ? Element->GetType.c_str() : NULL
			, Element ? Element->GetName().c_str() : NULL
			, Print().c_str()
			);*/
	}


	// ============================================================================
	// unINCLUDE
	// ============================================================================

	wxString unINCLUDE::Print() const
	{
		return wxString::Format(wxT("%s"), IsSkipped() ? wxT("SKIPPED") : ElementType->c_str() );
	}

	void unINCLUDE::Log( const wxString& prefix ) const
	{
		if( GConfig().bVerboseLog )
			unContainer::Log(prefix);
	}

	unINCLUDE::unINCLUDE()
	{
		bInline = TRUE;
	}

	// ============================================================================
	// unDELAY
	// ============================================================================
	void unDELAY::PopulateContainer( unPackage& file, unElement* elementType )
	{
		if( file.IsDelayLoading() )
			unINCLUDE::PopulateContainer(file, elementType);
		else
			file.RegisterDelayLoaded(this);
	}

	// ============================================================================
	// unBITFIELD
	// ============================================================================
	void unBITFIELD::ReadContainer( unPackage& file, unElement* /*elementType*/ )
	{
		if( !Children.empty() )
		{
			// Store offset
			wxFileOffset bitfieldOffset = file.Tell();

			// read bitfield value
			unPrimitiveChildren::iterator it=Children.begin();
			(*it)->Read(file);
			wxFileOffset revertOffset = file.Tell();

			// read remaining primitives
			file.Seek(bitfieldOffset);
			for( it=++it; it!=Children.end(); ++it )
			{
				(*it)->Read(file);
			}
			file.Seek(revertOffset);
		}
		else
		{
			throw unException(wxT("Bitfield is empty: %s"), Print().c_str());
		}
	}

	bool unBITFIELD::IsBitField() const
	{
		return true;
	}


	// ============================================================================
	// unSWITCH
	// ============================================================================
	void unSWITCH::ParseChunk( int StackIdx, int StackNum )
	{
		unContainer::ParseChunk(StackIdx, StackNum);
	}

	void unSWITCH::Read( unPackage& file )
	{
		unFlow::Read(file);

		UNR_FLOW_READ_DEBUG_NOW;

		// Init offset
		RevertOffset = -1;

		// Check length
		if( ItemCount > (qword)file.Length() )
			throw unException(wxT("Excessive array size: %lld"), ItemCount);

		// Get container element type
		unElement* element = GElements().GetElementNumbered(ElementType->c_str(), ItemCount);

		// Populate container
		PopulateContainer(file, element);

		// Read container
		ReadContainer(file, element);

		// Revert offset
		if( RevertOffset != -1 )
		{
			file.PopGuard();
			file.Seek(RevertOffset);
		}
	}

	// ============================================================================
	// unARRAY
	// ============================================================================
	unARRAY::unARRAY()
	{
		bIsArray = TRUE;
	}
	void unARRAY::PopulateContainer( unPackage& /*file*/, unElement* elementType )
	{
		Children.reserve(ItemCount);
		for( qword i=0; i<ItemCount; ++i )
		{
			unOBJECT* child = (unOBJECT*)GPrimitives().CreatePrimitive(GName(wxT("object")), elementType, this);
			child->SetElementType(elementType->GetTypeID());
			Children.push_back(child);
		}
	}

	bool unARRAY::IsArray() const
	{
		return true;
	}
	// ============================================================================
	// unLOOP
	// ============================================================================
	unLOOP::unLOOP()
	{
		// Not skipped by default
		ItemCount = 1;
		bIsArray = TRUE;
	}

	void unLOOP::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(1, StackNum);
		SetElementType(GName(GLua().ToString(++StackIdx)));
		ItemCount = StackNum > 1 ? static_cast<int>(GLua().ToBoolean(++StackIdx)) : 1;
	}

	void unLOOP::PopulateContainer( unPackage& /*file*/, unElement* /*elementType*/ )
	{
		// do nothing
	}

	void unLOOP::ReadContainer( unPackage& file, unElement* elementType )
	{
		// Loop until stopped externally
		try
		{
			while(true)
			{
				// Create child primitive
				unOBJECT* child = (unOBJECT*)GPrimitives().CreatePrimitive(GName(wxT("object")), elementType, this);
				child->SetElementType(elementType->GetTypeID());
				Children.push_back(child);

				// Read child primitive
				Children.back()->Read(file);
			}
		}
		catch(unFlowBreak&) {} // unFlowBreak exception used for breaking the loop
		catch(...) { throw; } // Re-throw everything else
	}

	void unLOOP::Log( const wxString& prefix ) const
	{
		wxLogMessage(wxT(""));
		wxLogMessage(wxT("%s%s array:")
			, prefix.c_str()
			, ElementType->c_str()
			);
	}

	bool unLOOP::IsArray() const
	{
		return true;
	}
	// ============================================================================
	// unBREAK
	// ============================================================================
	unBREAK::unBREAK() : bCondition(false)
	{

	}

	void unBREAK::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(1, StackNum);
		bCondition = GLua().ToBoolean(++StackIdx);
	}

	void unBREAK::Read( unPackage& file )
	{
		UNR_FLOW_READ_DEBUG;
		unFlow::Read(file);

		if( bCondition )
			throw unFlowBreak();
	}

	wxString unBREAK::Print() const
	{
		return wxString::Format(wxT("%s"), (bCondition?wxT("TRUE"):wxT("FALSE")));
	}

	void unBREAK::Log( const wxString& prefix ) const
	{
		if( GConfig().bVerboseLog )
			unFlow::Log(prefix);
	}


	// ============================================================================
	// unSKIP
	// ============================================================================
	unSKIP::unSKIP() : SkipOffset(-1)
	{

	}

	void unSKIP::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(2, StackNum);
		bCondition = GLua().ToBoolean(++StackIdx);
		SkipOffset = GLua().ToInteger(++StackIdx);
	}

	void unSKIP::Read( unPackage& file )
	{
		UNR_FLOW_READ_DEBUG;
		unFlow::Read(file);

		if( bCondition )
		{
			file.Skip(file.Tell(), SkipOffset-file.Tell());
			throw unFlowBreak();
		}
	}

	// ============================================================================
	// unASSERT
	// ============================================================================
	unASSERT::unASSERT() : bCondition(false)
	{
	}

	void unASSERT::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(1, StackNum);
		bCondition = GLua().ToBoolean(++StackIdx);
	}

	void unASSERT::Read( unPackage& file )
	{
		UNR_FLOW_READ_DEBUG;
		unFlow::Read(file);

		if( !bCondition )
			throw unException(wxT("Assertion failed: %s"), Element->GetName().c_str());
	}

	wxString unASSERT::Print() const
	{
		return wxString::Format(wxT("%s"), (bCondition?wxT("TRUE"):wxT("FALSE")));
	}

	// ============================================================================
	// unOFFSET
	// ============================================================================
	unOFFSET::unOFFSET() : OffsetFrom(-1), OffsetTo(-1)
	{
	}

	void unOFFSET::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(1, StackNum);
		OffsetFrom = GLua().ToInteger(++StackIdx);
		OffsetTo = StackNum > 1 ? GLua().ToInteger(++StackIdx) : -1;
	}

	void unOFFSET::Read( unPackage& file )
	{
		UNR_FLOW_READ_DEBUG;
		unFlow::Read(file);
		Parent->PushOffset(file,OffsetFrom, OffsetTo);
	}

	wxString unOFFSET::Print() const
	{
		if( OffsetTo != -1 )
			return wxString::Format(wxT("0x%.8llx to 0x%.8llx"), OffsetFrom, OffsetTo);
		else
			return wxString::Format(wxT("0x%.8llx"), OffsetFrom);
	}

	// ============================================================================
	// unOFFSET
	// ============================================================================
	void unDATA::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(2, StackNum);
		DataName = GLua().ToString(++StackIdx);
		DataSize =  GLua().ToInteger(++StackIdx);
	}

	void unDATA::Read( unPackage& file )
	{
		UNR_FLOW_READ_DEBUG;
		unFlow::Read(file);

		if( DataSize > 0 && DataSize < file.Length() )
		{
			RawData.reserve(DataSize);
			RawData.resize(DataSize);
			file.Read( &RawData[0], DataSize );
			//file.Skip(file.Tell(), DataSize);
		}
		else
			throw unException(wxT("Invalid data length at 0x%.8x"), static_cast<dword>(file.Tell()));
	}

	wxString unDATA::Print() const
	{
		return wxString::Format(wxT("%s[%d]"), DataName.c_str(), DataSize);
	}

	// ============================================================================
	// unLOG
	// ============================================================================
	void unLOG::ParseChunk( int StackIdx, int StackNum )
	{
		CheckParamCount(1, StackNum);
		Text = GLua().ToString(++StackIdx);
	}

	void unLOG::Read( unPackage& file )
	{
		unFlow::Read(file);
		UNR_FLOW_READ_DEBUG;
	}

	void unLOG::Log( const wxString& prefix ) const
	{
		wxLogMessage(wxT("%s%s")
			, prefix.c_str()
			, Text.c_str()
			);
	}
}