// ============================================================================
//  wxUnrilitiesCL.h
// ============================================================================
#pragma once


// ============================================================================
// wxUnrilitiesCL
// ============================================================================
class wxUnrilitiesCL : public wxAppConsole
{
public:
    virtual bool OnInit() { return true; }
    virtual int OnRun();

private:
    void ParseParams(const wxCmdLineParser& cmdline);
	void LoadPackage(const wxString& filename);
};