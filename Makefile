# This specifies which C++ compiler to use
CC = g++
#
# #This specifies what c-flags I want during compilation
# CFLAGS = -g -Wall $(INCLUDES)
CFLAGS = -std=c++11
#

hw1: readscene.cpp
	g++ -std=c++11 -g readscene.cpp *.cc -I. -I/usr/include/OpenEXR -I/usr/local/include/OpenEXR -lIlmImf -lImath -lHalf -L/usr/local/lib -Wall -o hw1

#.PHONY: main
#main:
#	$(CC) $(CFLAGS) readscene.cpp *.cc

#Need to make sure make knows clean and all are not file namesl
.PHONY: clean
clean:
	rm -f *.o a.out hw1 hw1.exr

.PHONY: all
all: clean main 

