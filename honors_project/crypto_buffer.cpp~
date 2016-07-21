#include <iostream>
#include <string>
#include "vigenere_cipher.h"
#include "columnar_cipher.h"
#include "crypto_buffer.h"
#include "crypto_method.h"
using namespace std;
using namespace crypto_engine;

crypto_buffer::crypto_buffer()
  :buffer{}
{
  //do nothing
}

crypto_buffer::~crypto_buffer() {
  //do nothing
}

void crypto_buffer::encrypt(string message, crypto_method* encryption_method) {
  buffer = encryption_method->encrypt(message);
}

void crypto_buffer::decrypt(string message, crypto_method* decryption_method) {
  buffer = decryption_method->decrypt(message);
}

bool crypto_engine::is_valid_character(char check) {
  switch(check) {
  case 'a': case 'b': case 'c': case 'd':
  case 'e': case 'f': case 'g': case 'h':
  case 'i': case 'j': case 'k': case 'l':
  case 'm': case 'n': case 'o': case 'p':
  case 'q': case 'r': case 's': case 't':
  case 'u': case 'v': case 'w': case 'x':
  case 'y': case 'z': case 'A': case 'B':
  case 'C': case 'D': case 'E': case 'F':
  case 'G': case 'H': case 'I': case 'J':
  case 'K': case 'L': case 'M': case 'N':
  case 'O': case 'P': case 'Q': case 'R':
  case 'S': case 'T': case 'U': case 'V':
  case 'W': case 'X': case 'Y': case 'Z':
  case '0': case '1': case '2': case '3':
  case '4': case '5': case '6': case '7':
  case '8': case '9': case '_': case '/':
  case '\\': case '!': case '#': case '@':
  case '$': case '&': case '*': case '?':
    return true;
  default:
    return false;
  }
}

crypto_method* crypto_engine::generate_crypto_object(char method, string key) {
  
  switch (method) {
  case '1':
    return new columnar_cipher{key};
    break;
  case '2':
    return new vigenere_cipher{key};
    break;
  default:
    cerr << "Not a valid encryption type. Exiting." << endl;
    exit(1);
  }
}

//idiom from Bjarne Stroustrope p.94
//declaring it outside the class and making it a friend to fix compilation errors
//from http://stackoverflow.com/questions/10744787/operator-must-take-exactly-one-argument
ostream& crypto_engine::operator<<(ostream& other, const crypto_buffer& input) {
  return other << input.buffer;
}

