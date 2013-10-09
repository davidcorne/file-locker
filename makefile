CC = cl
CC_OPTS = /I. /EHsc /Zi

#==============================================================================
exe/utest.exe: \
        obj/utest.obj \
        obj/LockedFile.obj \
        obj/Error.obj \
        obj/PathNotFoundError.obj
	@mkdir -p exe
	$(CC) $(CC_OPTS) $^ /Fe$@

#==============================================================================
obj/utest.obj: utest/utest.cpp test_area
	@mkdir -p obj
	$(CC) $(CC_OPTS) /c $< /Fo$@

#==============================================================================
obj/%.obj: source/%.cpp LockedFile/%.h
	@mkdir -p obj
	$(CC) $(CC_OPTS) /c $< /Fo$@

#==============================================================================
test_area:
# Make the temporary test files area
	@mkdir -p $@

#==============================================================================
clean:
	@rm -r obj exe
	@echo "Removing object and executable files."
