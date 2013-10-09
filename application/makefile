CC = cl
CC_OPTS = /I.. /EHsc
OBJECTS = \
  ../obj/LockedFile.obj \
  ../obj/Error.obj \
  ../obj/PathNotFoundError.obj \
  ../obj/FileInUseError.obj \
  ../obj/WindowsError.obj

#==============================================================================
exe/file_locker.exe: obj/main.obj $(OBJECTS)
	@mkdir -p exe
	$(CC) $(CC_OPTS) $^ /Fe$@

#==============================================================================
obj/main.obj: source/main.cpp $(OBJECTS)
	@mkdir -p obj
	$(CC) $(CC_OPTS) $^ /Fo$@

#==============================================================================
clean:
	@$(RM) -r exe
	@echo "Removing executable files."

