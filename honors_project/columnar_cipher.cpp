#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include "columnar_cipher.h"

using namespace std;

//Constructs a columnar cipher
//based on a key. Initializes the
//order of the encryption based on
//the key and stores the key_lenght.
columnar_cipher::columnar_cipher(string key)
  : crypto_method{key}
{
  key_length = key.size();
  //initalize order with the values in key
  for (int i = 0; i < key.size(); i++)
    order.push_back(key.at(i));
}

//Turns the message into columns
//for rearraging based on
//the order of the key.
//Input: message - message to columnize
//Output: columnized message
vector<string> columnar_cipher::columnize(const string& message) {
  string::size_type num_rows = ceil((double)(message.length()-1) / key.length());
  
  vector<string> column_message(key.size(), string(num_rows, ' '));

  for (string::size_type i = 0; i < key.size(); i++) {
    for (string::size_type j = 0; j < num_rows; j++) {
      if (i + j*key.size() >= message.size() - 1) {
	column_message[i].at(j) = ' ';
      }
      else {
	column_message[i].at(j) = message.at(i + j*key.size());
      }
    }
  }

  return column_message;
}

//do nothing
columnar_cipher::~columnar_cipher() {
  //do nothing
}

//Interface for crpto_method.
//Calls the symmetric_codify method.
string columnar_cipher::encrypt(const string& message) {
  if (message.length() < key.length()) {
    cerr << "Key is larger than message. Exiting.\n";
    exit(1);
  }

  //stable sort the characters in order
  stable_sort(order.begin(), order.end());
  string temp_key = key;
  
  vector<int> temp_order;
  
  int j;
  for (int i = 0; i < order.size(); i++) {
    j = 0;
    while (order[j] != temp_key.at(i)) {
      j++;
    }
    order[j] = SENTINAL;
    //record columnar position
    temp_order.push_back(j);
  }

  order = temp_order;
  
  return symmetric_codify(message);
}

//Interface for crpto_method.
//Calls the symmetric_codify method.
string columnar_cipher::decrypt(const string& message) {
  if (message.length() < key.length()) {
    cerr << "Key is larger than message. Exiting.\n";
    exit(1);
  }

  //stable sort the characters in order
  stable_sort(order.begin(), order.end());
  string temp_key = key;
  
  vector<int> temp_order;
  
  int j;
  for (int i = 0; i < order.size(); i++) {
    j = 0;
    while (order[i] != temp_key.at(j)) {
      j++;
    }
    temp_key[j] = SENTINAL;
    //record columnar position
    temp_order.push_back(j);
  }

  order = temp_order;
  
  return symmetric_codify(message);
}

//The columnar cipher is a symmetric cipher
//on the basis of the order of the columns.
//This method implements this symmetric coding.
//Input: message to symmetric code
//Output: symmetric coded message
string columnar_cipher::symmetric_codify(const string& message) {
  vector<string> codify{};
  vector<string> column_message = columnize(message);
  string output{};

  for (string::size_type i = 0; i < key.length(); i++) {
    codify.push_back(column_message[order[i]]);
  }

  for (string::size_type i = 0; i < codify.front().length(); i++) {
    for (string::size_type j = 0; j < key.length(); j++) {
      output.push_back(codify[j].at(i));
    }
  }

  return output;
}
