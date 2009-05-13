#COMPILER = g++
COMPILER = i586-mingw32msvc-g++
CCFLAGS = -c -g -ansi -W -Wall
LIBFLAGS = -lm

%.o : %.cc
	$(COMPILER) $(CCFLAGS) $(LIBFLAGS) -c $<

objects = lmmin.o lm_eval.o

all: $(objects) 

lm_eval.o: lm_eval.c

lmmin.o: lmmin.c

clean:
	rm $(objects)
