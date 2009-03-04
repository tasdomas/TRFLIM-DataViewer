COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fileformat.o

all: $(objects) 
    
fileformat.o: fileformat.cc

clean:
	rm $(objects)
