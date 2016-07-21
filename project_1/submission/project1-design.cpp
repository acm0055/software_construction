//////////////////////////////////////////////////////////
//Project 1                                             //
//This is a utility header for the Dragons game.        //
//Contained herein is the data structures and functions //
//necessary to play a game of Dragons.                  //
//Author: Austin Chase Minor                            //
//Auburn UserID: 903223922                              //
//Development Environment: Linux emacs gcc              //
//Version: 3/30/16                                      //
//Sources: stackoverflow for function pointer syntax    //
//Compile: g++ -std=c++0x -o hw6 hw6.cpp                //
//Sample Usage: no sample usage                         //
//////////////////////////////////////////////////////////
#include <string>
#include <fstream>
#include "project1-design.h"
#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

#ifndef PROJECT1_DESIGN
#define PROJECT1_DESIGN 1
struct user_prop {
  char time;
  char money;
  char intelligence;
};

struct user {
  string name;
  unsigned short pos;
  user_prop attr;
};

enum class encounter {
    grunt_work = 0,
    do_nothing,
    puzzle,
    professor,
    grad_student,
    grade_papers
};

//Pointer to generic encounter function
//syntax fix from http://stackoverflow.com/
//  questions/4295432/typedef-function-pointer
typedef void(*encounter_func)(user& user_in);

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

struct score_node {
  score_node *next;
  unsigned short score;
};

struct score_list {
  score_node *head;
  score_node *tail;
  int num_elements;
  int max_num_elements;
};

///////////////////////////////////////
//Globals Only One Copy Should Exist //
///////////////////////////////////////

//Globals used because of lack of knowledge
//of how to implement a singleton in c
//and to restrict the complexities of function calls.
quiz_list quiz;
encounter_func* encounter_array;
score_list score_board;
const string high_score_file{"high_scores.txt"};
const string quiz_file{"quiz_questions.txt"};
////////////////
//Quiz methods//
////////////////

//Adds question to list based on
//question properties. Does this
//for a global list.
void add_question(string question, string ans, user_prop mods);
//Removes the tail of the list and
//adjusts list properties likewise.
quiz_node* remove_question();
//Parses a single question from a text file and
//returns the question.
quiz_node* parse_question(ifstream& file);
//Parses the user property string to form
//the list of user properties.
user_prop parse_user_prop(string props);

///////////////////
//General methods//
///////////////////

//Modifies the users properties
//based on the modifications presented.
void mod_user_prop(user_prop& prop, const user_prop& mods);
//Initializes the globals of the program.
void init_globals();
//Initializes the global quiz list from a predefined quiz file.
void init_quiz_list();
//Move the character and generate a random encounter.
void move_character(user& user_in);
//Reading tech papers boosts intelligence and loses time.
void read_technical_paper(user& user_in);
//Searches for loose change boosts money and loses time.
void search_for_loose_change(user& user_in);
//Displays character and his/her stats
void view_character(user& user_in);

/////////////////////
//Encounter methods//
/////////////////////

//Returns an encounter based on the random
//probilities specified in the program design doc.
encounter_func generate_encounter();
//Modifies user according to the specifications of grunt work
void grunt_work(user& user_in);
//Modifies user according to the specifications of do nothing
void do_nothing(user& user_in);
//Modifies user according to the specifications of puzzle.
//Asks user a puzzle question and removes that question from
//the puzzle list.
void puzzle(user& user_in);
//Modifies user according to the specifications of professor
void professor(user& user_in);
//Modifies user according to the specifications of grad student
void grad_student(user& user_in);
//Modifies user according to the specifications of grade papers
void grade_papers(user& user_in);

////////////////
//Menu methods//
////////////////

//Displays the start menu and
//accepts user input modifying the
//program execution accordingly.
void start_menu();
//Displays the game move select and
//accepts user input modifying the
//program execution accordingly.
void move_select();
//Displays the top 5 high scores of
//the Dragons game.
void display_high_scores();
//Updates the high scores list
//based if the user is in the
//top 5 scores or not.
void write_high_scores(user& user_in);
#endif

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
void test_init_globals();
void test_generate_encounter();

#define TESTING 1
#ifdef TESTING
//Run all tests
int main() {
  //order of test cases is important do to globals
  test_add_question();
  test_remove_question();
  test_parse_question();
  test_do_nothing();
  test_grad_student();
  test_grade_papers();
  test_grunt_work();
  test_professor();
  test_puzzle();
  test_mod_user_prop();
  test_init_globals();
  test_generate_encounter();
}

void test_add_question()
{
  cout << "\tCase 1: Standard Quiz Node";
  add_question("Test","Test",user_prop{});
  cout << "\t\tCase 1.1: Size Change";
  assert(quiz.num_elements == 1);
  cout << "\t\tPassed...";
  cout << "\t\tCase 1.2: Proper List";
  assert(quiz.head == quiz.tail);
  assert(quiz.head->next == nullptr);
  cout << "\t\tPassed...";
  cout << "\t\tCase 1.2: Proper Node";
  assert(quiz.head->question == "Test");
  assert(quiz.head->answer == "Test");
  assert(quiz.head->mods.time == 0);
  assert(quiz.head->mods.money == 0);
  assert(quiz.head->mods.intelligence == 0);
  cout << "\t\tPassed...";
  //clean up
  remove_question();
  cout << "\tPassed...";
}

