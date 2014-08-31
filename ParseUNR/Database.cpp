// ============================================================================
//	Database
// ============================================================================
#include "ParseUNR/Precompile.h"
#include "ParseUNR/Database.h"

namespace Unrilities {
	// ============================================================================
	//	unDatabase
	// ============================================================================
	unDatabase::unDatabase() : Database(NULL), OpenMode(SQLITE_OPEN_READONLY)
	{
	}

	unDatabase::~unDatabase()
	{
		// Close DB if open
		if( Database )
		{    
			sqlite3_close(Database);
			Database = NULL;
		}
	}

	void unDatabase::Load( const wxString& filename )
	{
		if( !filename.IsEmpty() )
		{
			wxLogMessage(wxT("Loading database: %s"), filename.c_str());
			Filename = filename;
		}
		else
		{
			throw unException(wxT("Database path empty!"));
		}

		// Close DB if open
		if( Database )
		{    
			sqlite3_close(Database);
			Database = NULL;
		}

		// Open DB
		int rc = sqlite3_open_v2(Filename.mbc_str(), &Database, OpenMode, NULL);
		if( rc != SQLITE_OK )
		{
			wxString errmsg = wxString(sqlite3_errmsg(Database), wxConvUTF8);
			sqlite3_close(Database);
			Database = NULL;
			throw unException(wxT("Can't open database: %s!"), errmsg.c_str());
		}
	}

	void unDatabase::Execute( const wxString& command, Callback callback/*=DefaultCallback*/, void* data/*=NULL*/ )
	{
		if( Database )
		{
			char* zErrMsg = 0;
			int rc = sqlite3_exec(Database, command.mbc_str(), callback, data, &zErrMsg);
			if( rc != SQLITE_OK )
			{
				wxString errmsg = wxString(zErrMsg, wxConvUTF8);
				sqlite3_free(zErrMsg);
				throw unException(wxT("SQL error!\n Database: %s\n Command: %s\n Result: %s"), Filename.c_str(), command.c_str(), errmsg.c_str());
			}
		}
		else
		{
			throw unException(wxT("Database not loaded!"));
		}
	}

	int unDatabase::DefaultCallback( void* WXUNUSED(NotUsed), int argc, char** argv, char** azColName )
	{
		for(int i=0; i<argc; i++)
		{
			wxLogMessage(wxT("%hs = %hs"), azColName[i], argv[i] ? argv[i] : "NULL");
		}
		wxLogMessage(wxT(""));
		return SQLITE_OK;
	}
}