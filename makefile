CC = cl
CC_OPTS = /I. /EHsc

#==============================================================================
exe/utest.exe: \
        utest/utest.cpp \
        obj/LockedFile.obj \
        obj/Error.obj \
        obj/PathNotFoundError.obj 
	$(CC) $(CC_OPTS) $^ /Fe$@

#==============================================================================
obj/%.obj: source/%.cpp LockedFile/%.h
	$(CC) $(CC_OPTS) /c $< /Fo$@
