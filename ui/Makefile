CXX = g++
#CXX = i586-mingw32msvc-g++
PROGRAM = dv_ui

WX_LIBS = $(shell wx-config --libs)
WX_CXXFLAGS = -W -Wall -g $(shell wx-config --cxxflags)
#WX_LIBS = $(shell /usr/local/wx-2.8.9-mingw32/bin/wx-config --libs)
#WX_CXXFLAGS = -W -Wall -g $(shell /usr/local/wx-2.8.9-mingw32/bin/wx-config --cxxflags)

INCLUDES = 

OBJECTS = test_app.o app.o main_frame.o canvas.o datapanel.o imagepanel.o scaleframe.o grayscalepanel.o componentspanel.o compdialog.o graphdialog.o marginsdialog.o

# implementation

objects: $(OBJECTS)

.SUFFIXES:      .o .cpp

.cc.o :
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(OBJECTS) $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CXX) $(WX_LIBS) -o $(PROGRAM) $(OBJECTS) $(INCLUDES)
