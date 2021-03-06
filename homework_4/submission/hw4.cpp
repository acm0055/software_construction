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
 * Development Environment: emacs, gcc, Linux
 * Version: 2/12/16
 * Compile: g++ hw4.cpp -std=g++0x -o hw4
 * Sample usage: ./hw4
 * Sources: Merge algorithm has influences from Dr. Hendrix of Auburn University &&
 *                  Introduction to Algorithms 3rd Edition by Cormen et. al. ?? copy syntax inspiration
 *                  Bjarne Stroustrup The C++ Programming Language 4th Edition
  */
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

const int MAX_ARRAY_SZ = 100;
const int MAX_FILENAME_SZ = 256;

//function headers
void run_all_tests();
void merge_array_test();
void process_file_test();
void output_file_test();
int process_file(const char*, int[], int&);
int merge_arrays(const int[], const int[], int, int, int[]);
int output_file(const char*, int[], int);

//Driver for the program
//Runs the test suite on file_merger
//Provides cli for the file_merger library
//Invarient files should contain less than 100 entries
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

  if (output_file_sz > MAX_ARRAY_SZ) {
    cout << "Two many elements in the addition of both arrays. Exiting.\n";
    exit(1);
  }
  
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

//Processes file into an array of numbers
//In: file name (c-style string)
//In: modifiable array for output
//In: modifiable int for array size
//Out: 0 for good, 1 for error
//Out: array of numbers from file
//Out: array size
int process_file(const char* filename, int* output, int& arr_sz) {
  
  //throw error for null input
  if (!filename || !output)
    return 1;

  ifstream input{filename};
  //problem reading file
  if (!input.is_open())
    return 1;

  int i;
  //Bjarne Stroustrup
  for(i = 0; input; i++) {
    input >> output[i];
    if (i >= MAX_ARRAY_SZ) {
      cout << "Number of elements in file is two large. Exiting\n";
      exit(1);
    }
  }

  //clean up, set, and close
  //decrement because inc one two many times
  arr_sz = i - 1;
  input.close();

  return 0;
}

//Merges two file inputs of sorted numbers represented
//as an array into one sorted output represented as an array
//Source: See above statement in top header
//In: array representing file one
//In: array representing file two
//In: array size for file one array
//In: array size for file two array
//In: modifiable array for merged output
//Out: 0 for good, 1 for error
//Out: array of merged numbers from both files
//No need to output final arrays size since input array sizes known to client
int merge_arrays(const int file_one[], const int file_two[], int file_one_sz, int file_two_sz, int output[]) {
  
  //Check for null output array
  if(!output)
    return 1;

  //Bjarne Stroustrup inspired copy
  int i{};
  int j{};
  int k{};
  //copy until one file array is empty
  while (i < file_one_sz && j < file_two_sz)
    output[k++] = (file_one[i] < file_two[j]) ? file_one[i++] : file_two[j++];
  //special cases
  if (i < file_one_sz)
    while (i < file_one_sz)
      output[k++] = file_one[i++];
  else
    while (j < file_two_sz)
      output[k++] = file_two[j++];

  return 0;
}

//Output array into a file specified by the user
//In: file name (c-style string)
//In: output array
//In: array size
//Out: 0 for good, 1 for error
//Out: file filled with merged files
int output_file(const char* filename, int* output, int arr_sz) {
  //null input error
  if (!filename)
    return 1;
  //negative arr_sz error
  if (arr_sz < 0)
    return 1;

  ofstream file_out{filename};
  //File failed to be read
  if(!file_out.is_open())
    return 1;

  for (int i = 0; i < arr_sz; i++)
    file_out << output[i] << "\n";

  //flush and close file
  file_out.flush();
  file_out.close();
  return 0;
}

