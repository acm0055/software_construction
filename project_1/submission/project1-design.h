//////////////////////////////////////////////////////////
//Project 1                                             //
//This is a utility header for the Dragons game.        //
//Contained herein is the data structures and functions //
//necessary to play a game of Dragons.                  //
//Author: Austin Chase Minor                            //
//Version: 3/28/16                                      //
//Sources: stackoverflow for function pointer syntax    //
//////////////////////////////////////////////////////////
#include <string>
#include <fstream>
#include <vector>

#ifndef PROJECT1_DESIGN
#define PROJECT1_DESIGN 1
struct user_prop {
  char time;
  char money;
  char intelligence;
};

struct user {
  std::string name;
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
  std::string question;
  std::string answer;
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
const std::string high_score_file{"high_scores.txt"};
const std::string quiz_file{"quiz_questions.txt"};
////////////////
//Quiz methods//
////////////////

//Adds question to list based on
//question properties. Does this
//for a global list.
void add_question(std::string question, std::string ans, user_prop mods);
//Removes the tail of the list and
//adjusts list properties likewise.
quiz_node* remove_question();
//Parses a single question from a text file and
//returns the question.
quiz_node* parse_question(std::ifstream& file);
//Parses the user property string to form
//the list of user properties.
user_prop parse_user_prop(std::string props);

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
#endif /*PROJECT1_DESIGN*/
