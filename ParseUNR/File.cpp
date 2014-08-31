// ============================================================================
//	File
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/File.h"

namespace Unrilities {
	// ============================================================================
	//	unFile
	// ============================================================================
	unFile::unFile( const wxFileName& filename, bool bRead/*=true*/, bool bWrite/*=false*/, bool bCreate/*=false*/, bool bBinary/*=true */ ) : FileName(filename)
	{
		wxString openMode;
		if( bRead )		openMode.Append(wxT("r"));
		if( bWrite )	openMode.Append(wxT("w"));
		if( bCreate )	openMode.Append(wxT("+"));
		if( bBinary )	openMode.Append(wxT("b"));

		File.Open( FileName.GetFullPath(), openMode );
		if( !File.IsOpened() || File.Error() )
			throw unException( wxT("Could not open file %s"), FileName.GetFullPath().c_str() );

		// First guard contains entire file
		Guards.push_back(unFileGuard(0, Length()));

		// Init bits array
		BitMap = unFileBitmap(Length(),FALSE);
	}

	unFile::~unFile()
	{
		if( File.IsOpened() )
			File.Close();
	}

	size_t unFile::Read( void* buffer, size_t count )
	{
		// Verify guards
		const wxFileOffset offset = Tell();
		if( offset >= Guards.back().From && offset + count <= Guards.back().To )
		{
			// Read
			size_t bytes = File.Read(buffer, count);
			if( File.Error() )
				throw unException( wxT("Could not read file %s"), FileName.GetFullPath().c_str() );

			// Update bitmap
			// TODO: replace with something faster
			for(int i=offset; i!=offset+count; ++i)
				BitMap[i] = TRUE;

			return bytes;
		}
		else
		{
			// Outside guarded range
			throw unException( wxT("File read in %s <0x%.8x 0x%.8x> outside guarded range <0x%.8x 0x%.8x>")
				, FileName.GetFullPath().c_str()
				, static_cast<dword>(offset) 
				, static_cast<dword>(offset + count) 
				, static_cast<dword>(Guards.back().From) 
				, static_cast<dword>(Guards.back().To) 
				);
		}
	}

	size_t unFile::Write( void* buffer, size_t count )
	{
		// Verify guards
		const wxFileOffset offset = Tell();
		if( offset >= Guards.back().From && offset + count <= Guards.back().To )
		{
			// Write
			size_t bytes = File.Write(buffer, count);
			if( File.Error() )
				throw unException( wxT("Could not write file %s"), FileName.GetFullPath().c_str() );

			return bytes;
		}
		else
		{
			// Outside guarded range
			throw unException( wxT("File write in %s <0x%.8x 0x%.8x> outside guarded range <0x%.8x 0x%.8x>")
				, FileName.GetFullPath().c_str()
				, static_cast<dword>(offset) 
				, static_cast<dword>(offset + count) 
				, static_cast<dword>(Guards.back().From) 
				, static_cast<dword>(Guards.back().To) 
				);
		}
	}

	void unFile::Seek( wxFileOffset offset, wxSeekMode mode /*= wxFromStart */ )
	{
		// Seek
		if( !File.Seek(offset, mode) )
		{
			// Invalid offset
			throw unException( wxT("Invalid seek in file %s <0x%.8x>, file range: <0x%.8x 0x%.8x>")
				, FileName.GetFullPath().c_str()
				, static_cast<dword>(offset) 
				, static_cast<dword>(0) 
				, static_cast<dword>(Length()) 
				);
		}
	}

	void unFile::PushGuard( wxFileOffset from, wxFileOffset to )
	{
		// Offsets must be inside the file
		if( from >= Guards.front().From && from < Guards.front().To
		&&  to >= Guards.front().From && to <= Guards.front().To
		&&  from <= to )
		{
			// Push new guard
			Guards.push_back(unFileGuard(from,to));
		}
		else
		{
			// Invalid offsets
			throw unException( wxT("File guard in %s <0x%.8x 0x%.8x> outside valid range <0x%.8x 0x%.8x>")
				, FileName.GetFullPath().c_str()
				, static_cast<dword>(from) 
				, static_cast<dword>(to) 
				, static_cast<dword>(0) 
				, static_cast<dword>(Length()) 
				);
		}
	}

	void unFile::PopGuard()
	{
		Guards.pop_back();
	}

	void unFile::SetMarker( dword marker, wxFileOffset from, wxFileOffset to )
	{
		// Offsets must be inside the file
		if( from >= Guards.front().From && from < Guards.front().To
		&&  to >= Guards.front().From && to <= Guards.front().To
		&&  from <= to )
		{
			// Mark
			Markers.insert(unFileMarker(marker, from, to));
		}
		else
		{
			// Invalid offsets
			throw unException( wxString::Format( wxT("File marker 0x%.8x in %s <0x%.8x 0x%.8x> outside valid range <0x%.8x 0x%.8x>")
				, static_cast<dword>(marker) 
				, FileName.GetFullPath().c_str()
				, static_cast<dword>(from) 
				, static_cast<dword>(to) 
				, static_cast<dword>(0) 
				, static_cast<dword>(Length()) 
				) );
		}
	}

	void unFile::CheckBitmap() const
	{
		int from = -1;
		int to = -1;
		for(size_t i=0; i<BitMap.size(); ++i)
		{
			if( BitMap[i] == FALSE )
			{
				if( to != -1 )
				{
					to = i;
				}
				else
				{
					from = i;
					to = i;
				}
			}
			else
			{
				if( to != -1 )
				{
					wxLogError(wxT("Unread region: <0x%.8x 0x%.8x>"), from, to);
					to = -1;
					from = -1;
				}
			}
		}
	}

	void unFile::Skip( wxFileOffset Offset, wxFileOffset Length )
	{
		// Verify guards
		if( Offset >= Guards.back().From && Offset + Length <= Guards.back().To )
		{
			// Skip bytes
			Seek(Length, wxFromCurrent);

			// Update bitmap
			// TODO: replace with something faster
			for(int i=Offset; i!=Offset+Length; ++i)
				BitMap[i] = TRUE;
		}
		else
		{
			// Outside guarded range
			throw unException( wxT("File mark in %s <0x%.8x 0x%.8x> outside guarded range <0x%.8x 0x%.8x>")
				, FileName.GetFullPath().c_str()
				, static_cast<dword>(Offset) 
				, static_cast<dword>(Offset + Length) 
				, static_cast<dword>(Guards.back().From) 
				, static_cast<dword>(Guards.back().To) 
				);
		}
	}
}