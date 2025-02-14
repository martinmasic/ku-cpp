CC = clang++
CFLAGS = -std=c++23 -Wall -pedantic

test: generator.o
	$(CC) $(CFLAGS) -o ./bin/test ./src/generator.o ./src/test.cpp

generator.o: ./src/generator.cpp
	$(CC) $(CFLAGS) -o ./src/generator.o -c ./src/generator.cpp

clean:
	rm -f ./src/*.o ./bin/*