//Main test driver with interface
void run_all_tests() {
  cout << "*** Unit Test Cases ***";
  cout << "Unit Test Case 1: Function Name - void process_file(char*, int[], int[])\n";
  process_file_test();
  cout << "Press any key to continue...";
  cin.ignore().get();
  cout << "Unit Test Case 2: Function Name - void merge_array(int[], int[], int[])\n";
  merge_array_test();
  cout << "Press any key to continue...";
  cin.ignore().get();
  cout << "Unit Test Case 3: Function Name - void output_file(char*,  int[])\n";
  output_file_test();
  cout << "Press any key to continue...";
  cin.ignore().get();
}

//Merge array test
void merge_array_test() {
  int* a1{};
  int* a2{};
  int a1_sz{};
  int a2_sz{};
  int* output = new int[20];
  int err_state{};
  ///////////////////////////////////////
  //Test case 1 - Both arrays empty
  //////////////////////////////////////
  cout << "\tCase 1: Both arrays empty.\n";
  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //merge should not throw error
  assert(!err_state);
  cout << "\tCase Passed.\n";
  //////////////////////////////////////
  //Test case 2 - one array empty
  /////////////////////////////////////
  cout << "\tCase 2: One array empty.\n";
  a1 = new int[10];
  output = new int[10];
  a1_sz = 10;
  a2_sz = 0;
  for (int i = 0; i < 10; i++)
    a1[i] = i;
  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //merge should not throw error
  assert(err_state == 0);
  for (int i = 0; i < a1_sz; i++)
    assert(a1[i] == output[i]);
  //switch zero element array
  err_state = merge_arrays(a2, a1, a2_sz, a1_sz, output);
  assert(err_state == 0);
  for (int i = 0; i < a1_sz; i++)
    assert(a1[i] == output[i]);

  //deallocate memory
  delete[] a1;
  delete[] output;

  cout << "\tCase Passed.\n";
  /////////////////////////////////
  //Case 3: One array null
  ////////////////////////////////
  cout << "\tCase 3: One array null.\n";
  a1 = nullptr;
  a2 = new int[10];
  output = new int[10];
  a1_sz = 0;
  a2_sz = 10;
  for(int i = 0; i < 10; i++)
    a2[i] = i;

  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //should not throw error same as empty array
  assert(!err_state);
  //switch null array
  err_state = merge_arrays(a2, a1, a2_sz, a1_sz, output);
  //should not throw error same as empty array
  assert(!err_state);

  //deallocate memory
  delete[] a2;
  delete[] output;

  cout << "\tCase Passed.\n";
  ///////////////////////////////////////
  //Case 4: Both inputs null
  //////////////////////////////////////
  cout << "\tCase 4: Both arrays null.\n";
  a1 = nullptr;
  a2 = nullptr;
  output = new int[10];
  a1_sz = 0;
  a2_sz = 0;

  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //throws error because of null input array
  assert(!err_state);

  cout << "\tCase Passed.\n";
   /////////////////////////////////
  //Case 5: Output array null
  ////////////////////////////////
  cout << "\tCase 5: Output array null.\n";
  a1 = new int[10];
  a2 = new int[10];
  output = nullptr;
  a1_sz = 10;
  a2_sz = 10;
  for(int i = 0; i < 10; i++)
    a1[i] = a2[i] = i;

  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //throws error because of null output array
  assert(err_state);

  delete[] a2;
  delete[] a1;

  cout << "\tCase Passed.\n";
   /////////////////////////////////
  //Case 6: Normal test
  ////////////////////////////////
  cout << "\tCase 6: Average input array of size 10 and 5 with different element gaps\n";
  a1 = new int[10];
  a2 = new int[10];
  output = new int[20];
  a1_sz = 10;
  a2_sz = 10;
  for(int i = 0; i < 10; i++)
    a1[i] = i;
  for(int i = 0; i < 5; i++)
    a2[i] = i*i;

  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //should not throw error
  assert(!err_state);

  assert(output[0] == 0);
  assert(output[1] == 0);
  assert(output[2] == 1);
  assert(output[3] == 1);
  assert(output[4] == 2);
  assert(output[5] == 3);
  assert(output[6] == 4);
  assert(output[7] == 4);
  assert(output[8] == 5);
  assert(output[9] == 6);
  assert(output[10] == 7);
  assert(output[11] == 8);
  assert(output[12] == 9);
  assert(output[13] == 9);
  assert(output[14] == 16);

  delete[] a2;
  delete[] a1;
  delete[] output;

  cout << "\tCase Passed.\n";
}

