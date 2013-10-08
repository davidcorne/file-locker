#ifndef PathNotFoundError_H
#define PathNotFoundError_H

#include "Error.h"

//=============================================================================
class PathNotFoundError : public Error {
public:

  PathNotFoundError(std::string path);

  virtual std::string to_string() const override;

  virtual ~PathNotFoundError();
private:

  std::string m_path;
};

#endif
