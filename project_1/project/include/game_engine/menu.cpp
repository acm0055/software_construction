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
 * filename: menu.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/11/16
 * Compile: make
 * Sample usage: n/a
 * Sources: syntax help from http://www.cplusplus.com/reference/fstream
 * /ofstream/ofstream/
 */
#include "menu.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//Initializes the main menu data structure
menu init_main_menu()
{
  menu out{};
  string temp;
  for (int i = 0; i < 49; i++)
    temp.push_back('~');
  out.header_msg = temp;
  out.footer_msg = temp;

  out.head =
    new menu_entry{nullptr,
		   "Start a new quest: (a)"};
  out.head->next_entry =
    new menu_entry{nullptr,
		   "Display high scores: (b)"};
  out.head->next_entry->next_entry =
    new menu_entry{nullptr,
		   "Quit the game: (c)"};
  out.num_items = 3;
  return out;
}

//Initializes the move menu data structure
menu init_move_menu()
{
  menu out{};
  string temp;
  for (int i = 0; i < 49; i++)
    temp.push_back('~');
  out.header_msg = temp;
  out.footer_msg = temp;

  out.head =
    new menu_entry{nullptr,
		   "Take step forward: (a)"};
  out.head->next_entry =
    new menu_entry{nullptr,
		   "Read technical paper: (b)"};
  out.head->next_entry->next_entry =
    new menu_entry{nullptr,
		   "Search for loose change: (c)"};
  out.head->next_entry->next_entry->next_entry =
    new menu_entry{nullptr,
		   "View character: (d)"};
  out.head->next_entry->next_entry->next_entry->next_entry =
    new menu_entry{nullptr,
		   "Quit game: (e)"};
  out.num_items = 5;
  return out;
}

//Initializes the difficulty menu data structure
menu init_difficulty_menu()
{
  menu out{};
  string temp;
  for (int i = 0; i < 49; i++)
    temp.push_back('~');
  out.header_msg = temp;
  out.header_msg +=
    ("\nHuman that dares play this game.\n"
     "Select thine difficulty. Wield thy fate.\n");
  out.footer_msg = temp;

  out.head =
    new menu_entry{nullptr,
		   "Noice: (a)"};
  out.head->next_entry =
    new menu_entry{nullptr,
		   "Apprentice: (b)"};
  out.head->next_entry->next_entry =
    new menu_entry{nullptr,
		   "Master: (c)"};
  out.num_items = 3;
  return out;
}

//Displays a menu object to cout
void display_menu(menu menu_in)
{
  cout << menu_in.header_msg << endl;

  menu_entry* temp = menu_in.head;
  for (int i = 0; i < menu_in.num_items; i++) {
    cout << temp->entry_desc << endl;
    temp = temp->next_entry;
  }

  cout << menu_in.footer_msg << endl;
}

//Returns the user input making sure
//to only allow valid inputs for main
char main_select()
{
  char user_input;
  bool valid{false};
  do {
    cout << "User input: ";
    cin >> user_input;
    //flush input
    cin.peek() == '\r' ? cin.ignore() : cin;
    cin.peek() == '\n' ? cin.ignore() : cin;
    
    switch (user_input) {
    case 'a':
      return 'a';
    case 'b':
      return 'b';
    case 'c':
      return 'c';
    default:
      cout << "Please enter a valid value:" << endl;
    }
  } while (!valid);
  return '0';
}

//Returns the user input making sure
//to only allow valid inputs for move
char move_select()
{
  char user_input;
  bool valid{false};
  do {
    cout << "User input: ";
    cin >> user_input;
    //flush input
    cin.peek() == '\r' ? cin.ignore() : cin;
    cin.peek() == '\n' ? cin.ignore() : cin;
    
    switch (user_input) {
    case 'a':
      return 'a';
    case 'b':
      return 'b';
    case 'c':
      return 'c';
    case 'd':
      return 'd';
    case 'e':
      return 'e';
    default:
      cout << "Please enter a valid value:" << endl;
    }
  } while (!valid);
  return '0';
}

