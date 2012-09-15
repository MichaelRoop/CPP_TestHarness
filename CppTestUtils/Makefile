
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

# define any archive (static lib) flags
ARFLAGS=rv

# define any directories containing header files other than /usr/include
INCLUDES =-Iinclude

# define library paths in addition to /usr/lib
#   specify path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib

# define the CPP source files
SRCS = \
	source/mr_string.cpp							\
	source/mr_exception.cpp							\
	source/exceptions/mr_fileException.cpp			\
	source/exceptions/mr_pointerException.cpp		\
	source/mr_singleton.cpp							\
	source/mr_staticTimer.cpp

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

# define the static lib file 
UTILLIB = $(LIBDIR)/libutils.a


DEFINES=-DCPPTESTUTILS_EXPORTS
DEFINES+=-DMR_USE_WIDE_STR

# User defined function for compile to make for each compact. 
do-compile=$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $1.cpp -o $1.o > stderr

#do-compile=$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $1.cpp -o $1.o > stderr



# The following part of the makefile is generic; it can be used to 
# build any static lib just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
.PHONY: depend clean

all: $(UTILLIB)
	@echo  Simple compiler named libutils.a has been compiled


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
	@echo Creating lib
	$(AR) $(ARFLAGS) $@ $(OBJS)	
	@echo ------------------------------------------------------------


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
	@rm $(OBJS)
	@rm $(UTILLIB)
		#$(RM) $(OBJS)
		#$(RM) *~ $(UTILLIB)


depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
