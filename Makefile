COMPILER = g++
#COMPILER = i586-mingw32msvc-g++

CCFLAGS = -g -ansi -W -Wall
LIBFLAGS = -lm --libdir=/usr/local/i586-mingw32/lib

WX_LIBS = $(shell wx-config --libs)
WX_CXXFLAGS = $(shell wx-config --cxxflags)
#WX_LIBS = $(shell /usr/local/wx-2.8.9-mingw32/bin/wx-config --libs)
#WX_CXXFLAGS = $(shell /usr/local/wx-2.8.9-mingw32/bin/wx-config --cxxflags)



LIBRARIES = main/ fileformat/ ui/ lib/ include/newmat/ include/wxMathPlot include/lmfit

FILEFORMAT_OBJECTS = fileformat/fileformat.o fileformat/sdt.o fileformat/datablock.o fileformat/simplesdt.o fileformat/simpleblock.o

MAIN_OBJECTS = main/main.o

INCLUDE_OBJECTS = include/newmat/libnewmat.a include/wxMathPlot/mathplot.o include/lmfit/lmmin.o include/lmfit/lm_eval.o

LIB_OBJECTS = lib/fwhmblock.o lib/exception.o lib/componentblock.o lib/fitter.o lib/svdblock.o

UI_OBJECTS = ui/canvas.o ui/main_frame.o ui/datapanel.o ui/imagepanel.o ui/scaleframe.o ui/grayscalepanel.o ui/componentspanel.o ui/compdialog.o ui/graphdialog.o ui/marginsdialog.o ui/svdpanel.o

OBJECTS = $(FILEFORMAT_OBJECTS) $(UI_OBJECTS) $(LIB_OBJECTS) $(INCLUDE_OBJECTS)

.PHONY: all $(LIBRARIES)

%.o : %.cc
	$(COMPILER) $(CCFLAGS) -c $<

all: test

test: $(LIBRARIES) 
	$(COMPILER) $(LIBFLAGS) -o $@ $(FILEFORMAT_OBJECTS) main/main.o

dv: $(LIBRARIES)
	$(COMPILER) $(OBJECTS) ui/app.o $(WX_LIBS) $(LIBFLAGS) -o $@

test_app:  $(LIBRARIES)
	$(COMPILER) $(OBJECTS) ui/test_app.o $(WX_LIBS) $(LIBFLAGS) -o $@

$(LIBRARIES) :
	$(MAKE) --directory=$@
