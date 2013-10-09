#ifndef FileInUseError_H
#define FileInUseError_H

#include "Error.h"

//=============================================================================
class FileInUseError : public Error {
public:

  FileInUseError(std::string path);

  virtual std::string to_string() const override;

  virtual ~FileInUseError();
private:

  std::string m_path;
};

#endif
