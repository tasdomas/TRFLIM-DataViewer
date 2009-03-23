#COMPILER = g++
COMPILER = i586-mingw32msvc-g++
CCFLAGS = -g -ansi -W -Wall
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fwhmblock.o

all: $(objects) 

fwhmblock.o: fwhmblock.cc

clean:
	rm $(objects)
