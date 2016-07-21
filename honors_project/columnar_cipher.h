#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include "crypto_method.h"

//Implements a columnar cipher.
//Adheres to the crypto_method interface.
class columnar_cipher : public crypto_method {
 private:
  char SENTINAL = '\a';  
  int key_length;
  std::vector<int> order;

  //Initializes the order transform
  //for the columns of the message
  //based on the key.
  //IE: assigns numbers on the basis
  //    of their character
  //    code size in order;
  //    less - lower number
  //    greater - higher number
  void init_order();
  //Turns the message into columns
  //for rearraging based on
  //the order of the key.
  //Input: message - message to columnize
  //Output: columnized message
  std::vector<std::string> columnize(const std::string& message);
  //The columnar cipher is a symmetric cipher
  //on the basis of the order of the columns.
  //This method implements this symmetric coding.
  //Input: message to symmetric code
  //Output: symmetric coded message
  std::string symmetric_codify(const std::string& message);
 public:
  //Constructs a columnar cipher
  //based on a key. Initializes the
  //order of the encryption based on
  //the key and stores the key_lenght.
  columnar_cipher(std::string key);
  //does nothing
  ~columnar_cipher();
  //Interface for crpto_method.
  //Just calls the symmetric_codify method.
  std::string encrypt(const std::string& message);
  //Interface for crpto_method.
  //Just calls the symmetric_codify method.
  std::string decrypt(const std::string& message);
};
