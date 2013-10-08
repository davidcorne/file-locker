//=============================================================================
class LockedFile {
public:

  LockedFile(std::string path, std::unique_ptr<Error>& err);

  ~LockedFile();
  
private:

  LockedFile(const LockedFile&);
  LockedFile& operator=(const LockedFile&);
  // cannot copy or assign
  
  Error* m_error;
  HANDLE m_file_handle;
  
};

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
    // the most likly culprit, possible to instead call GetLastError and
    // check what exactly went wrong, leave for another day.
    err.reset(new PathNotFoundError(path));
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
      // err.reset(new FileUsedByAnotherProcess(path));
    }
  }
}

//=============================================================================
LockedFile::~LockedFile()
{
  CloseHandle(m_file_handle);
}
