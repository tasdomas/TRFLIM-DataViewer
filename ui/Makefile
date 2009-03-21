CXX = g++
PROGRAM = dv_ui
# wx-config --libs
WX_LIBS = $(shell wx-config --libs)
# wx-config --cxxflags
#
INCLUDES = 
WX_CXXFLAGS = -g $(shell wx-config --cxxflags)

OBJECTS = app.o main_frame.o canvas.o datapanel.o imagepanel.o

# implementation

objects: $(OBJECTS)

.SUFFIXES:      .o .cpp

.cc.o :
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(OBJECTS) $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CXX) $(WX_LIBS) -o $(PROGRAM) $(OBJECTS) $(INCLUDES)
