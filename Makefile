# Makefile for CpSc 360 Project 4

SRCS := $(wildcard *.cpp)

.cpp.o:
	g++ -g -c -Wall $<

all: httpproxy

httpproxy: httpproxy.o proxy.o startup.o common.o
	g++ -g -o httpproxy $^

clean:
	rm *.o
	rm httpproxy

depend: $(SRCS)
	makedepend $(INCLUDES) $^

httpproxy.o: common.h proxy.h startup.h httpproxy.h
