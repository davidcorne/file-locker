//=============================================================================
//
// 

#include <assert.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

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
    test_file_deletion();
  }

private:

  void test_non_existant_file();
  void test_file_deletion();
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
  
  void print(std::string message) {
    std::string banner(
      "========================================"
      "=======================================\n"
    );
    std::cout << "\n" << banner <<  message << "\n" << banner << std::endl;
  }

};

//=============================================================================
void utest_LockedFile::test_non_existant_file()
{
  print(__FUNCTION__);
  std::unique_ptr<Error> error = 0;
  LockedFile("non_existant.txt", error);
  test(error, "File should not exist");
}

//=============================================================================
void utest_LockedFile::test_file_deletion()
{
  print(__FUNCTION__);
  std::string path("test_area/test_file_deletion");
  std::ofstream test_file;
  test_file.open(path, std::ios::out);
  test_file << "Writing to this file.\n";
  test_file.close();
  assert(!test_file.bad());
  
  int remove_result = 0;
  {
    std::unique_ptr<Error> error = 0;
    LockedFile file_lock(path, error);
    test(!error, "Should be no error");
    remove_result = remove(path.c_str());
    test(remove_result != 0, "Should not be able to delete locked file.");
  }
  remove_result = remove(path.c_str());
  test(remove_result == 0, "File shouldn't be locked any more.");
}

//=============================================================================
void utest_LockedFile::test_file_locks()
{
  print(__FUNCTION__);
  std::string file_name("test_area/test_file_locks.txt");
  std::ofstream test_file;
  test_file.open(file_name, std::ios::out);
  test_file << "Writing to this file.\n";
  test_file.close();
  assert(!test_file.bad());
  
  {
    std::unique_ptr<Error> error = 0;
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
  int remove_result = remove(file_name.c_str());
  assert(remove_result == 0);
}

//=============================================================================
void utest_LockedFile::test_file_exists()
{
  print(__FUNCTION__);
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
