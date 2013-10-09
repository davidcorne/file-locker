CC = cl
CC_OPTS = /I. /EHsc

#==============================================================================
exe/utest.exe: \
        obj/utest.obj \
        obj/LockedFile.obj \
        obj/Error.obj \
        obj/PathNotFoundError.obj 
	$(CC) $(CC_OPTS) $^ /Fe$@

#==============================================================================
obj/utest.obj: utest/utest.cpp
	$(CC) $(CC_OPTS) /c $< /Fo$@

#==============================================================================
obj/%.obj: source/%.cpp LockedFile/%.h
	$(CC) $(CC_OPTS) /c $< /Fo$@
