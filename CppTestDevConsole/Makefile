
#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build static lib 'libutils.a'
# 'make clean'  removes all .o and static lib files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -c
CFLAGS += -fPIC
CFLAGS += -fno-stack-protector

# define any directories containing header files other than /usr/include
INCLUDES +=-I../CppTestUtils/include
INCLUDES +=-I../CppTest/include
INCLUDES +=-I../CppTest/Core/include


# define library paths in addition to /usr/lib
#   specify path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib

# define the CPP source files
SRCS = \
	source/CppTestDevConsole.cpp							\



# define the CPP object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .cpp of all words in the macro SRCS
# with the .o suffix
OBJS = $(SRCS:.cpp=.o)

# folder for lib file.
LIBDIR = lib

# define the shared object file
UTILLIB = $(LIBDIR)/cutConsoleRunner

# the libs from the other Cut so
#LIBS+=-lstdc++
#LIBS+=-lcut_utils
#LIBS+=-ldl
#LIBS+=-lcut_test


LIBS+=-lcut_test
LIBS+=-lcut_utils
LIBS+=-ldl
LIBS+=-lstdc++




#until I can get groups and rights setup
#LIBDIRS+=-L/home/michael/opt/cut_test/lib
#LIBDIRS+=-L/usr/lib/gcc/i686-linux-gnu/4.6.3
LIBDIRS+=-L/usr/lib/gcc/i686-linux-gnu/4.6.3/
LIBDIRS+=-L/opt/cut_test/lib/




DEFINES+=-DMR_USE_WIDE_STR
DEFINES+=-DDEBUG

# User defined function for compile to make for each compact. 
do-compile=$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $1.cpp -o $1.o > stderr

#do-compile=$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $1.cpp -o $1.o > stderr


# The following part of the makefile is generic; it can be used to 
# build any static lib just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
.PHONY: depend clean

all: $(UTILLIB)
	@echo  Simple compiler named ConsoleRunner has been compiled


# rule to archive all of the object files into the static lib
# chains to the OBJS macro which calls the .cpp.o to do the compilation first.
# For some reason gcc does not send out text to stdout of stderr.  Must echo
# it
$(UTILLIB): $(SRCS) 
	
	mkdir -p $(LIBDIR)

	@echo ------------------------------------------------------------
	@echo Compiling object files.
	$(foreach i,$(SRCS:.cpp=),$(shell $(call do-compile,$i) ))
	@echo ------------------------------------------------------------

	@echo ------------------------------------------------------------
	@echo Objects $(OBJS)
	@echo Libs $(LIBS)
	@echo ------------------------------------------------------------

	@echo ------------------------------------------------------------
	@echo Linking into executable
#	ld -o $@ $(OBJS) $(LIBDIRS) $(LIBS)

#	$(CC) -o $@ $(OBJS) $(LIBDIRS) $(LIBS)
	$(CC) $(OBJS) $(LIBDIRS) $(LIBS) -o $@



	@echo ------------------------------------------------------------


#$(LDFLAGS) $(CUT_LIBS)


#	@echo ------------------------------------------------------------
#	@echo Creating Shared Object
#	ld -shared -soname $@ -o $@ $(OBJS)
#	@echo ------------------------------------------------------------


#	ld -shared -soname $@ -o $@ /usr/lib/gcc/i686-linux-gnu/4.6.3/libgcc_s.so -lc -fno-stack-protector $(OBJS)
#	ld -shared -fno-stack-protector -soname $@ -o $@  $(OBJS)
#ld -shared -lc -fno-stack-protector -soname $@ -o $@  $(OBJS)


# TODO - lookup what the no-stack-protector might be doing

# this is a suffix replacement rule for building .o's from .cpp's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#.cpp.o:
#	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	@echo ------------------------------------------------------------
	@echo Cleaning House
	@echo ------------------------------------------------------------
	$(RM) $(UTILLIB)
	$(RM) $(OBJS)


depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
