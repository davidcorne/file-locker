#include "LockedFile/PathNotFoundError.h"

//=============================================================================
PathNotFoundError::PathNotFoundError(std::string path)
  : m_path(path)
{
}

//=============================================================================
std::string PathNotFoundError::to_string() const
{
  std::string message("Path not found ");
  return message + m_path;
}

//=============================================================================
PathNotFoundError::~PathNotFoundError()
{
}
