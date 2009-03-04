COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

objects = main.o

all: $(objects)
    
main.o: main.cc

clean:
	rm $(objects)
