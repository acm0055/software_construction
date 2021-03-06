#include <iostream>
#include <string>
#include <memory>
#include "crypto_method.h"

#ifndef CRYPTO_ENGINE
#define CRYPTO_ENGINE 1
namespace crypto_engine {
  class crypto_buffer {
    friend std::ostream& crypto_engine::operator<<(std::ostream& other, const crypto_buffer& input);
  public:
    crypto_buffer();
    ~crypto_buffer();
    
    void encrypt(std::string message, crypto_method* encryption_method);
    void decrypt(std::string message, crypto_method* decryption_method);
    std::string& get_buffer() {
      return buffer;
    }
  private:
    std::string buffer;
  };
  
  bool is_valid_character(char check);
  crypto_method* generate_crypto_object(char method, std::string key);
  std::ostream& operator<<(std::ostream& other, const crypto_buffer& self);
}
#endif
