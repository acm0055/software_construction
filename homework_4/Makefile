CXX = g++
CXXFLAGS = -g -std=c++0x
objects = file_merger.o test.o

all: $(objects) hw4.o
	$(CXX) $(CXXFLAGS) -o hw4 $(objects) hw4.o
test_drv: $(objects) test_drv.o
	$(CXX) $(CXXFLAGS) -o test_drv $(objects) test_drv.o
test_drv.o: test_drv.cpp
file_merger.o: file_merger.cpp
test.o: test.cpp

.PHONY: clean
clean:
	rm *.o hw4 test_drv
