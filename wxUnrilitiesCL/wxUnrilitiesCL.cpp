// ============================================================================
//  wxUnrilitiesCL.cpp
// ============================================================================

#include "wxUnrilitiesCL/Precompile.h"
#include "wxUnrilitiesCL/wxUnrilitiesCL.h"
#include "ParseUNR/File.h"
#include "ParseUNR/Config.h"
#include "ParseUNR/Primitive.h"
#include "ParseUNR/Element.h"
#include "ParseUNR/Package.h"

// ============================================================================
// wxUnrilitiesCL
// ============================================================================

IMPLEMENT_APP_CONSOLE(wxUnrilitiesCL);

int wxUnrilitiesCL::OnRun()
{
#ifdef _DEBUG
	FILE* m_pLogFile = fopen( "log.txt", "w+" );
	delete wxLog::SetActiveTarget(new wxLogStderr(m_pLogFile));
	wxLog::SetVerbose(true);
#endif

	try 
	{
		static const wxCmdLineEntryDesc cmdLineDesc[] =
		{
			{ wxCMD_LINE_PARAM,  NULL, NULL, wxT("input file"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
			{ wxCMD_LINE_NONE, NULL, NULL, NULL, (wxCmdLineParamType)0, 0 }
		};

		wxCmdLineParser parser(cmdLineDesc, argc, argv);
		
		switch (parser.Parse())
		{
		case -1:
			break;

		case 0:
			ParseParams(parser);
			break;
		}

		// Debug wait
		//wxSystem(wxT("pause"));
		return 0;

	}  
	catch( Unrilities::unException& e ) 
	{ 
		wxLogMessage(wxT("%s"), e.What().c_str()); 
		//wxMessageOutput::Get()->Printf(wxT("%s\n"), e.What().c_str()); 
	}
	catch( exception& e ) 
	{ 
		wxLogMessage(wxT("%hs"), e.what()); 
		//wxMessageOutput::Get()->Printf(wxT("%hs\n"), e.what()); 
	}

#ifdef _DEBUG
	delete wxLog::SetActiveTarget(NULL);
	if (m_pLogFile != NULL)
		fclose(m_pLogFile);
#endif

	// Debug wait
	//wxSystem(wxT("pause"));
	return 1;
}


void wxUnrilitiesCL::ParseParams(const wxCmdLineParser& cmdline)
{
	// Init config
	Unrilities::GConfig().Load(wxT("ParseUNR.sqlite"));

	// Check cmdline
	if( cmdline.GetParamCount() == 0 )
	{
		// Load all files
		wxArrayString files;
		wxDir::GetAllFiles( wxT("."), &files, wxT("*.u"), wxDIR_FILES | wxDIR_HIDDEN | wxDIR_DIRS );

		for( size_t i=0; i!=files.Count(); ++i )
		{
			LoadPackage(files[i]);
		}
	}
	else
	{
		// Load specified file
		LoadPackage(cmdline.GetParam(0));
	}
}

void wxUnrilitiesCL::LoadPackage(const wxString& filename)
{
	// Load package
	wxLogMessage( wxT("Load File %s"), filename.c_str() );
	UNR::unFile file(filename);

	// Parse package
	UNR::unPackage package(file);
	{
#ifndef _DEBUG
		// Don't log in this scope
		wxLogNull logNo;
#endif

		wxLogMessage( wxT("Parse Package %s"), filename.c_str() );
		package.ReadFile();
		wxLogMessage( wxT("Parsed Package %s"), filename.c_str() );
	}

	file.CheckBitmap();

}