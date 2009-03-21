COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fwhmblock.o

all: $(objects) 

fwhmblock.o: fwhmblock.cc

clean:
	rm $(objects)
