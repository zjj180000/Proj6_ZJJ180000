 # Filename     Makefile
 # Date         4/30/2020
 # Author       Zachary James Jackson
 # Email        ZJJ180000@utdallas.edu
 # Course       CS 3377.501 Spring 2020
 # Version      1.0
 # Copyright    2020, All Rights Reserved
 #
 # Description
 #
 # Makefile to compile the project

CXX = g++ -std=c++11
CXXFLAGS =
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

# Executable Name
EXECFILE = display

# Auto include all .cc files
SOURCES := $(wildcard *.cc)
OBJS = $(SOURCES:.cc=.o)

# Rely on implicit rules for compilation

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

