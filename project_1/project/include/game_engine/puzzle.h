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
 * filename: puzzle.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/10/16
 * Compile: make
 * Sample usage: n/a
 * Sources: no sources
 *
 * Methods and structures for dealing with puzzles.
 */
#ifndef PUZZLE_H
#define PUZZLE_H 1

#include "user.h"
#include <string>
#include <fstream>
using namespace std;

//Right answer adds mods
//Wrong answer subtracts mods
struct quiz_node {
  quiz_node *next;
  string question;
  string answer;
  user_prop mods;
};

struct quiz_list {
  quiz_node *head;
  quiz_node *tail;
  int num_elements;
};

////////////////
//Quiz methods//
////////////////

//Adds question to list based on
//question properties. Does this
//for a global list.
void add_question(string question, string ans, user_prop mods, quiz_list& quiz);
void add_question(quiz_node* question, quiz_list& quiz);
//Removes the tail of the list and
//adjusts list properties likewise.
quiz_node* remove_question(quiz_list& list);
//Parses a single question from a text file and
//returns the question.
quiz_node* parse_question(ifstream& file);
//Parses the user property string to form
//the list of user properties.
user_prop parse_user_prop(string props);
//Initializes the quiz list from a quiz file.
quiz_list init_quiz_list(string filename);
#endif /*PUZZLE_H*/
