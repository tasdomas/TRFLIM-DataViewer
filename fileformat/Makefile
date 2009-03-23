COMPILER = g++
#COMPILER = i586-mingw32msvc-gcc
CCFLAGS = -g -ansi -W -Wall
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fileformat.o sdt.o datablock.o

all: $(objects) 

datablock.o: datablock.cc

fileformat.o: fileformat.cc

sdt.o : sdt.cc

clean:
	rm $(objects)
