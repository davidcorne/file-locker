#ifndef WindowsError_H
#define WindowsError_H

#include "Error.h"

//=============================================================================
class WindowsError : public Error {
public:

  WindowsError(int windows_error_code);

  virtual std::string to_string() const override;

  virtual ~WindowsError();
  
private:

  int m_error_code;
};

#endif