//Returns the user input making sure
//to only allow valid inputs for difficulty menu
char diff_select()
{
  char user_input;
  bool valid{false};
  do {
    cout << "User input: ";
    cin >> user_input;
    //flush input
    cin.peek() == '\r' ? cin.ignore() : cin;
    cin.peek() == '\n' ? cin.ignore() : cin;
    
    switch (user_input) {
    case 'a':
      return 'a';
    case 'b':
      return 'b';
    case 'c':
      return 'c';
    default:
      cout << "Please enter a valid value:" << endl;
    }
  } while (!valid);
  return '0';
}

//Reads a displays a high score list
//stored in a speciliaty formated file
void display_high_scores(string listname)
{
  ifstream file{listname};
  string temp;
  
  getline(file, temp);
  int num_elements = stoi(temp);

  //flush out max_num_elements line
  getline(file, temp);

  for (int i = 0; i < num_elements; i++) {
    //name
    getline(file, temp);
    cout << "Player #" << i+1 << " " << temp;
    //score
    getline(file, temp);
    cout << " " << temp << endl;
  }
}

//Writes high score list to a speciliaty formated file.
//Reads the current high scores and adds the user
//if his/her score is high enough.
void write_high_scores(const user& user_in, string listname)
{
  ifstream file{listname};
  string temp;
  score_list list{nullptr, 0, 0};

  getline(file, temp);
  int num_elements = stoi(temp);

  getline(file, temp);
  list.max_num_elements = stoi(temp);

  int pos;
  score_node* score;
  for (int i = 0; i < num_elements; i++) {
    score = new score_node;
    score->next = nullptr;
    
    getline(file, temp);
    score->user_name = temp;
    
    getline(file, temp);
    score->score = stoi(temp);
    
    add_score(score, list);
  }

  //add user to high score list
  //if possible
  score = new score_node;
  score->next = nullptr;
  score->user_name = user_in.name;
  score->score = user_in.attr.intelligence;
  score->score += user_in.attr.intelligence*user_in.attr.money;
  score->score += user_in.attr.intelligence*user_in.attr.money*
    user_in.attr.time;
  add_score(score, list);

  file.close();

  //syntax help from http://www.cplusplus.com/reference/fstream/ofstream/ofstream/
  ofstream out{listname, ofstream::trunc};
  //write file
  out << list.num_elements << endl;
  out << list.max_num_elements << endl;
  //user score as prev node
  score = list.head;
  score_node* cur = list.head;
  for (int i = 0; i < list.num_elements; i++) {
    out << cur->user_name << endl;
    out << cur->score << endl;
    score = cur;
    cur = cur->next;
    delete score;
  }
}

//Adds score to the end of a score list
void add_score(score_node* elem, score_list& list) {
  score_node* temp;
  score_node* prev = nullptr;
  score_node* cur = list.head;

  if (list.num_elements == 0) {
    list.head = elem;
    elem->next = nullptr;
    list.num_elements++;
  }
  else if (list.num_elements == 1) {
    if (list.head->score > elem->score) {
      list.head->next = elem;
      elem->next = nullptr;
    }
    else {
      temp = list.head;
      list.head = elem;
      elem->next = temp;
      temp->next = nullptr;
    }
    list.num_elements++;
  }
  else {
    while (cur->next) {
      if (elem->score > cur->score) {
	break;
      }
      prev = cur;
      cur = cur->next;
    }
    //replace head
    if (!prev) {
      temp = list.head;
      list.head = elem;
      elem->next = temp;
      prev = list.head;
    }
    //replace body/tail
    else {
      if (!cur->next) {
	if (elem->score > cur->score) {
	  prev->next = elem;
	  elem->next = cur;
	}
	else {
	  cur->next = elem;
	  elem->next = nullptr;
	}
      }
      else {
	prev->next = elem;
	elem->next = cur;
      }
    }
    
    list.num_elements++;
  }

  //check to make sure their are not too
  //many nodes in the list and correct the problem
  if (list.num_elements > list.max_num_elements) {
    //sense an element is added we
    //are looking for the node before the
    //last element
    while (prev->next->next != nullptr)
      prev = prev->next;
    //guarenteed to work since only
    //one score is added at a time
    delete prev->next;
    prev->next = nullptr;
    list.num_elements--;
  }
}
