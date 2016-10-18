# This specifies which C++ compiler to use
CC = g++
#
# #This specifies what c-flags I want during compilation
# CFLAGS = -g -Wall $(INCLUDES)
CFLAGS = -std=c++11
#

prog_out: main.cc readscene.cc
	g++ -g *.cc -I. -I/usr/include/OpenEXR -I/usr/local/include/OpenEXR -lIlmImf -lImath -lHalf -lpthread -lm -lrt -Wall -std=c++11 -o prog_out 

#.PHONY: main
#main:
#	$(CC) $(CFLAGS) readscene.cpp *.cc

#Need to make sure make knows clean and all are not file namesl
.PHONY: clean
clean:
	rm -f *.o a.out prog_out *.exr

.PHONY: all
all: clean prog_out 

