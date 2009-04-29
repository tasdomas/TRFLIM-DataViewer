#CXX = g++
CXX = i586-mingw32msvc-g++

#WX_LIBS = $(shell wx-config --libs)
#WX_CXXFLAGS = -W -Wall -g $(shell wx-config --cxxflags)
WX_LIBS = $(shell /usr/local/wx-2.8.9-mingw32/bin/wx-config --libs)
WX_CXXFLAGS = -W -Wall -g $(shell /usr/local/wx-2.8.9-mingw32/bin/wx-config --cxxflags)

INCLUDES = 

OBJECTS = mathplot.o

# implementation

objects: $(OBJECTS)

.SUFFIXES:      .o .cpp

.cpp.o :
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(OBJECTS)