void test_remove_question()
{
  cout << "\tCase 1: Empty List";
  assert(remove_question() == nullptr);
  assert(quiz.num_elements == 0);
  cout << "\tPassed...";
  
  cout << "\tCase 2: One Element List";
  cout << "\t\tCase 2.1: Proper List";
  add_question("Test","Test",user_prop{});
  assert(quiz.num_elements == 1);
  quiz_node* temp = remove_question();
  assert(quiz.head == nullptr);
  assert(quiz.tail == nullptr);
  cout << "\t\tPassed...";
  cout << "\t\tCase 2.2: Proper Node";
  assert(temp->question == "Test");
  assert(temp->answer == "Test");
  assert(temp->mods.time == 0);
  assert(temp->mods.money == 0);
  assert(temp->mods.intelligence == 0);
  assert(quiz.num_elements == 0);
  delete temp;
  cout << "\t\tPassed...";
  cout << "\tPassed...";
  
  cout << "\tCase 3: Average List";
  add_question("Test","Test",user_prop{});
  add_question("Test","Test",user_prop{});
  add_question("Test","Test",user_prop{});
  add_question("Test","Test",user_prop{});
  assert(quiz.num_elements == 4);
  temp = remove_question();
  delete temp;
  temp = remove_question();
  delete temp;
  temp = remove_question();
  delete temp;
  temp = remove_question();
  delete temp;
  assert(quiz.num_elements == 0);
  cout << "\tPassed...";
}

//parse_user_props implicitly in this test
void test_parse_question()
{
  ifstream unknown_file{"unknown"};
  quiz_node* temp = parse_question(unknown_file);
  assert(temp == nullptr);
  
  ifstream test_file{"test_quiz.txt"};
  assert(test_file.is_open());
  
  temp = parse_question(test_file);
  assert(temp->question == "Test");
  assert(temp->answer == "Test");
  assert(temp->mods.time == 0);
  assert(temp->mods.money == 0);
  assert(temp->mods.intelligence == 0);
  assert(temp->next == nullptr);
  delete temp;

  temp = parse_question(test_file);
  assert(temp->question == "Test Test");
  assert(temp->answer == "Test Test");
  assert(temp->mods.time == 0);
  assert(temp->mods.money == 0);
  assert(temp->mods.intelligence == 0);
  assert(temp->next == nullptr);
  delete temp;
  test_file.close();
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
  for (int i = 0; i < 100; i++ ) {
    grunt_work(chase);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence != 0);
    assert(chase.attr.money == 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout << "\tPassed..." << endl;
}

void test_do_nothing()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  for (int i = 0; i < 100; i++) {
    do_nothing(chase);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence == 0);
    assert(chase.attr.money == 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout << "\tPassed..." << endl;
}

void test_puzzle()
{
  user chase{"chase", 0, user_prop{}};
  cout << "\tCase 1: No questions left in list." << endl;
  cout << "\t+Tester should verify that a question did indeeded appear." << endl;
  puzzle(chase);
  cout << "\tPassed..." << endl;
  cout << "\tCase 2: Tester should miss question." << endl;
  puzzle(chase);
  assert(chase.attr.intelligence < 0 || chase.attr.money < 0);
  chase.attr.intelligence = 0;
  chase.attr.money = 0;
  cout << "\tPassed..." << endl;
  cout << "\tCase 3: Tester should answer question correctly." << endl;
  puzzle(chase);
  assert(chase.attr.intelligence > 0 || chase.attr.money > 0);
  cout << "\tPassed..." << endl;
}

void test_professor()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  int i{};
  for (int j = 0; j < 100; j++) {
    professor(chase);
    assert(chase.attr.time != 0);
    if (chase.attr.intelligence != 0) {
      chase.attr.intelligence == 0;
      i++;
    }
  }
  //user should have randomly gained intelligence
  assert(i != 0);
  cout << "\tPassed..." << endl;
}

void test_grad_student()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  for (int i = 0; i < 100; i++) {
    grad_student(chase);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence == 0);
    assert(chase.attr.money == 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout << "\tPassed..." << endl;
}

void test_grade_papers()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  for (int i = 0; i < 100; i++) {
    grad_student(chase);
    assert(chase.attr.time != 0);
    assert(chase.attr.intelligence != 0);
    assert(chase.attr.money != 0);
    chase.attr.time = 0;
    chase.attr.intelligence = 0;
    chase.attr.money = 0;
  }
  cout << "\tPassed..." << endl;
}

void test_generate_encounter()
{
  cout << "\tCase 1: Testing over iterations." << endl;
  user chase{"chase", 0, user_prop{}};
  for (int i = 0; i < 100; i++) {
    generate_encounter()(chase);
    //time always modified by encounters
    assert(chase.attr.time != 0);
    chase.attr.time = 0;
  }
  cout << "\tPassed..." << endl;
}

//implicitly test init quiz list
void test_init_globals()
{
  cout << "\tCase 1: Testing global quiz list initialization." << endl;
  init_globals();
  assert(quiz.num_elements != 0);
  assert(encounter_array != nullptr);
  cout << "\tPassed..." << endl;
}

//test move character
void test_move_character()
{
  user chase{"Chase", 0, user_prop{1,1,1}};
  cout << "\tCase 1: Testing move character. (Is position incremented?)" << endl;
  move_character(chase);
  assert(chase.pos != 0);
  assert(chase.attr.time != 1);
  cout << "\tPassed..." << endl;
  cout << "\tCase 2: Tester should verify random encounter generated." << endl;
  //statistically unlikely that case 2 would accidently fail.
  for (int i = 0; i < 10; i++) {
    move_character(chase);
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
#endif
