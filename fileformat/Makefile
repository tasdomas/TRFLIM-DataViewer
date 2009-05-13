COMPILER = g++
#COMPILER = i586-mingw32msvc-g++
CCFLAGS = -g -ansi -W -Wall
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fileformat.o sdt.o datablock.o simpleblock.o simplesdt.o

all: $(objects) 

simpleblock.o: simpleblock.cc

simplesdt.o: simplesdt.cc

datablock.o: datablock.cc

fileformat.o: fileformat.cc

sdt.o : sdt.cc

clean:
	rm $(objects)
