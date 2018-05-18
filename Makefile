CC=g++
CXXFLAGS=-g -std=c++11

OBJS = main.cpp

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o P7 ${OBJS}

	
clean:
	rm -rf src/*.o 
