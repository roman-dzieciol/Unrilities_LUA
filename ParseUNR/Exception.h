// ============================================================================
//	Exception
// ============================================================================
#pragma once

namespace Unrilities {
	// ============================================================================
	// unException
	// ============================================================================
	class unException : public std::exception
	{
	public: 
		unException( const wxChar *pszFormat, ... )
		{
			va_list argptr;
			va_start(argptr, pszFormat);
			m_errorMsg.PrintfV(pszFormat, argptr);
			va_end(argptr);
		}

		unException( const unException& rhs ) : m_errorMsg(rhs.m_errorMsg)
		{
		}

		virtual ~unException()
		{
		}

		unException& operator=( const unException& rhs )
		{
			m_errorMsg = rhs.m_errorMsg; 
			return *this; 
		}

		wxString What() const
		{
			return m_errorMsg;
		}

	private:
		wxString m_errorMsg;
	};

}

#define UNR_THROW_NOT_IMPLEMENTED throw unException(wxT("NOT IMPLEMENTED! %s:%u %s"), __FILEW__, __LINE__ , __FUNCTIONW__ );



// ============================================================================
// guards
// ============================================================================
#define guard	try {
#define unguard } catch( unException& e ) { Unrilities::LogError( wxString::Format(wxT("%s"), e.wwhat())); }\
				  catch( exception& e ) { Unrilities::LogError( wxString::Format(wxT("%hs"), e.what())); }



