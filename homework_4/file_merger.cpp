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
 * filename: file_merger.cpp
 * Development Environment: make, emacs, Linux, gcc
 * Version: 2/9/16
 * Compile: make
 * Sample usage: no usage
 * Sources: Merge algorithm has influences from Dr. Hendrix of Auburn University ??
 *                  Introduction to Algorithms 3rd Edition by Cormen et. al. ?? copy syntax inspiration
 *                  Bjarne Stroupse C++ Language Reference 4th Edition
 *                  File open check from http://stackoverflow.com/questions/1647557/ifstream-how-to-tell-if-specified-file-doesnt-exist
 */
#include <fstream>
using namespace std;

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
  //Bjarne Stroupse
  for(i = 0; input; i++)
    input >> output[i];

  //clean up, set, and close
  //decrement because inc one two many times
  arr_sz = i - 1;
  input.close();

  return 0;
}

//Merges two file inputs of sorted numbers represented
//as an array into one sorted output represented as an array
//In: modifiable array representing file one
//In: modifiable array representing file two
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

  //Bjarne Stroupse inspired copy
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
    while (i < file_two_sz)
      output[k++] = file_two[i++];

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
