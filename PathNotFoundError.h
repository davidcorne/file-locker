//=============================================================================
class PathNotFoundError : public Error {
public:

  PathNotFoundError(std::string path);

  virtual std::string to_string() const override;

  virtual ~PathNotFoundError();
private:

  std::string m_path;
};

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

