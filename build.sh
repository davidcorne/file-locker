#!/bin/sh
# Written by: DGC

set -x
mkdir -p obj exe
cl /I. /EHsc /c source/Error.cpp /Foobj/Error.obj
cl /I. /EHsc /c source/PathNotFoundError.cpp /Foobj/PathNotFoundError.obj
cl /I. /EHsc /c source/LockedFile.cpp /Foobj/LockedFile.obj
cl /I. /EHsc utest/utest.cpp obj/LockedFile.obj obj/PathNotFoundError.obj obj/Error.obj /Feexe/utest.exe