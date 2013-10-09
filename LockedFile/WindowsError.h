#ifndef WindowsError_H
#define WindowsError_H

#include "Error.h"
#include <Windows.h>

//=============================================================================
class WindowsError : public Error {
public:

  WindowsError(DWORD windows_error_code);

  virtual std::string to_string() const override;

  virtual ~WindowsError();
  
private:

  DWORD m_error_code;
};

#endif
