// ============================================================================
// Package
// ============================================================================
#pragma once
#include "ParseUNR/File.h"

namespace Unrilities {
	// ============================================================================
	// unPackage
	// ============================================================================
	class unPackage
	{
	public:
		unFile& File;
		bool bDelayLoading;
		auto_ptr<unElement> RootElement;
		auto_ptr<unPrimitive> RootPrimitive;
		vector<unPrimitive*> DelayLoaded;

	public:
		unPackage( unFile& file );

		void ReadFile();
		bool IsDelayLoading() const;
		void RegisterDelayLoaded(unPrimitive* primitive );

	public:
		size_t			Read		( void* buffer, size_t count ) { return File.Read(buffer, count); }
		size_t			Write		( void* buffer, size_t count ) { return File.Write(buffer, count); }
		void			Seek		( wxFileOffset offset, wxSeekMode mode = wxFromStart ) { File.Seek(offset, mode); }
		wxFileOffset	Tell		() const { return File.Tell(); }
		wxFileOffset	Length		() const { return File.Length(); }

	public:
		void			PushGuard	( wxFileOffset from, wxFileOffset to ){ File.PushGuard(from, to);  }
		void			PopGuard	() { File.PopGuard(); }
		unFileGuards	GetGuards	() const { return File.GetGuards(); }
		void			Skip		( wxFileOffset Offset, wxFileOffset Length ) { File.Skip(Offset, Length); }
	};
}