//Process file test
void process_file_test() {
  const char* inv_addr{"invalid address"};
  const char* empty_addr{"empty.txt"};
  //ten elements
  const char* avg_addr{"avg.txt"};
  const char* one_addr{"one_element.txt"};
  int err_state{};
  int* output = new int[20];
  int arr_sz{};
  //////////////////////////////
  //Case 1: File Not Found
  /////////////////////////////
  cout << "\tCase 1: File not found\n";
  err_state = process_file(inv_addr, output, arr_sz);
  //error should be thrown for invalid file name
  assert(err_state);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 2: File name null
  /////////////////////////////
  cout << "\tCase 2: File name null\n";
  err_state = process_file(nullptr, output, arr_sz);
  //error should be thrown for null file name
  assert(err_state);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 3: File Empty
  /////////////////////////////
  cout << "\tCase 3: File empty\n";
  err_state = process_file(empty_addr, output, arr_sz);
  //no error should be thrown
  assert(!err_state);
  //empty array
  assert(!arr_sz);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 4: File one element
  /////////////////////////////
  cout << "\tCase 4: File contains one element\n";
  err_state = process_file(one_addr, output, arr_sz);
  //no error should be thrown
  assert(!err_state);
  //one element array
  assert(arr_sz == 1);
  //right element
  assert(output[0] == 1);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 5: File average
  /////////////////////////////
  cout << "\tCase 5: File of average element length 10\n";
  err_state = process_file(avg_addr, output, arr_sz);
  //no error should be thrown
  assert(!err_state);
  //10 element array
  assert(arr_sz == 10);
  //assert right elements
  for (int i = 0; i < 10; i++)
    assert(output[i] == i);

  cout << "\tCase Passed.\n";
}

//output file test
void output_file_test() {
  const char* inv_addr{"invalid address out"};
  const char* out_addr{"out.txt"};
  int* null_arr = nullptr;
  int empty_arr[]{};
  int avg_arr[]{0,1,2,3,4,5,6,7,8,9};
  int one_arr[]{1};
  int err_state{};
  int arr_sz{10};
  int* output = new int[20];
  //////////////////////////////
  //Case 1: File name null
  /////////////////////////////
  cout << "\tCase 1: File name null\n";
  err_state = output_file(nullptr, avg_arr, arr_sz);
  //error should be thrown for null file name
  assert(err_state);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 2: Array Empty
  /////////////////////////////
  cout << "\tCase 2: Array empty\n";
  arr_sz = 0;
  err_state = output_file(out_addr, empty_arr, arr_sz);
  //no error should be thrown
  assert(!err_state);
  //empty output
  process_file(out_addr, output, arr_sz);
  //empty array
  assert(!arr_sz);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 3: Array one element
  /////////////////////////////
  arr_sz = 1;
  cout << "\tCase 3: Array contains one element\n";
  err_state = output_file(out_addr, one_arr, arr_sz);
  //no error should be thrown
  assert(!err_state);

  process_file(out_addr, output, arr_sz);
  //one element array
  assert(arr_sz == 1);
  //right element
  assert(output[0] == 1);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 4: Array average
  /////////////////////////////
  arr_sz = 10;
  cout << "\tCase 4: Array of average element length 10\n";
  err_state = output_file(out_addr, avg_arr, arr_sz);
  //no error should be thrown
  assert(!err_state);

  process_file(out_addr, output, arr_sz);
  //10 element array
  assert(arr_sz == 10);
  //assert right elements
  for (int i = 0; i < 10; i++)
    assert(output[i] == i);

  cout << "\tCase Passed.\n";
}
