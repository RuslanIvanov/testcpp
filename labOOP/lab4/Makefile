CCCC = g++ --std=c++11

LIBS = -lpthread  -lrt \

CFLAGS=-c -Wall
LDFLAGS=

SOURCES= \
Circle.cpp \
List.cpp \
main.cpp \
Node.cpp \
Point.cpp \
Shape.cpp \

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=./run.exe

huwbuild: $(EXECUTABLE)
all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CCCC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CCCC) $(CFLAGS) $< -o $@  -MD $(LIBS)
	
#include $($(SOURCES).d)
include $(wildcard *.d)

install:
	cp $(EXECUTABLE)  ./$(EXECUTABLE)

uninstall:
	rm -f ./$(EXECUTABLE)
clean:
	rm -f *.o $(EXECUTABLE) *.d
	rm -f *~
