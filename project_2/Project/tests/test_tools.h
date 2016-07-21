#ifndef TEST_TOOLS_H
#define TEST_TOOLS_H 1

#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void print_case(int case_num, string case_name)
{
  cout << "\tCase " << case_num << ": " << case_name << endl;
}

void print_pass()
{
  cout << "\tPassed..." << endl;
}

void user_verify(string verification_message)
{
  cout << "\t\t" << verification_message << endl;
  cout << "\t\tIs case true?(y/n): ";
  
  char u_in = 'k';
  while (u_in != 'y' || u_in != 'Y') {
    cin >> u_in;
    if (u_in == 'n' || u_in == 'N')
      //stop program for failure
      assert(false);
    else if (u_in != 'y' || u_in != 'Y')
      cout << "Please enter a valid response: ";
  }
}
#endif /*TEST_TOOLS_H*/
