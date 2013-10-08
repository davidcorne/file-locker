mkdir -p obj exe
cl /EHsc /c /Tp Error.h /Foobj/Error.obj
cl /EHsc /c /Tp PathNotFoundError.h /Foobj/PathNotFoundError.obj
cl /EHsc /c /Tp LockedFile.h /Foobj/LockedFile.obj
cl /EHsc utest.cpp /Foobj/utest.obj /Feexe/utest.exe