#include "LockedFile/LockedFile.h"

#include "LockedFile/WindowsError.h"

//=============================================================================
LockedFile::LockedFile(std::string path, std::unique_ptr<Error>& err)
{
  m_file_handle = CreateFile(
    path.c_str(),                 // LPCTSTR lpFileName,
    GENERIC_READ | GENERIC_WRITE, // DWORD dwDesiredAccess,
    FILE_SHARE_READ,              // DWORD dwShareMode,
    NULL,                         // LPSECURITY_ATTRIBUTES lpSecurityAttribs,
    OPEN_EXISTING,                // DWORD dwCreationDisposition,
    FILE_ATTRIBUTE_NORMAL,        // DWORD dwFlagsAndAttributes,
    NULL                          // HANDLE hTemplateFile
  );
  if (INVALID_HANDLE_VALUE == m_file_handle) {
    // Check the error values, if it's one we know handle it appropriately
    DWORD error_value = GetLastError();
    if (error_value == 2) {
      err.reset(new PathNotFoundError(path));
    } else {
      err.reset(new WindowsError(error_value));
    }
  } else {
    // find the file size
    BOOL ok = FALSE;
    LARGE_INTEGER file_size;
    ok = GetFileSizeEx(
      m_file_handle, // HANDLE hFile,            
      &file_size     // PLARGE_INTEGER lpFileSize
    );
    assert(ok);

    OVERLAPPED overlapped;
    // lock the file
    ok = LockFileEx(
      m_file_handle,             // HANDLE hFile,
      LOCKFILE_EXCLUSIVE_LOCK |
      LOCKFILE_FAIL_IMMEDIATELY, // DWORD dwFlags,
      0,                         // DWORD dwReserved,
      file_size.LowPart,         // DWORD nNumberOfBytesToLockLow,
      file_size.HighPart,        // DWORD nNumberOfBytesToLockHigh,
      &overlapped                // LPOVERLAPPED lpOverlapped
    );
    if (!ok) {
      DWORD error_value = GetLastError();
      err.reset(new WindowsError(error_value));
    }
  }
}

//=============================================================================
LockedFile::~LockedFile()
{
  CloseHandle(m_file_handle);
}
