//=============================================================================
//
//D This is a specific windows error with error code from GetLastError.
//

#include "LockedFile/WindowsError.h"

#include <assert.h>

#include <Windows.h>

//=============================================================================
WindowsError::WindowsError(DWORD windows_error_code)
  : m_error_code(windows_error_code)
{
}

//=============================================================================
std::string WindowsError::to_string() const
{
  LPTSTR error_text = NULL;
  DWORD error = FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |           
    FORMAT_MESSAGE_FROM_SYSTEM |               
    FORMAT_MESSAGE_IGNORE_INSERTS,             // DWORD dwFlags,    
    NULL,                                      // LPCVOID lpSource, 
    m_error_code,                              // DWORD dwMessageId,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // DWORD dwLanguageId,
    reinterpret_cast<LPTSTR>(&error_text),     // LPTSTR lpBuffer,  
    0,                                         // DWORD nSize,      
    NULL                                       // va_list *Arguments
  );
  assert(error != 0);
  std::string message(error_text);
  return message;
}

//=============================================================================
WindowsError::~WindowsError()
{
}
