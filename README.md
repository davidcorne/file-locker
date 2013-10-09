# Locked File #

## Purpose ##

This is a project to get a good RAII class for locking a file for reading and writing. This is implemented in C++.

### The Purpose of Locking Files ###

The main use of file locking is to stop someone writing to a file between you reading it and writing it back out changed. It also becomes important implementing databases and websites.

## Contents ##

The main class in this repository is LockedFile, there are also supporting error classes and a unit test.

## Application ##

There is a sample application which will lock the files you give it on the command line.

This is not that much use, but it shows what's going on.

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

## Implementation Problems ##

- The dependencies in the makefile are not well set up. Somethimes if you change a header you need to manually remake other files (or `make -B`) to get them to compile.
- The reading and writing in `LockedFile` says nothing about encoding.
