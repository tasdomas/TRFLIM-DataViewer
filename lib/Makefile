#COMPILER = g++
COMPILER = i586-mingw32msvc-g++
CCFLAGS = -g -ansi -W -Wall
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fwhmblock.o exception.o componentblock.o

all: $(objects) 

fwhmblock.o: fwhmblock.cc

exception.o: exception.cc

componentblock.o: componentblock.cc

clean:
	rm $(objects)
