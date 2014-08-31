// ============================================================================
// Database
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// unDatabase
	// ============================================================================
	class unDatabase
	{
	private:
		wxString Filename;
		sqlite3* Database;
		int OpenMode;

	public:
		typedef int (*Callback)(void* NotUsed, int argc, char** argv, char** azColName);

	public:
		unDatabase();
		~unDatabase();

	public:
		void Load(const wxString& filename);
		void Execute(const wxString& command, Callback callback=DefaultCallback, void* data=NULL);


	private:
		static int DefaultCallback(void* NotUsed, int argc, char** argv, char** azColName);
	};
}