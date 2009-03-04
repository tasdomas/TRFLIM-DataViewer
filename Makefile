COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

LIBRARIES = main/ fileformat/

FILEFORMAT_OBJECTS = fileformat/fileformat.o fileformat/sdt.o

MAIN_OBJECTS = main/main.o

OBJECTS = $(FILEFORMAT_OBJECTS) $(MAIN_OBJECTS)

.PHONY: all $(LIBRARIES)

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

all: test

test: $(LIBRARIES) 
	$(COMPILER) $(LIBFLAGS) -o $@ $(OBJECTS)

$(LIBRARIES) :
	$(MAKE) --directory=$@
