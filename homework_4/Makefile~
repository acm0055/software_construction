CXX = g++
CXXFLAGS = -g -std=c++0x
objects = puzzler_shooting_gallery.o test.o

all: $(objects) hw3.o
	$(CXX) $(CXXFLAGS) -o hw3 $(objects) hw3.o
test_puzzler: $(objects)
	$(CXX) $(CXXFLAGS) -o test_puzzler $(objects)
hw3.o: hw3.cpp
puzzler_shooting_gallery.o: puzzler_shooting_gallery.cpp
test.o: test.cpp

.PHONY: clean
clean:
	rm hw3 $(objects) hw3.o
