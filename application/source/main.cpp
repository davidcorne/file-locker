//=============================================================================
//
// 

#include "LockedFile/LockedFile.h"
#include "LockedFile/Error.h"

#include <iostream>
#include <vector>

using namespace std;

//=============================================================================
class NotEnoughArgumentsError : public Error {
public:

  virtual string to_string() const override {
    return "Not enough arguments were passed to file_locker";
  }
};


//=============================================================================
int main(int num_args, char** arguments) {
  unique_ptr<Error> error = 0;
  if (num_args <= 1) {
    error.reset(new NotEnoughArgumentsError);
  }
  vector<unique_ptr<LockedFile>> locked_files;
  if (!error) {
    for (int i = 1; i < num_args; ++i) {
      unique_ptr<LockedFile> locked_file(new LockedFile(arguments[i], error));
      if (error) {
        break;
      }
      locked_files.push_back(std::move(locked_file));
    }
  }
  if (error) {
    cout << error->to_string() << endl;
  } else {
    while (true) {}
  }
  return 0;
}
