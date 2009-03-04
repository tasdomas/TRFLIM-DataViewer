COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = fileformat.o sdt.o

all: $(objects) 
    
fileformat.o: fileformat.cc

sdt.o : sdt.cc

clean:
	rm $(objects)
