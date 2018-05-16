CC=g++
CXXFLAGS=-g 

OBJS = src/main.cpp

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o P7 ${OBJS}

	
clean:
	rm -rf src/*.o 