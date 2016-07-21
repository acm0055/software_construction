#include <string>
#include <memory>

#ifndef CRYPTO_METHOD
#define CRYPTO_METHOD 1
class crypto_method {
 protected:
  std::string key;
 public:
  //Constructs crypto_method using a password.
  //input: user_key - password for encryption
  crypto_method(std::string user_key)
    : key{user_key}
  {};
  //does nothing
  virtual ~crypto_method() {};
  //interface for encrypting
  virtual std::string encrypt(const std::string& message)=0;
  //interface for decrypting
  virtual std::string decrypt(const std::string& message)=0;
};
#endif
