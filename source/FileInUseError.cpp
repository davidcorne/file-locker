#include "LockedFile/FileInUseError.h"

//=============================================================================
FileInUseError::FileInUseError(std::string path)
  : m_path(path)
{
}

//=============================================================================
std::string FileInUseError::to_string() const
{
  std::string first_part("File ");
  std::string second_part(" is in use by another process.");
  return first_part+ m_path + second_part;
}

//=============================================================================
FileInUseError::~FileInUseError()
{
}
