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
 * Version: 4/11/16
 * Compile: make test
 * Sample usage: ./test_game
 * Sources: no sources
 */
#include "../include/game_engine/encounter.h"
#include "../include/game_engine/user.h"
#include "../include/game_engine/game_play.h"
#include "../include/game_engine/menu.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void test_add_question();
void test_remove_question();
void test_parse_question();
void test_do_nothing();
void test_grad_student();
void test_grade_papers();
void test_grunt_work();
void test_professor();
void test_puzzle();
void test_mod_user_prop();
void test_generate_encounter();

quiz_list quiz;

//Run all tests
int main() {
  srand(time(0));
  cout << "Test add_question()" << endl;  
  test_add_question();
  cout << "Test remove_question()" << endl;
  test_remove_question();
  cout << "Test parse_question()" << endl;
  test_parse_question();
  cout << "Test do_nothing()" << endl;
  test_do_nothing();
  cout << "Test grad_student()" << endl;
  test_grad_student();
  cout << "Test grade_papers()" << endl;
  test_grade_papers();
  cout << "Test grunt_work()" << endl;
  test_grunt_work();
  cout << "Test professor()" << endl;
  test_professor();
  cout << "Test puzzle()" << endl;
  test_puzzle();
  cout << "Test mod_user_prop()" << endl;
  test_mod_user_prop();
  cout << "Test generate_encounter()" << endl;
  test_generate_encounter();
}

void test_add_question()
{
  cout << "\tCase 1: Standard Quiz Node" << endl;
  add_question("Test","Test",user_prop{}, quiz);
  cout << "\t\tCase 1.1: Size Change" << endl;
  assert(quiz.num_elements == 1);
  cout << "\t\tPassed..." << endl;
  cout << "\t\tCase 1.2: Proper List" << endl;
  assert(quiz.head == quiz.tail);
  assert(quiz.head->next == nullptr);
  cout << "\t\tPassed..." << endl;
  cout << "\t\tCase 1.2: Proper Node" << endl;
  assert(quiz.head->question == "Test");
  assert(quiz.head->answer == "Test");
  assert(quiz.head->mods.time == 0);
  assert(quiz.head->mods.money == 0);
  assert(quiz.head->mods.intelligence == 0);
  cout << "\t\tPassed..." << endl;
  //clean up
  remove_question(quiz);
  cout << "\tPassed..." << endl;
}

void test_remove_question()
{
  cout << "\tCase 1: Empty List" << endl;
  assert(remove_question(quiz) == nullptr);
  assert(quiz.num_elements == 0);
  cout << "\tPassed..." << endl;
  
  cout << "\tCase 2: One Element List" << endl;
  cout << "\t\tCase 2.1: Proper List" << endl;
  add_question("Test","Test",user_prop{}, quiz);
  assert(quiz.num_elements == 1);
  quiz_node* temp = remove_question(quiz);
  assert(quiz.head == nullptr);
  assert(quiz.tail == nullptr);
  cout << "\t\tPassed..." << endl;
  cout << "\t\tCase 2.2: Proper Node" << endl;
  assert(temp->question == "Test");
  assert(temp->answer == "Test");
  assert(temp->mods.time == 0);
  assert(temp->mods.money == 0);
  assert(temp->mods.intelligence == 0);
  assert(quiz.num_elements == 0);
  delete temp;
  cout << "\t\tPassed..." << endl;
  cout << "\tPassed..." << endl;
  
  cout << "\tCase 3: Average List" << endl;
  add_question("Test","Test",user_prop{}, quiz);
  add_question("Test","Test",user_prop{}, quiz);
  add_question("Test","Test",user_prop{}, quiz);
  add_question("Test","Test",user_prop{}, quiz);
  assert(quiz.num_elements == 4);
  temp = remove_question(quiz);
  delete temp;
  temp = remove_question(quiz);
  delete temp;
  temp = remove_question(quiz);
  delete temp;
  temp = remove_question(quiz);
  delete temp;
  assert(quiz.num_elements == 0);
  cout << "\tPassed..." << endl;
}

//parse_user_props implicitly in this test
void test_parse_question()
{
  ifstream unknown_file{"unknown"};
  cout << "\tCase 1: Unknown file returns nullptr." << endl;
  quiz_node* temp = parse_question(unknown_file);
  assert(temp == nullptr);
  cout << "\tPassed..." << endl;
  
  ifstream test_file{"test_quiz.txt"};
  assert(test_file.is_open());
  //flush number of questions mark out
  string num;
  getline(test_file, num);

  cout << "\tCase 2: Parse first question of file." << endl;
  temp = parse_question(test_file);
  assert(temp->question == "Test");
  assert(temp->answer == "Test");
  assert(temp->mods.time == -1);
  assert(temp->mods.money == 2);
  assert(temp->mods.intelligence == 2);
  assert(temp->next == nullptr);
  delete temp;
  cout << "\tPassed..." << endl;

  cout << "\tCase 3: Parse second question of file." << endl;
  temp = parse_question(test_file);
  assert(temp->question == "Test Test");
  assert(temp->answer == "Test Test");
  assert(temp->mods.time == -1);
  assert(temp->mods.money == 2);
  assert(temp->mods.intelligence == 2);
  assert(temp->next == nullptr);
  delete temp;
  test_file.close();
  cout << "\tPassed..." << endl;
}

