CCCC = g++ --std=c++17
#CCCC = g++

LIBS = -lpthread  -lrt \

CFLAGS=-c -Wall
LDFLAGS=

SOURCES= \
queueTh.cpp \

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
