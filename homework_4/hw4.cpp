/*
 * Copyright (c) 2016, Austin Chase Minor
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL AUSTIN CHASE MINOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Name: Austin Chase Minor
 * Auburn UserID: 903223922
 * filename: test.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 2/11/16
 * Compile: make
 * Sample usage: ./hw4
 * Sources: no sources
 */
#include <iostream>
#include "file_merger.h"
#include "test.h"
using namespace std;

const int MAX_ARRAY_SZ = 100;
const int MAX_FILENAME_SZ = 256;

//Driver for the program
//Runs the test suite on file_merger
//Provides cli for the file_merger library
int main() {
  int output[MAX_ARRAY_SZ] {};
  int file_one[MAX_ARRAY_SZ] {};
  int file_two[MAX_ARRAY_SZ] {};
  int file_one_sz {};
  int file_two_sz{};
  int output_file_sz{};
  int error_code {};
  char* filename = new char[MAX_FILENAME_SZ];

  //Run testing suite
  run_all_tests();
  
  cout << "*** Welcome to Austin Minor's sorting program ***\n"
       << "Enter the first input file name: ";
  cin.getline(filename, MAX_FILENAME_SZ);

  error_code = process_file(filename, file_one, file_one_sz);
  if (error_code == 1) {
    cout << "Invalid input. Exiting.\n";
    exit(1);
  }
  
  cout << "The list of " << file_one_sz << " numbers in file "
       << filename << " is:\n";
  //print numbers from file
  for (int i = 0 ; i < file_one_sz; i++)
    cout << file_one[i] << endl;
  
  cout << "Enter the second input file name: ";
  cin.getline(filename, MAX_FILENAME_SZ);

  error_code = process_file(filename, file_two, file_two_sz);
  if (error_code == 1) {
    cout << "Invalid input. Exiting.\n";
    exit(1);
  }
  
  cout << "The list of " << file_two_sz << " numbers in file "
       << filename << " is:\n";
  //print numbers from file
  for (int i = 0 ; i < file_two_sz; i++)
    cout << file_two[i] << endl;

  output_file_sz = file_one_sz + file_two_sz;
  error_code = merge_arrays(file_one, file_two, file_one_sz, file_two_sz, output);
  if (error_code == 1) {
    cout << "Error in merge files. Exiting.\n";
    exit(1);
  }

  //Prints sorted list
  cout << "The sorted list of " << output_file_sz << " numbers is : ";
  for(int i = 0; i < output_file_sz; i++)
    cout << output[i] << " ";
  cout << endl << "Enter the output file name: ";
  cin.getline(filename, MAX_FILENAME_SZ);

  output_file(filename, output, output_file_sz);
  
  cout << "*** Please check the new file - " << filename << " ***\n"
       << "*** Goodbye. ***\n";
}
