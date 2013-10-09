#ifndef LockedFile_H
#define LockedFile_H

#include <assert.h>
#include <string>
#include <memory>

#include <Windows.h>

#include "Error.h"
#include "PathNotFoundError.h"

//=============================================================================
class LockedFile {
public:

  LockedFile(std::string path, std::unique_ptr<Error>& err);

  std::string read() const;
  // Read the entire file and return it as a string.
  
  ~LockedFile();
  
private:

  LockedFile(const LockedFile&);
  LockedFile& operator=(const LockedFile&);
  // cannot copy or assign
  
  Error* m_error;
  HANDLE m_file_handle;
  
};

#endif
