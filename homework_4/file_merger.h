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
 * filename: file_merger.h
 * Development Environment: make, emacs, Linux, gcc
 * Version: 2/8/16
 * Compile: make
 * Sample usage: no usage
 * Sources: no sources
 */
#include <fstream>

//Processes file into an array of numbers
//In: file name (c-style string)
//In: modifiable array for output
//In: modifiable int for array size
//Out: 0 for good, 1 for error
//Out: array of numbers from file
//Out: array size
int process_file(const char*, int[], int&);

//Merges two file inputs of sorted numbers represented
//as an array into one sorted output represented as an array
//In: modifiable array representing file one
//In: modifiable array representing file two
//In: array size for file one array
//In: array size for file two array
//In: modifiable array for merged output
//Out: 0 for good, 1 for error
//Out: array of merged numbers from both files
int merge_arrays(const int[], const int[], int, int, int[]);

//Output array into a file specified by the user
//In: file name (c-style string)
//In: output array
//In: array size
//Out: 0 for good, 1 for error
//Out: file filled with merged files
int output_file(const char*, int[], int);
