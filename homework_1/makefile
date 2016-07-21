CXX = g++
CXXFLAGS = -std=c++11
objects = hw1.o

main: $(objects)
	$(CXX) $(CXXFLAGS) -o main $(objects)

hw1.o : hw1.cpp
	$(CXX) $(CXXFLAGS) -c src/hw1.cpp

.PHONY : clean
clean :
	rm main $(objects)
