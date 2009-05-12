COMPILER = g++
#COMPILER = i586-mingw32msvc-g++
CCFLAGS = -g -ansi -W -Wall
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fwhmblock.o exception.o componentblock.o fitter.o

all: $(objects) 

fitter.o: fitter.cc

fwhmblock.o: fwhmblock.cc

exception.o: exception.cc

componentblock.o: componentblock.cc

clean:
	rm $(objects)
