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
 * filename: hw5.cpp
 * Development Environment: Linux emacs gcc
 * Version: 2/28/16
 * Compile: g++ hw5.cpp -std=c++0x -o hw5
 * Sample usage: ./hw5
 * Sources: node structure influence from Bjarne Stroustrup The C++ Programming Language 4th Edition &&
 *                  last node  access algorithm influenced by Dr. Hendrix of Auburn University
 */
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

//#define UNIT_TESTING

//Linked List Structure
//for trivia questions
//Bjarne Stroustrup
struct TriviaNode {
  TriviaNode* next_question;
  int value;
  string question;
  string answer;
};

//Number of trivia questions
int NUMBER_OF_QUESTIONS{0};

//Function Declarations
TriviaNode* initialize_trivia_game();
TriviaNode* add_trivia_question(TriviaNode*);
void quiz_user(TriviaNode*,  int&, int);

#ifdef UNIT_TESTING
//Unique testing function declarations
void initialize_trivia_game_test();
void add_trivia_question_test();
void quiz_user_test();

//Main testing driver for a
//the quiz user program
int main() {
  cout << "*** This is a debugging version ***\n";
  TriviaNode* quiz = initialize_trivia_game();
  int score{0};

  cout << "Unit Test Case 1: Ask no question. The program"
       << " should give a warning message.\n";
  quiz_user(quiz, score, 0);

  cout << "Unit Test Case 2.1: Ask 1 question in the linked list."
       << " The tester enters an incorrect answer.\n";
  quiz_user(quiz, score, 1);
  //Score should not change.
  assert(score == 0);

  cout << "Unit Test Case 2.2: Ask 1 question in the linked list."
       << " Thes tester enters a correct answer.\n";
  quiz_user(quiz, score, 1);
  //Score should not be equal to zero.
  assert(score != 0);

  cout << "Unit Test Case 3: Ask all the questions of the last"
       << " trivia in the linked list. The tester should check that"
       << " three questions are asked.\n";
  quiz_user(quiz, score, NUMBER_OF_QUESTIONS);
  //Nothing can be guarenteed about the score for this test.

  cout << "Unit Test Case 4: Ask five questions in the linked list."
       << " The program should give a warning message because"
       << " their are not five questions in the testing list.\n";
  quiz_user(quiz, score, 5);

  cout << "*** End of the Debugging Version ***\n";
}

#else

//Main driver for a quiz game
//Lets the user create questions
//Play with those questions or
//Play with a set of default questions
int main() {
  cout << "*** Welcome to Austin Minor's trivia quiz game ***\n";

  int game_switch{};
  cout << "Would you like to create your own game (1) or play a default game (2)? (1/2): ";
  string user_input;

  //Input user input with type checking to prevent errors.
  cin >> user_input;
  try {
    game_switch = stoi(user_input);
  }
  catch(...) {
    cerr << "Wrong score type. Exiting.\n";
    exit(1);
  }

  TriviaNode* list = nullptr;
  switch (game_switch) {
  case 1:
    do {
      list = add_trivia_question(list);
      cout << "Continue? (Yes/No): ";
      //guard for whitespace corruption
      (cin.peek() == '\r') ? cin.ignore(): cin;
      (cin.peek() == '\n') ? cin.ignore(): cin;
      //prevent over flow from whitespace seperated string
      getline(cin, user_input);
      //only checks for no's all other input deamed as yes's
    } while(user_input != "No" && user_input != "no" && user_input != "n");
    break;
  case 2:
    list = initialize_trivia_game();
    break;
  default:
    cerr << "Wrong input answer. Exiting.\n";
    return 1;
  }

  (cin.peek() == '\r') ? cin.ignore(): cin;
  (cin.peek() == '\n') ? cin.ignore(): cin;
  

  int score{};
  quiz_user(list, score, NUMBER_OF_QUESTIONS);

  cout << "You scored " << score
       << " points. Thanks for playing!\n";
  cout << "*** Thank you for playing the"
       << " trivia quiz game. Goodbye!***\n";
}
#endif
//Initialize trivia game with a set of three
//default questions. Returns a trivia game
//represented by a linked list.
TriviaNode* initialize_trivia_game() {
  TriviaNode* question = new TriviaNode();
  question->question = "How long was the shortest war on record? (Hint: how many minutes)";
  question->answer = "38";
  question->value = 100;
  question->next_question = nullptr;
  NUMBER_OF_QUESTIONS++;

  TriviaNode* prev = question;
  question = new TriviaNode();
  question->question = "What was Bank of America's original name?"
    "(Hint: Bank of Italy or Bank of Germany)?";
  question->answer = "Bank of Italy";
  question->value = 50;
  question->next_question = prev;
  NUMBER_OF_QUESTIONS++;
  
  prev = question;
  question = new TriviaNode();
  question->question = "What is the best-selling video game of all"
    " time? (Hint: Call of Duty or Wii Sports)?";
  question->answer = "Wii Sports";
  question->value = 50;
  question->next_question = prev;
  NUMBER_OF_QUESTIONS++;

  return question;
}

//Lets the client add a trivia question to a list
//Returns the modified trivia quiz pointer
//This is to allow for passing in an empty (nullptr) list
TriviaNode* add_trivia_question(TriviaNode* list) {
  TriviaNode* question = new TriviaNode();

  cout << "Enter a question: ";
  //guard for whitespace corruption
  (cin.peek() == '\r') ? cin.ignore(): cin;
  (cin.peek() == '\n') ? cin.ignore(): cin;
  getline(cin, question->question);

  cout << "Enter an answer: ";
  (cin.peek() == '\r') ? cin.ignore(): cin;
  (cin.peek() == '\n') ? cin.ignore(): cin;
  getline(cin, question->answer);

  cout << "Enter award points: ";
  string temp_value;
  getline(cin, temp_value);
  try {
    question->value = stoi(temp_value);
  }
  catch(...) {
    cerr << "Wrong score type. Exiting.\n";
    exit(1);
  }
  //  cin >> question->value;

  //rather inefficient way of adding a new entry
  //however without a tail node impossible to improve
  //Dr. Hendrix
  TriviaNode* prev = list;
  TriviaNode* current = list;
  while(current) {
    prev = current;
    current = current->next_question;
  }

  if (prev)
    prev->next_question = question;
  else
    list = question;

  NUMBER_OF_QUESTIONS++;

  return list;
}

//Quizes user and updates the score
//The client passes in an individual question
//and the users score to be modified based on correctness
void quiz_user(TriviaNode* question, int& score, int num_questions) {
  string user_ans;

  if (num_questions < 1) {
    cerr << "Warning - The number of trivia to be asked"
	 << " must equal to or larger than 1.\n";
    return;
  }
  if (num_questions > NUMBER_OF_QUESTIONS) {
    cerr << "Warning - There are only three trivia in the list.\n";
    return;
  }

  //Loops through asking user question with
  //an additional null check to prevent program crashes.
  for (int i = 0; i < num_questions && question; i++) {

    cout << "Question: " << question->question
	 << endl;

    cout << "Answer: ";
    //guard for whitespace corruption
    (cin.peek() == '\r') ? cin.ignore(): cin;
    (cin.peek() == '\n') ? cin.ignore(): cin;
    getline(cin, user_ans);

    if (question->answer == user_ans) {
      cout << "Your answer is correct. You"
	   << " recieve " << question->value << " points.\n";
      score += question->value;
    }
    else
      cout << "Your answer is incorrect. The correct answer is: "
	   << question->answer << endl;

    //set up next question
    question = question->next_question;
  }
}
