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
 * filename: puzzle.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/11/16
 * Compile: make
 * Sample usage: n/a
 * Sources: personal randomize algorithm from algorithms assignment
 */

#include "puzzle.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


//Adds question to the end of list
void add_question(quiz_node* elem, quiz_list& list) {
  if (list.num_elements > 0) {
    list.tail->next = elem;
    list.tail = elem;
    list.num_elements++;
  }
  else {
    list.head = elem;
    list.tail = elem;
    list.num_elements++;
  }
}
//Adds question to the end of list
void add_question(string question, string ans, user_prop mods, quiz_list& list)
{
  quiz_node* elem = new quiz_node{nullptr, question, ans, mods};
  add_question(elem, list);
}
//Removes the tail of the list and
//adjusts list properties likewise.
quiz_node* remove_question(quiz_list& list)
{
  quiz_node* elem = list.head;
  if (list.num_elements > 0) {
    if (list.num_elements == 1) {
      list.head = nullptr;
      list.tail = nullptr;
      list.num_elements--;
    }
    else {
      list.head = list.head->next;
      list.num_elements--;
    }
  }
  return elem;
}
//Parses a single question from a text file and
//returns the question.
quiz_node* parse_question(std::ifstream& file)
{
  if (!file.is_open())
    return nullptr;
  string question, ans, user_mods;
  //question is first line
  getline(file, question);
  //answer is second line
  getline(file, ans);
  //user_mods is third line
  getline(file, user_mods);
  return new quiz_node{nullptr, question, ans,
      parse_user_prop(user_mods)};
}
//Parses the user property string to form
//the list of user properties.
user_prop parse_user_prop(string props)
{
  string time, money, intelligence;
  int old_pos;
  int comma_pos = props.find_first_of(',');
  time = props.substr(0, comma_pos);
  old_pos = comma_pos;
  comma_pos = props.find_first_of(',', old_pos + 1);
  money = props.substr(old_pos + 1, comma_pos - old_pos);
  old_pos = comma_pos;
  intelligence = props.substr(old_pos + 1);

  return user_prop{static_cast<char>(stoi(time)),
      static_cast<char>(stoi(money)),
      static_cast<char>(stoi(intelligence))};
}
//Initializes the quiz list from a quiz file.
//Assumes properly formated file.
quiz_list init_quiz_list(string filename)
{
  ifstream file{filename};
  vector<quiz_node*> unperm_list{};
  quiz_list perm_list{};

  //number of questions
  string num_s;
  int num;
  getline(file, num_s);
  num = stoi(num_s);

  for (int i = 0; i < num; i++)
    unperm_list.push_back(parse_question(file));

  //from algorithms assignment
  //author: Chase Minor
  quiz_node* temp;
  int rng_index;
  //simple array permutate in theta(n) time
  for (int i = 0; i < unperm_list.size(); i++) {
    rng_index = rand() % unperm_list.size();
    temp = unperm_list[i];
    unperm_list[i] = unperm_list[rng_index];
    unperm_list[rng_index] = temp; 
  }

  for (int i = 0; i < unperm_list.size(); i++)
    add_question(unperm_list[i], perm_list);

  return perm_list;
}
