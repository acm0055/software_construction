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
 * filename: hw3.cpp
 * Development Environment: g++, Linux, emacs, make
 * Version: 2/5/2016
 * Compile: make
 * Sample usage: ./hw3
 * Sources: I did not use any sources for this assignment.
 * 
 * Tests functions relating to a dual simulator
 * between three parties Aaron, Bob, and Charlie.
 * Runs the simulation for 2 of Aaron's strategies
 * and determines the better of the two from Aaron's perspective.
 */

#include<iostream>
#include<ctime>
#include<cstdlib>
#include "test.h"
#include "puzzler_shooting_gallery.h"
using namespace std;

const int TOTAL_ITERATIONS{10000};

char who_alive(bool, bool, bool);

//Runs tests and simulations
//on the dual simulator
int main() {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  double kill_percent{};
  bool aaron_state{false};
  bool bob_state{false};
  bool charlie_state{false};
  int num_aaron_alive_1{};
  int num_aaron_alive_2{};
  int num_bob_alive{};
  int num_charlie_alive{};

  //seed rng
  srand(time(0));
  
  //Run Tests
  run_all_tests();
  
  //Strategy 1 simulation//

  cout  << "Ready to test strategy 1 (run " << TOTAL_ITERATIONS
        << " times):\nPress any key to continue...\n"
	<< "\n...\n...\n...\n";
  cin.ignore().get();
  
  for(int i = 0; i < TOTAL_ITERATIONS; i++) {
    //initialization
    aaron_state = bob_state = charlie_state = true;
    while(at_least_two_alive(aaron_state, bob_state, charlie_state)) {
	if(aaron_state)
	  aaron_shoots1(bob_state, charlie_state);
	if(bob_state)
	  bob_shoots(aaron_state, charlie_state);
	if(charlie_state)
	  charlie_shoots(aaron_state, bob_state);
      }
    switch(who_alive(aaron_state, bob_state, charlie_state)) {
      case 'a':
	num_aaron_alive_1++;
	break;
      case 'b':
	num_bob_alive++;
	break;
      default:
	num_charlie_alive++;
      }
  }

  //How many times Aaron wins
  kill_percent = static_cast<double> (num_aaron_alive_1) / TOTAL_ITERATIONS * 100;
  cout << "Aaron won " << num_aaron_alive_1 << "/"
       << TOTAL_ITERATIONS << " duels or " << kill_percent << "%\n";
  //How many times Bob wins
  kill_percent = static_cast<double> (num_bob_alive) / TOTAL_ITERATIONS * 100;
  cout << "Bob won " << num_bob_alive << "/"
       << TOTAL_ITERATIONS << " duels or " << kill_percent << "%\n";
  //How many times Charlie wins
  kill_percent = static_cast<double> (num_charlie_alive) / TOTAL_ITERATIONS * 100;
  cout << "Charlie won " << num_charlie_alive << "/"
       << TOTAL_ITERATIONS << " duels or " << kill_percent << "%\n\n";

  //Strategy 2 simulation//

  //reinitialize win counts
  num_aaron_alive_2 = num_bob_alive = num_charlie_alive = 0;
  
  cout  << "Ready to test strategy 2 (run " << TOTAL_ITERATIONS
        << " times):\nPress any key to continue...\n"
	<< "\n...\n...\n...\n";
  cin.ignore().get();
  
  for(int i = 0; i < TOTAL_ITERATIONS; i++) {
    //initialization
    aaron_state = bob_state = charlie_state = true;
    while(at_least_two_alive(aaron_state, bob_state, charlie_state)) {
	if(aaron_state)
	  aaron_shoots2(bob_state, charlie_state);
	if(bob_state)
	  bob_shoots(aaron_state, charlie_state);
	if(charlie_state)
	  charlie_shoots(aaron_state, bob_state);
      }
    switch(who_alive(aaron_state, bob_state, charlie_state)) {
      case 'a':
	num_aaron_alive_2++;
	break;
      case 'b':
	num_bob_alive++;
	break;
      default:
	num_charlie_alive++;
      }
  }

  //How many times Aaron wins
  kill_percent = static_cast<double> (num_aaron_alive_2) / TOTAL_ITERATIONS * 100;
  cout << "Aaron won " << num_aaron_alive_2 << "/"
       << TOTAL_ITERATIONS << " duels or " << kill_percent << "%\n";
  //How many times Bob wins
  kill_percent = static_cast<double> (num_bob_alive) / TOTAL_ITERATIONS * 100;
  cout << "Bob won " << num_bob_alive << "/"
       << TOTAL_ITERATIONS << " duels or " << kill_percent << "%\n";
  //How many times Charlie wins
  kill_percent = static_cast<double> (num_charlie_alive) / TOTAL_ITERATIONS * 100;
  cout << "Charlie won " << num_charlie_alive << "/"
       << TOTAL_ITERATIONS << " duels or " << kill_percent << "%\n";

  //Results
  if(num_aaron_alive_1 > num_aaron_alive_2)
    cout << "Strategy 1 is better than strategy 2.\n";
  else
    cout << "Strategy 2 is better than strategy 1.\n\n";
  
  return 0;
}

//Function for determining who is still alive
//Returns a lower case char represent first letter
//of the name of the person still alive
char who_alive(bool aaron_state, bool bob_state, bool charlie_state) {
  if(aaron_state)
    return 'a';
  if(bob_state)
    return 'b';
  if(charlie_state)
    return 'c';
  cerr << "Violation of program invarient. No one left alive.\n"
       << "Exiting\n";
  exit(1);
}
