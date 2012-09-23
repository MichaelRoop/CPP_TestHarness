
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

#CXXFLAGS+=-shared
#CXXFLAGS+=-W1


# define any directories containing header files other than /usr/include
INCLUDES =-Iinclude

# define library paths in addition to /usr/lib
#   specify path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib

# define the CPP source files
SRCS = \
	source/mr_exception.cpp							\
	source/mr_singleton.cpp							\
	source/mr_sstream.cpp							\
	source/mr_string.cpp							\
	source/mr_staticTimer.cpp						\
	source/exceptions/mr_fileException.cpp			\
	source/exceptions/mr_pointerException.cpp		\
	source/IniReader/mr_ini_node.cpp				\
	source/IniReader/mr_ini_section.cpp				\
	source/IniReader/mr_iniInputLine.cpp			\
	source/IniReader/mr_ini_file.cpp				\


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

#until I can get groups and rights setup
LIBOPTDIR=/opt/cut_test/lib


# define the static lib file 
LIBNAME=libcut_utils.so
UTILLIB = $(LIBDIR)/$(LIBNAME)


DEFINES=-DCPPTESTUTILS_EXPORTS
DEFINES+=-DMR_USE_WIDE_STR

# User defined function for compile to make for each compact. 
do-compile=$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $1.cpp -o $1.o > stderr

# The following part of the makefile is generic; it can be used to 
# build any static lib just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
.PHONY: depend clean

all: $(UTILLIB)
	@echo  Simple compiler named libutils.so has been compiled


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
	@echo
	@echo ------------------------------------------------------------
	@echo Creating Shared Object
#	ld -shared -soname $@ -o $@ $(OBJS)
	$(CC) -shared -W1,-soname,$@.1 -o $@.1.0 $(OBJS)
	#$(CC) $(CXXFLAGS)-soname $@.1 -o $@.1.0 $(OBJS)
	@echo ------------------------------------------------------------


#	$(CC) $(CXXFLAGS),-soname, $@.1 -o $@.1.0 $(OBJS)
#	$(CC) $(CXXFLAGS),-soname, $@.1 -o $@.1.0 $(OBJS)



	mkdir -p $(LIBOPTDIR)
	mv $@.1.0 $(LIBOPTDIR)
	ln -sf $(LIBOPTDIR)/$(LIBNAME).1.0 $(LIBOPTDIR)/$(LIBNAME)
	ln -sf $(LIBOPTDIR)/$(LIBNAME).1.0 $(LIBOPTDIR)/$(LIBNAME).1




#	ld -shared -soname $@ -o $@ $(OBJS)

	@echo ------------------------------------------------------------






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
	$(RM) $(LIBOPTDIR)/$(LIBNAME)
	$(RM) $(LIBOPTDIR)/$(LIBNAME).1
	$(RM) $(LIBOPTDIR)/$(LIBNAME).1.0



depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
