#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include "crypto_method.h"

//Implements a vigenere cipher.
//Adheres to the crypto_method interface.
class vigenere_cipher : public crypto_method {
 private:
  //Method for performing a special case
  //proper mathematical modulus
  //for the encrypt and decrypt functions.
  //input: num - number
  //       den - divisor
  //output: remainder
  //       -Since using this is a special
  //        case for characters char is
  //        guarenteed to hold the result
  //        of the operation.
  char proper_mod(int num, int den);
 public:
  //Constructs a vigenere cipher from
  //a password.
  //Input: key - password for encryption/decryption
  vigenere_cipher(std::string key);
  //do nothing
  ~vigenere_cipher();
  //Encrypts by the modulo definition of
  //the vigenere cipher. This is evident
  //by the shifting nature of the cipher.
  //On most systems, the guarentee of the
  //password characters keeps the value in
  //an appropriate range for shifting.
  //Input: message - message to encrypt
  //Output: encrypted message
  std::string encrypt(const std::string& message);
  //Decrypts by a reformulation
  //of the modulo definition of
  //the vigenere cipher for encryption.
  //This is evident by the shifting nature of the cipher.
  //On most systems, the guarentee of the
  //password characters keeps the value in
  //an appropriate range for shifting.
  //Input: message - message to decrypt
  //Output: decrypted (with right password) message
  std::string decrypt(const std::string& message);
};
