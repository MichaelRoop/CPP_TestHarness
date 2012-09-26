
#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build static lib 'libinireader.a'
# 'make clean'  removes all .o and static lib files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -c

# define any archive (static lib) flags
ARFLAGS=rv

# define any directories containing header files other than /usr/include
INCLUDES =-ICore/include -I../Utils/include

# define library paths in addition to /usr/lib
#   specify path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib

# define the CPP source files
SRCS = \
	Core/source/mr_case.cpp							\
	Core/source/mr_compareFunctions.cpp				\
	Core/source/mr_fileOutput.cpp					\
	Core/source/mr_fileScriptReader.cpp				\
	Core/source/mr_simpleLogger.cpp					\
	Core/source/mr_testEngine.cpp					\
	Core/source/mr_testInfoObject.cpp				\
	Core/source/mr_testLogEngine.cpp				\
	Core/source/mr_testLogger.cpp					\
	Core/source/mr_verboseLogger.cpp				\
	Core/source/Exceptions/mr_scriptException.cpp	\
	Core/source/LogOutputs/mr_consoleOutput.cpp	



# define the CPP object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .cpp of all words in the macro SRCS
# with the .o suffix
OBJS = $(SRCS:.cpp=.o)


# generate object names without compile
OBJNAMES = $(SRCS:.cpp=.o)

#folder for lib file.
LIBDIR = lib


# define the static lib file 
ST_LIB = $(LIBDIR)/libMRTest.a

# The following part of the makefile is generic; it can be used to 
# build any static lib just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
.PHONY: depend clean

all:    $(ST_LIB)
	@echo  Simple compiler named libutils.a has been compiled

# rule to archive all of the object files into the static lib
# chains to the OBJS macro which calls the .cpp.o to do the compilation first.
$(ST_LIB): $(OBJS) 
	mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $?


# this is a suffix replacement rule for building .o's from .cpp's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) $(OBJNAMES)
	$(RM) *~ $(ST_LIB)


depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
