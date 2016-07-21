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
 * filename: menu.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/10/16
 * Compile: make
 * Sample usage: ./game
 * Sources: no sources
 * 
 * Methods and data structures for dealing with scoreboards and menus.
 */
#ifndef MENU_H
#define MENU_H 1

#include "user.h"
#include "puzzle.h"
#include <string>
using namespace std;

struct menu_entry {
  menu_entry* next_entry;
  string entry_desc;
};

struct menu {
  menu_entry* head;
  char num_items;
  string header_msg;
  string footer_msg;
};

//initializes main menu
menu init_main_menu();
//initializes move menu
menu init_move_menu();
//initializes difficulty menu
menu init_difficulty_menu();

char main_select();
char move_select();
char diff_select();

struct score_node {
  score_node *next;
  string user_name;
  unsigned short score;
};

struct score_list {
  score_node *head;
  int num_elements;
  int max_num_elements;
};

void display_menu(menu menu_in);
//Displays the top 5 high scores of
//the Dragons game.
void display_high_scores(string listname);
//Updates the high scores list
//based if the user is in the
//top 5 scores or not.
void write_high_scores(const user& user_in, string listname);

void add_score(score_node* elem, score_list& list);
#endif /*MENU_H*/
