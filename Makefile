COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

WX_LIBS = $(shell wx-config --libs)
WX_CXXFLAGS = $(shell wx-config --cxxflags)

LIBRARIES = main/ fileformat/ ui/

FILEFORMAT_OBJECTS = fileformat/fileformat.o fileformat/sdt.o

MAIN_OBJECTS = main/main.o

UI_OBJECTS = ui/canvas.o ui/main_frame.o

OBJECTS = $(FILEFORMAT_OBJECTS) $(UI_OBJECTS)

.PHONY: all $(LIBRARIES)

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

all: test

test: $(LIBRARIES) 
	$(COMPILER) $(LIBFLAGS) -o $@ $(FILEFORMAT_OBJECTS) main/main.o

dv: $(LIBRARIES)
	$(COMPILER) $(WX_LIBS) $(LIBFLAGS) -o $@ $(OBJECTS) ui/app.o


$(LIBRARIES) :
	$(MAKE) --directory=$@
