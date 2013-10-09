# Locked File #

## Purpose ##

This is a project to get a good RAII class for locking a file for reading and writing. This is implemented in C++.

## Contents ##

The main class in this repository is LockedFile, there are also supporting error classes and a unit test.

## Implementation Details ##

This repository is indended to be built using make and the Microsoft C++ compiler. This repository currently only works on windows.

### Running Tests ###

The entire project is built and the test run, by typing 

    make test

This should give output which looks like this.

```
===============================================================================
utest_LockedFile::test_file_exists
===============================================================================

Pass: File should exist

===============================================================================
utest_LockedFile::test_non_existant_file
===============================================================================

Pass: File should not exist
Pass: This is not PathNotFoundError

===============================================================================
utest_LockedFile::test_file_write_lock
===============================================================================

Pass: File should lock ok.
Pass: Should not write correctly.
Pass: Should write correctly.

===============================================================================
utest_LockedFile::test_file_deletion
===============================================================================

Pass: Should be no error from LockedFile
Pass: Should not be able to delete locked file.
Pass: File shouldn't be locked any more.

===============================================================================
utest_LockedFile::test_nested_locks
===============================================================================

Pass: First lock should work.
Pass: Second lock should not work.
Pass: This is not FileInUseError
Pass: Third lock should work.
```
