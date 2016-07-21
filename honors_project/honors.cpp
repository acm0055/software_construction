#include <iostream>
#include <cstring>
#include <fstream>
#include "crypto_method.h"
#include "crypto_buffer.h"
using namespace std;

void validate_parameters(int argc, char* argv[]);
void validate_key(string key);
bool encrypt_or_decrypt(char code);

//Driver for the enryption program.
//Parses the info and uses the
//encryption engine class.
int main(int argc, char* argv[]) {
  validate_parameters(argc, argv);
  //create a temp string for various
  //operations bellow
  string temp{};
  
  //cast key to string and get crypto_method
  string key{};
  cout << "Enter your password: ";
  cin >> key;

  string output_file{};
  cout << "What is the name of the output file: ";
  cin >> output_file;

  validate_key(key);
  temp = argv[2];
  crypto_method* method = crypto_engine::generate_crypto_object(temp.at(1), key);
  
  //open input file
  ifstream input{argv[3]};
  if (!input.is_open()) {
    cerr << "Input file does not exist. Exiting." << endl;
    exit(1);
  }
  //make input into string
  string message{};
  while (input) {
    //append each line into
    //message string
    message.push_back(input.get());
  }
  input.close();

  crypto_engine::crypto_buffer crypter{};
  temp = argv[1];
  if (encrypt_or_decrypt(temp.at(1))) {
    crypter.encrypt(message, method);
  }
  else {
    crypter.decrypt(message, method);
  }

  //open output file
  ofstream output{output_file};
  output << crypter;
  output.close();
}

//Validates input parameters to perform a
//cursory check for malformity. If input is
//malformed, the program crashes.
//input: argc - number of parameters
//       argv - string array of terminal inputs
//output: not applicable
void validate_parameters(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "Please enter the proper amount of arguements."
	 << "Exiting." << endl;
    exit(1);
  }

  //ignore program name
  for (int i = 1; i < argc - 1; i++) {
    if (strlen(argv[i]) < 2) {
      cerr << "Malformed argument. Exiting." << endl;
      exit(1);
    }
  }
}

//Validates password. Checking is done against the
//encryption engine valid character check.
//Crashes program if their is an invalid character.
//input:key - password
//output: not applicable
void validate_key(string key) {
  for (string::size_type i = 0; i < key.length(); i++) {
    if (!crypto_engine::is_valid_character(key.at(i))) {
      cerr << "Password has invalid character(s). Exiting." << endl;
    }
  }
}

//Parses input to determine if the code is an
//encrypt or decrypt code. If another code is
//present crashes the program.
//input: encrypt/decrypt code
//output: true - encrypt, false - decrypt
bool encrypt_or_decrypt(char code) {
  switch (code) {
  case 'e':
  case 'E':
    return true;
    break;
  case 'd':
  case 'D':
    return false;
    break;
  default:
    cerr << "Please specify encryption/decryption. Exiting." << endl;
    exit(1);
  }
}
