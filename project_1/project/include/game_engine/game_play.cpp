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
 * filename: game_play.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/11/16
 * Compile: make
 * Sample usage: n/a
 * Sources: no sources
 */
#include "game_play.h"
#include "encounter.h"
#include "user.h"
#include "puzzle.h"
#include "menu.h"
#include <iostream>
using namespace std;

//Move the character and generate a random encounter.
void move_character(user& user_in, quiz_list& list)
{
  user_in.pos--;

  encounter_func encounter = generate_encounter();
  encounter(user_in, &list);
}
//Reading tech papers boosts intelligence and loses time.
void read_technical_paper(user& user_in)
{
  cout << endl << "Reading a new technical paper"
       << " you obtain a grasp of knowledge beyond you." << endl
       << "Gain intelligence and lose time" << endl << endl;
  user_in.attr.intelligence += TECH_PAPER_INT_BOOST;
  user_in.attr.time--;
}
//Searches for loose change boosts money and loses time.
void search_for_loose_change(user& user_in)
{
  cout << endl << "Your want for Taco Bell drives"
       << " your desire to search your couch for money." << endl
       << "Gain money and lose time." << endl << endl;
  user_in.attr.money += LOOSE_CHANGE_MNY_BOOST;
  user_in.attr.time--;
}
//Displays character and his/her stats
void view_character(user& user_in)
{
  cout << endl;
  for (int i = 0; i < 49; i++)
    cout << "~";
  cout << endl;

  cout << "\t\tName: " << user_in.name << endl;
  cout << "\t\tIntelligence: "
       << static_cast<short>(user_in.attr.intelligence) << endl;
  cout << "\t\tMoney: "
       << static_cast<short>(user_in.attr.money) << endl;
  cout << "\t\tTime: "
       << static_cast<short>(user_in.attr.time) << endl;
  cout << "\t\tPos: "
       << user_in.pos << endl;

  for (int i = 0; i < 49; i++)
    cout << "~";
  cout << endl;
}

//selects user difficulty.
//returns a user object of that difficulty
user select_difficulty(string user_name)
{
  char input;
  display_menu(init_difficulty_menu());
  input = diff_select();
  switch (input) {
  case 'a':
    return user{user_name, 20,
	user_prop{30,7,7}};
  case 'b':
    return user{user_name, 20,
	user_prop{30,5,5}};
  case 'c':
    return user{user_name, 20,
	user_prop{27,3,3}};
  }
}

//Does the appropriate actions for a move.
void process_move(user& user_in, quiz_list& quiz, char move)
{
  switch (move) {
  case 'a':
    move_character(user_in, quiz);
    break;
  case 'b':
    read_technical_paper(user_in);
    break;
  case 'c':
    search_for_loose_change(user_in);
    break;
  case 'd':
    view_character(user_in);
  }
}

//starts a game
void game()
{
  menu move_menu = init_move_menu();
  quiz_list quiz{};
  char move_action{'a'};
  string name;
  
  cout << endl << "Adventure what be thou name: ";
  getline(cin, name);
  
  user player = select_difficulty(name);
  
  while (move_action != 'e') {
    //makes sure quiz list always full
    if (quiz.num_elements == 0)
      quiz = init_quiz_list("quiz.txt");
    
    display_menu(move_menu);
    move_action = move_select();
    process_move(player,quiz,move_action);
    
    //user may have lost game
    if (is_user_dead(player)) {
      game_over(player);
      move_action = 'e';
    }
    
    if (player.pos == 0) {
      cout << endl << "YOU WIN!!!" << endl;
      write_high_scores(player, "highscores.txt");
      move_action = 'e';
    }
  }

  //clear elements and free memory
  quiz_node* temp;
  while (quiz.num_elements != 0) {
    temp = remove_question(quiz);
    delete temp;
  }
}

//handles game over scenario
void game_over(const user& user_in)
{
    if (user_in.pos == 0) {
      //do nothing handled in main game code
    }
    else {
      switch (is_user_dead(user_in)) {
      case 'a':
	cout << endl << "As procastination settles into"
	     << endl << "your soul, you run out of time"
	     << endl << "and get kicked out of college." << endl;
	break;
      case 'b':
	cout << endl << "Lack of money led to you accepting a position"
	     << endl << "in a medical trial. Except you were infected with"
	     << endl << "a strange virus. You are patient zero of zombie appocolypse."
	     << endl;
	break;
      case 'c':
	cout << endl << "Lack of intelligence led to all night video game parties."
	     << endl << "As the wee morning hours wain into existence, you forgot"
	     << endl << "to do your job. Gets fired." << endl;
	break;
      }
      cout << "Game Over" << endl;
    }
}
