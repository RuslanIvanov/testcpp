CCCC = g++
#CCCC:=../../../builds/x86_cPCI-3965/buildroot-2017.02/output/host/usr/bin/i686-buildroot-linux-uclibc-g++
#CCCC:= ../../../builds/buildroot_tam3517_upum6/buildroot-2013.05/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-g++

LIBS = -lpthread  -lrt 

CFLAGS=-c -Wall
LDFLAGS=

SOURCES=\
main.cpp\
c_finddev.cpp\
c_event.cpp\
c_data.cpp\
c_ethernet.cpp\
c_timer.cpp\
c_timersys.cpp\
c_log.cpp\

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/upu_answ

huwbuild: $(EXECUTABLE)
all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CCCC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CCCC) $(CFLAGS) $< -o $@  -MD $(LIBS)
	
#include $($(SOURCES).d)
include $(wildcard *.d)

install:
	#cp $(EXECUTABLE)  /usr/bin/$(EXECUTABLE)
	cp $(EXECUTABLE)  ../../output/target/usr/bin/$(EXECUTABLE)

uninstall:
	#rm -f /usr/bin/$(EXECUTABLE)
	rm -f ../../output/target/usr/bin/$(EXECUTABLE)
clean:
	rm -f *.o $(EXECUTABLE) *.d *~ ./bin/*~
