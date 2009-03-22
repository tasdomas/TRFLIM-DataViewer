COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = -lm

WX_LIBS = $(shell wx-config --libs)
WX_CXXFLAGS = $(shell wx-config --cxxflags)

LIBRARIES = main/ fileformat/ ui/ lib/

FILEFORMAT_OBJECTS = fileformat/fileformat.o fileformat/sdt.o fileformat/datablock.o

MAIN_OBJECTS = main/main.o

LIB_OBJECTS = lib/fwhmblock.o

UI_OBJECTS = ui/canvas.o ui/main_frame.o ui/datapanel.o ui/imagepanel.o ui/scaleframe.o

OBJECTS = $(FILEFORMAT_OBJECTS) $(UI_OBJECTS) $(LIB_OBJECTS)

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
