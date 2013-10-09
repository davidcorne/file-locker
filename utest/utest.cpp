//=============================================================================
//
// 

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "LockedFile/Error.h"
#include "LockedFile/PathNotFoundError.h"
#include "LockedFile/LockedFile.h"

//=============================================================================
class utest_LockedFile {
public:

  void run_tests() {
    test_file_exists();
    test_non_existant_file();
    test_file_locks();
  }

private:

  void test_non_existant_file();
  void test_file_exists();
  void test_file_locks();

  void test(bool pass, std::string message) {
    if (pass) {
      message = "Pass: " + message;
    } else {
      message = "Fail: " + message;
    }
    std::cout << message << std::endl;
    assert(pass);
  }
};

//=============================================================================
void utest_LockedFile::test_non_existant_file()
{
  std::unique_ptr<Error> error = 0;
  LockedFile("non_existant.txt", error);
  test(error, "File should not exist");
}

//=============================================================================
void utest_LockedFile::test_file_locks()
{
  std::string file_name("test_area/temporary_data.txt");
  std::ofstream test_file;
  test_file.open(file_name, std::ios::out);
  test_file << "Writing to this file.\n";
  test_file.close();
  assert(!test_file.bad());
  
  std::unique_ptr<Error> error = 0;
  {
    LockedFile file_lock(file_name, error);
    test(!error, "File should lock ok.");
    test_file.open(file_name, std::ios::out);
    test_file << "Nothing";
    test_file.close();
    test(test_file.bad(), "Should not write correctly.");
  }
  test_file.open(file_name, std::ios::out);
  test_file << "";
  test_file.close();
  test(!test_file.bad(), "Should write correctly.");
}

//=============================================================================
void utest_LockedFile::test_file_exists()
{
  std::unique_ptr<Error> error = 0;
  LockedFile("data/test.txt", error);
  test(!error, "File should exist");
}

//=============================================================================
int main() {
  
  utest_LockedFile tester;
  tester.run_tests();
  return 0;
}
