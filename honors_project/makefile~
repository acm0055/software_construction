CXX = g++
CXXFLAGS = -g -std=c++11
objects = columnar_cipher.o vigenere_cipher.o crypto_buffer.o

all : $(objects) honors.o test
	$(CXX) $(CXXFLAGS) -o honors $(objects) honors.o
test : $(objects) test.o
	$(CXX) $(CXXFLAGS) -o test $(objects) test.o
honors.o : honors.cpp
test.o : test.cpp
columnar_cipher.o : columnar_cipher.cpp crypto_method.h
vigenere_cipher.o : vigenere_cipher.cpp crypto_method.h
crypto_buffer.o : crypto_buffer.cpp
clean:
	rm -rf *.o honors
