#ifndef LockedFile_H
#define LockedFile_H

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
  
  void write(std::string contents);
  // Overwrite the file with the contents of this string.
  
  ~LockedFile();
  
private:

  LockedFile(const LockedFile&);
  LockedFile& operator=(const LockedFile&);
  // cannot copy or assign

  void reset_handle_pointer() const;
  // Reset the file handle to the begining of the file.
  // Should be called after any read/write operation.
  Error* m_error;
  HANDLE m_file_handle;
  
};

#endif
