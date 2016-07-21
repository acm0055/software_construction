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
 * filename: encounter.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/10/16
 * Compile: make
 * Sample usage: n/a
 * Sources: no sources
 */
#include "encounter.h"
#include "user.h"
#include "puzzle.h"
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

//User encounters grunt work.
void grunt_work(user& user_in, void*)
{
  cout << endl << user_in.name << ". You have encountered"
       << " grunt work. As you hopeless type away," << endl
       << "the disapointment of grad life naws at"
       << " your soul. Lose intelligence and time." << endl << endl;
  char time_loss = ((rand() % 2) + 1) * -1;
  char intelligence_loss = ((rand() % 4) + 1) * -1;
  user_prop mods{time_loss, 0, intelligence_loss};
  mod_user_prop(user_in.attr, mods);
}

void do_nothing(user& user_in, void*)
{
  cout << endl << user_in.name << ". You have encountered"
       << " nothing. You enjoy your day" << endl
       << "talking to your girlfriend. Except you do not"
       << " have a girlfriend. Lose time." << endl << endl;
  user_prop mods{-1, 0, 0};
  mod_user_prop(user_in.attr, mods);
}

//User encounters a professor.
void professor(user& user_in, void*)
{
  cout << endl << user_in.name << ". You have encountered"
       << " a professor. As he begins to talk you zone" << endl
       << "in and out. You wonder how much time has past."
       << " You wake in your apartment out of your stupour" << endl
       << "May gain intelligence. Lose time." << endl << endl;
  char time_loss = ((rand() % 2) + 1) * - 1;
  char intelligence_gain = (rand() % 2);
  user_prop mods{time_loss, 0, intelligence_gain};
  mod_user_prop(user_in.attr, mods);
}

//User encounters a grad student.
void grad_student(user& user_in, void*)
{
  cout << endl << user_in.name << ". You have encountered"
       << " a fellow grad student. You compete in video game," << endl
       << "the enjoyment of a day off nourishes"
       << " your soul. Lose time and money." << endl << endl;
  char time_loss = ((rand() % 2) + 1) * -1;
  char money_loss = ((rand() % 3) + 1) * -1;
  user_prop mods{time_loss, money_loss, 0};
  mod_user_prop(user_in.attr, mods);
}

//User must grade papers.
void grade_papers(user& user_in, void*)
{
  cout << endl << user_in.name << ". You have encountered"
       << " a mass of papers. As the tower of dead trees"
       << " colapse on your desk, you are filled with a" << endl
       << " spirit of hard work. You knock out these grades."
       << " Lose time and gain money." << endl << endl;
  char time_loss = ((rand() % 2) + 1) * -1;
  char money_gain = ((rand() % 2) + 1);
  user_prop mods{time_loss, money_gain, 0};
  mod_user_prop(user_in.attr, mods);
}

//Puzzle encounter for playing a puzzle.
void puzzle(user& user_in, void* puzzle_list)
{
  quiz_list* quiz = static_cast<quiz_list*>(puzzle_list);
  quiz_node* question = remove_question(*quiz);

  string user_resp{};

  cout << question->question << endl;
  cout << "User Response: ";
  getline(cin, user_resp);

  if (user_resp == question->answer) {
    cout << "You are correct!" << endl;
    mod_user_prop(user_in.attr, question->mods);
  }
  else {
    cout << "You are wrong." << endl;
    cout << "Correct Answer: " << question->answer << endl;
    user_prop neg_mods{static_cast<char>(question->mods.time),
	static_cast<char>(question->mods.money * -1),
	static_cast<char>(question->mods.intelligence * -1)};
    mod_user_prop(user_in.attr, neg_mods);
  }

  delete question;
}

//Returns a randomly generated encounter.
encounter_func generate_encounter() {
  int temp = rand() % 100;
  if (temp < GRUNT_WORK_CHANCE) {
    return &grunt_work;
  }
  else if (temp < DO_NOTHING_CHANCE) {
    return &do_nothing;
  }
  else if (temp < PUZZLE_CHANCE) {
    return &puzzle;
  }
  else if (temp < PROFESSOR_CHANCE) {
    return &professor;
  }
  else if (temp < GRAD_STUDENT_CHANCE) {
    return &grad_student;
  }
  else {
    return &grade_papers;
  }
}
