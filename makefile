
#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build static lib 'libinireader.a'
# 'make clean'  removes all .o and static lib files
#

# define the C compiler to use
#CC = gcc
CC = @echo


# define any compile-time flags
#CFLAGS = -c

# define any archive (static lib) flags
#ARFLAGS=rv

# define any directories containing header files other than /usr/include
#INCLUDES =-ICore/include -I../Utils/include

# define library paths in addition to /usr/lib
#   specify path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib

# define the CPP source files
SRCS =		\
	x.cpp	\
	y.cpp	\
	X/a.cpp	\
	X/b.cpp
	



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

MAC2= mac2

# define the static lib file 
ST_LIB = $(LIBDIR)/libMRTest.a

# The following part of the makefile is generic; it can be used to 
# build any static lib just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
.PHONY: depend clean

#all:
all:    $(ST_LIB)
	@echo  Simple compiler named libutils.a has been compiled

# rule to archive all of the object files into the static lib
# chains to the OBJS macro which calls the .cpp.o to do the compilation first.
$(ST_LIB): $(MAC2)
	@echo $(ST_LIB) target rules
#	@echo $(SRCS)
#	@echo $(SRCS:.cpp=.o)
#	@echo $<  -o $@


#$(MAC2): $(SRCS:.cpp=.o)
#	@echo $(MAC2) target rules
#	@echo vars less=$<  at=$@   Question=$?  percent=$%   carret=$^   asterix=$*
#	@echo $@ $?


#$(MAC2):
#	@echo $(MAC2) target rules - for each loop
#	$(foreach i,$(SRCS:.cpp=),  \
#		@echo compile $i.cpp to $i.o  \n  \
#	 )
	

$(MAC2):
	@echo $(MAC2) target rules - for each loop
	$(foreach i,$(SRCS:.cpp=),						\
		$(shell echo $i.cpp to $i.o > /dev/stderr)	\
	 )


#$(MAC2):
#	@echo $(MAC2) target rules - for each loop
#	$(foreach i,$(SRCS:.cpp=),							\
#		$(if $($i)										\
#			,$(shell echo $i.cpp to $i.o > /dev/stderr)	\
#			,$(shell echo No value in i=$(i) > /dev/stderr)	\
#		)												\
#	 )




	
#	@echo Prerequisite=$<  Target=$@   Whatever=$?
#	@echo vars less=$<  at=$@   Question=$?  percent=$%   carret=$^   asterix=$*
#	@echo $@ $?





#	@echo $(ST_LIB) target rules
#	@echo $@ $?


#$(ST_LIB): $(OBJS) 
#	mkdir -p $(LIBDIR)
#	$(AR) $(ARFLAGS) $@ $?


# this is a suffix replacement rule for building .o's from .cpp's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#.cpp.o:
#	@echo cpp o replacement rules
#	@echo $<  -o $@
#	@echo Prerequisite=$<  Target=$@   Whatever=$?
#	@echo vars less=$<  at=$@   Question=$?  percent=$%   carret=$^   asterix=$*

	
#	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	@echo $(ST_LIB) clean rules
	$(RM) $(OBJNAMES)
	$(RM) *~ $(ST_LIB)


depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
