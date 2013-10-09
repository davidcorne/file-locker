#include "LockedFile/LockedFile.h"

#include "LockedFile/FileInUseError.h"
#include "LockedFile/WindowsError.h"

#include <assert.h>

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
    if (error_value == ERROR_FILE_NOT_FOUND) {
      err.reset(new PathNotFoundError(path));
    } else if (error_value == ERROR_SHARING_VIOLATION) {
      err.reset(new FileInUseError(path));
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

//=============================================================================
std::string LockedFile::read() const
{
  LARGE_INTEGER file_size;
  BOOL ok = FALSE;
  ok = GetFileSizeEx(
    m_file_handle, // HANDLE hFile,
    &file_size     // PLARGE_INTEGER lpFileSize
  );
  assert(ok);

  char* buffer = new char[file_size.LowPart + 1];
  DWORD  bytes_read = 0;
  ReadFile(
    m_file_handle,     // HANDLE hFile,
    buffer,            // LPVOID lpBuffer,
    file_size.LowPart, // DWORD nNumberOfBytesToRead,
    &bytes_read,       // LPDWORD lpNumberOfBytesRead,
    NULL               // LPOVERLAPPED lpOverlapped
  );
  buffer[bytes_read] = '\0';
  std::string file_as_string(buffer);
  delete[] buffer;
  reset_handle_pointer();
  return file_as_string;
}

//=============================================================================
void LockedFile::reset_handle_pointer() const
{
  SetFilePointer(
    m_file_handle, // HANDLE hFile,
    0,             // LONG lDistanceToMove,
    NULL,          // PLONG lpDistanceToMoveHigh,
    FILE_BEGIN     // DWORD dwMoveMethod
  );
}

//=============================================================================
void LockedFile::write(std::string contents)
{
  DWORD bytes_written;
  WriteFile(
    m_file_handle,    // HANDLE hFile,
    contents.c_str(), // LPCVOID lpBuffer,
    contents.length(),// DWORD nNumberOfBytesToWrite,
    &bytes_written,   // LPDWORD lpNumberOfBytesWritten,
    NULL              // LPOVERLAPPED lpOverlapped
  );
  assert(bytes_written == contents.length());
  reset_handle_pointer();
}
