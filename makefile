CXX = clang++
# CC = zig c++
CXXLAGS = -std=c++23 -Wall -pedantic

test: generator.o
	$(CXX) $(CXXLAGS) -o ./bin/test ./src/generator.o ./src/test.cpp

generator.o: ./src/generator.cpp
	$(CXX) $(CXXLAGS) -o ./src/generator.o -c ./src/generator.cpp

clean:
	rm -f ./src/*.o ./bin/*

