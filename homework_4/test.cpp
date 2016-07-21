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
 * Sample usage: no usage without driver
 * Sources: no sources
 */
#include <iostream>
#include <cassert>
#include "file_merger.h"
#include "test.h"
using namespace std;

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
  cout << "\tCase 6: Average input arrays of size 10\n";
  a1 = new int[10];
  a2 = new int[10];
  output = new int[20];
  a1_sz = 10;
  a2_sz = 10;
  for(int i = 0; i < 10; i++)
    a1[i] = a2[i] = i;

  err_state = merge_arrays(a1, a2, a1_sz, a2_sz, output);
  //should not throw error
  assert(!err_state);

  int j = 0;
  for (int i = 0; i < 20; i++) {
    assert(output[i] == j);
    //increment every other entry
    if (i % 2 == 1)
      j++;
  }

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
  cout << "\tCase 2: File name null\n";
  err_state = output_file(nullptr, avg_arr, arr_sz);
  //error should be thrown for null file name
  assert(err_state);

  cout << "\tCase Passed.\n";
  //////////////////////////////
  //Case 2: Array Empty
  /////////////////////////////
  cout << "\tCase 3: Array empty\n";
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
  cout << "\tCase 4: Array contains one element\n";
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
  cout << "\tCase 5: Array of average element length 10\n";
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
