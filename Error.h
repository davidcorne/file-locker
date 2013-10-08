#ifndef Error_H
#define Error_H

//=============================================================================
class Error {
public:
  
  Error();

  virtual std::string to_string() const = 0;

  virtual ~Error() = 0;
};

Error::Error()
{
}

Error::~Error()
{
}

#endif