void test_mod_user_prop()
{
  user_prop user_attr{};
  user_prop mods{-1,2,1};
  cout << "\tCase 1: Modify user properties." << endl;
  mod_user_prop(user_attr,mods);
  assert(user_attr.time == mods.time);
  assert(user_attr.intelligence == mods.intelligence);
  assert(user_attr.money == mods.money);
  cout << "\tPassed..." << endl;
}

void test_grunt_work()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  cout.setstate(ios::badbit);
  for (int i = 0; i < 100; i++ ) {
    grunt_work(chase, nullptr);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence != 0);
    assert(chase.attr.money == 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout.clear();
  cout << "\tPassed..." << endl;
}

void test_do_nothing()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  cout.setstate(ios::badbit);
  for (int i = 0; i < 100; i++) {
    do_nothing(chase, nullptr);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence == 0);
    assert(chase.attr.money == 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout.clear();
  cout << "\tPassed..." << endl;
}

void test_puzzle()
{
  user chase{"chase", 0, user_prop{}};
  quiz = init_quiz_list("test_quiz.txt");
  cout << "\tCase 1: Tester should miss question. "
       << endl << "\tAnswer is the same as question." << endl;
  puzzle(chase, &quiz);
  assert(chase.attr.intelligence < 0 || chase.attr.money < 0);
  chase.attr.intelligence = 0;
  chase.attr.money = 0;
  cout << "\tPassed..." << endl;
  cout << "\tCase 2: Tester should answer question correctly."
       << endl << "\tAnswer is the same as question." << endl;
  puzzle(chase, &quiz);
  assert(chase.attr.intelligence > 0 || chase.attr.money > 0);
  cout << "\tPassed..." << endl;
}

void test_professor()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  int i{};
  cout.setstate(ios::badbit);
  for (int j = 0; j < 100; j++) {
    professor(chase, nullptr);
    assert(chase.attr.time != 0);
    if (chase.attr.intelligence != 0) {
      chase.attr.intelligence = 0;
      i++;
    }
  }
  cout.clear();
  //user should have randomly gained intelligence
  assert(i != 0);
  cout << "\tPassed..." << endl;
}

void test_grad_student()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  cout.setstate(ios::badbit);
  for (int i = 0; i < 100; i++) {
    grad_student(chase, nullptr);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence == 0);
    assert(chase.attr.money <= 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout.clear();
  cout << "\tPassed..." << endl;
}

void test_grade_papers()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  cout.setstate(ios::badbit);
  for (int i = 0; i < 100; i++) {
    grade_papers(chase, nullptr);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence == 0);
    assert(chase.attr.money != 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout.clear();
  cout << "\tPassed..." << endl;
}

void test_generate_encounter()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  for (int i = 0; i < 10; i++) {
    if (quiz.num_elements == 0)
      quiz = init_quiz_list("test_quiz.txt");
    generate_encounter()(chase, &quiz);
    
    //time always modified by encounters
    assert(chase.attr.time != 0);
    chase.attr.time = 0;
  }
  cout << "\tPassed..." << endl;
}

//test move character
void test_move_character()
{
  user chase{"Chase", 0, user_prop{1,1,1}};
  cout << "\tCase 1: Testing move character. (Is position incremented?)" << endl;
  move_character(chase, quiz);
  assert(chase.pos != 0);
  assert(chase.attr.time != 1);
  cout << "\tPassed..." << endl;
  cout << "\tCase 2: Tester should verify random encounter generated." << endl;
  //statistically unlikely that case 2 would accidently fail.
  for (int i = 0; i < 10; i++) {
    move_character(chase, quiz);
  }
  cout << "\tPassed..." << endl;
}

void test_read_technical_paper()
{
  user chase{"Chase", 0, user_prop{1,1,1}};
  cout << "\tCase 1: Checking that user intelligence increased and time decreased."
       << endl;
  read_technical_paper(chase);
  assert(chase.attr.intelligence != 1);
  assert(chase.attr.time != 1);
  cout << "\tPassed..." << endl;
}

void test_search_for_loose_change()
{
  user chase{"Chase", 0, user_prop{1,1,1}};
  cout << "\tCase 1: Checking that user money increased and time decreased."
       << endl;
  read_technical_paper(chase);
  assert(chase.attr.money != 1);
  assert(chase.attr.time != 1);
  cout << "\tPassed..." << endl;
}
