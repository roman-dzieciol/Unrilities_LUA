// ============================================================================
//	File
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// Typedefs
	// ============================================================================
	typedef list<unFileGuard> unFileGuards;
	typedef set<unFileMarker> unFileMarkers;
	typedef vector<byte> unFileBitmap;


	// ============================================================================
	// unFile
	// ============================================================================
	class unFile
	{
	protected:
		wxFFile			File;
		wxFileName		FileName;
		unFileGuards	Guards;
		unFileMarkers	Markers;
		unFileBitmap	BitMap;

	public:
		explicit unFile( const wxFileName& filename, bool bRead=true, bool bWrite=false, bool bCreate=false, bool bBinary=true );
		~unFile();

	public:
		size_t			Read		( void* buffer, size_t count );
		size_t			Write		( void* buffer, size_t count );
		void			Seek		( wxFileOffset offset, wxSeekMode mode = wxFromStart );
		wxFileOffset	Tell		() const { return File.Tell(); }
		wxFileOffset	Length		() const { return File.Length(); }

	public:
		wxFFile&		GetFile		() { return File; }
		wxFileName		GetFileName	() const { return FileName; }
		wxString		GetName		() const { return FileName.GetName(); }

	public:
		void			PushGuard	( wxFileOffset from, wxFileOffset to );
		void			PopGuard	();
		unFileGuards	GetGuards	() const { return Guards; }

	public:
		void			SetMarker	( dword marker, wxFileOffset from, wxFileOffset to );
		unFileMarkers	GetMarkers	() const { return Markers; }

	public:
		void			Skip	( wxFileOffset Offset, wxFileOffset Length );
		void			CheckBitmap	() const;
	};


	// ============================================================================
	// unFileGuard
	// ============================================================================
	class unFileGuard
	{
	public:
		wxFileOffset	From;
		wxFileOffset	To;

	public:
		explicit unFileGuard( wxFileOffset from, wxFileOffset to )
			: From(from), To(to)
		{
		}
	};


	// ============================================================================
	// unFileMarker
	// ============================================================================
	class unFileMarker : public unFileGuard
	{
	public:
		dword	Marker;

	public:
		explicit unFileMarker( dword marker, wxFileOffset from, wxFileOffset to ) 
			: Marker(marker), unFileGuard(from,to)
		{
		}

		friend bool operator < (const unFileMarker& Left, const unFileMarker& Right)
		{
			return Left.To < Right.From;
		}
	};


	// ============================================================================
	// unOffsetGuard
	// ============================================================================
	class unOffsetGuard
	{
	private:
		unFile& File; 

	public:
		unOffsetGuard( unFile& file, wxFileOffset from, wxFileOffset to ) : File(file) {
			File.PushGuard(from,to); }

		~unOffsetGuard() {
			File.PopGuard(); }
	};
}