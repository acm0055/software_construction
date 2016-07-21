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
 * DISCLAIMED. IN NO EVENT SHALL Austin Chase Minor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Name: Austin Minor
 * Auburn UserID: 903223922
 * filename: test.cpp
 * Development Environment: emacs, g++, Linux, make
 * Version: 2/4/16
 * Compile: compiled as part of the main program
 * Sources: I did not use any sources for this assignment.
 *
 * Testing interface for shooter program.
 */

#include<iostream>
#include<cmath>
#include "test.h"
#include"puzzler_shooting_gallery.h"
#include <cstdlib>
#include<cassert>
using namespace std;

//Runs tests on all the methods of the shooter
//program and does so with a simple text interface.
void run_all_tests() {
  cout << "*** Welcome to Austin Minor's Duel Simulator ***\n";
  
  cout << "Unit Testing 1: Function at_least_two_alive()\n";
  run_at_least_two_alive_test();
  cout << "Press any key to contine...";
  cin.ignore().get();
  
  cout << "Unit Testing 2: Function aaron_shoots1(Bob_alive, Charlie_alive)\n";
  run_aaron_shoots_1_test();
  cout << "Press any key to contine...";
  cin.ignore().get();
  
  cout << "Unit Testing 3: Function aaron_shoots2(Bob_alive, Charlie_alive)\n";
  run_aaron_shoots_2_test();
  cout << "Press any key to contine...";
  cin.ignore().get();
  
  cout << "Unit Testing 4: Function bob_shoots(Aaron_alive, Charlie_alive)\n";
  run_bob_shoots_test();
  cout << "Press any key to contine...";
  cin.ignore().get();
  
  cout << "Unit Testing 5: Function charlie_shoots(Aaron_alive, Bob_alive)\n";
  run_charlie_shoots_test();
  cout << "Press any key to contine...";
  cin.ignore().get();
}

//Tests the two alive method
void run_at_least_two_alive_test() {
  cout << "\t\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
  assert(at_least_two_alive(true, true, true));
  cout << "\t\tCase passed ...\n";
  
  cout << "\t\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
  assert(at_least_two_alive(false, true, true));
  cout << "\t\tCase passed ...\n";
  
  cout << "\t\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
  assert(at_least_two_alive(true, false, true));
  cout << "\t\tCase passed ...\n";
  
  cout << "\t\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
  assert(at_least_two_alive(true, true, false));
  cout << "\t\tCase passed ...\n";
	 
  cout << "\t\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
  assert(!at_least_two_alive(false, false, true));
  cout << "\t\tCase passed ...\n";

  cout << "\t\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
  assert(!at_least_two_alive(false, true, false));
  cout << "\t\tCase passed ...\n";
	 
  cout << "\t\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
  assert(!at_least_two_alive(true, false, false));
  cout << "\t\tCase passed ...\n";

  cout << "\t\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
  assert(!at_least_two_alive(false, false, false));
  cout << "\t\tCase passed ...\n";
}

//Tests the aaron method for shooting strategy 1
void run_aaron_shoots_1_test() {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  double kill_percent{};
  double expected_kill_percent{0.33};
  double total_iterations{10000};
  bool aaron_state{false};
  bool bob_state{false};
  bool charlie_state{false};
  double tolerance{0.7};
  int num_bob_dies{};
  int num_charlie_dies{};
  
  ////////////////////////////////
  //Case 1: Bob alive, Charlie alive
  ///////////////////////////////
  cout << "\tCase 1: Bob alive, Charlie alive\n"
       << "\t\tAaron is shooting at Charlie\n";
  for(int i = 0; i < total_iterations; i++) {
    bob_state = true;
    charlie_state = true;
    aaron_shoots1(bob_state, charlie_state);
    //bob should not be shot at first
    assert(bob_state);
    if(!charlie_state)
      num_charlie_dies++;
  }
  kill_percent = num_charlie_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tAaron hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 2: Bob alive, Charlie dead
  ///////////////////////////////
  cout << "\tCase 2: Bob alive, Charlie dead\n"
       << "\t\t Aaron is shooting at Bob\n";
  num_bob_dies = 0;
   for(int i = 0; i < total_iterations; i++) {
    bob_state = true;
    charlie_state = false;
    aaron_shoots1(bob_state, charlie_state);
    if(!bob_state)
      num_bob_dies++;
  }
   kill_percent = num_bob_dies / total_iterations;
   //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tAaron hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 3: Bob dead, Charlie alive
  ///////////////////////////////
  cout << "\tCase 3: Bob dead, Charlie alive\n"
       << "\t\t Aaron is shooting at Charlie\n";
  num_charlie_dies = 0;
  for(int i = 0; i < total_iterations; i++) {
    bob_state = false;
    charlie_state = true;
    aaron_shoots1(bob_state, charlie_state);
    if(!charlie_state)
      num_charlie_dies++;
  }
  kill_percent = num_charlie_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tAaron hits " << kill_percent * 100
       << "% of the time\n";
}

//Tests the aaron method for shooting strategy 2
void run_aaron_shoots_2_test() {
    cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  double kill_percent{};
  double expected_kill_percent{0.33};
  double total_iterations{10000};
  bool aaron_state{false};
  bool bob_state{false};
  bool charlie_state{false};
  double tolerance{0.7};
  int num_bob_dies{};
  int num_charlie_dies{};
  
  ////////////////////////////////
  //Case 1: Bob alive, Charlie alive
  ///////////////////////////////
  cout << "\tCase 1: Bob alive, Charlie alive\n"
       << "\t\tAaron is shooting at Charlie\n";
  for(int i = 0; i < total_iterations; i++) {
    bob_state = true;
    charlie_state = true;
    aaron_shoots2(bob_state, charlie_state);
    //no one should be shot on first round
    assert(bob_state);
    assert(charlie_state);
  }
  cout << "\t\tAaron intenionally misses\n";

  ////////////////////////////////
  //Case 2: Bob alive, Charlie dead
  ///////////////////////////////
  cout << "\tCase 2: Bob alive, Charlie dead\n"
       << "\t\tAaron is shooting at Bob\n";
  num_bob_dies = 0;
   for(int i = 0; i < total_iterations; i++) {
    bob_state = true;
    charlie_state = false;
    aaron_shoots2(bob_state, charlie_state);
    if(!bob_state)
      num_bob_dies++;
  }
   kill_percent = num_bob_dies / total_iterations;
   //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tAaron hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 3: Bob dead, Charlie alive
  ///////////////////////////////
  cout << "\tCase 3: Bob dead, Charlie alive\n"
       << "\t\tAaron is shooting at Charlie\n";
  num_charlie_dies = 0;
  for(int i = 0; i < total_iterations; i++) {
    bob_state = false;
    charlie_state = true;
    aaron_shoots2(bob_state, charlie_state);
    if(!charlie_state)
      num_charlie_dies++;
  }
  kill_percent = num_charlie_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tAaron hits " << kill_percent * 100
       << "% of the time\n";
}

//Tests the bob shoots method
void run_bob_shoots_test() {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  double kill_percent{};
  double expected_kill_percent{0.5};
  double total_iterations{10000};
  bool aaron_state{false};
  bool charlie_state{false};
  double tolerance{0.7};
  int num_aaron_dies{};
  int num_charlie_dies{};
  
  ////////////////////////////////
  //Case 1: Aaron alive, Charlie alive
  ///////////////////////////////
  cout << "\tCase 1: Aaron alive, Charlie alive\n"
       << "\t\tBob is shooting at Charlie\n";
  for(int i = 0; i < total_iterations; i++) {
    aaron_state = true;
    charlie_state = true;
    bob_shoots(aaron_state, charlie_state);
    //aaron should not be shot at first
    assert(aaron_state);
    if(!charlie_state)
      num_charlie_dies++;
  }
  kill_percent = num_charlie_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tBob hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 2: Aaron alive, Charlie dead
  ///////////////////////////////
  cout << "\tCase 2: Aaron alive, Charlie dead\n"
       << "\t\tBob is shooting at Aaron\n";
  num_aaron_dies = 0;
   for(int i = 0; i < total_iterations; i++) {
    aaron_state = true;
    charlie_state = false;
    bob_shoots(aaron_state, charlie_state);
    if(!aaron_state)
      num_aaron_dies++;
  }
   kill_percent = num_aaron_dies / total_iterations;
   //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tBob hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 3: Aaron dead, Charlie alive
  ///////////////////////////////
  cout << "\tCase 3: Aaron dead, Charlie alive\n"
       << "\t\tBob is shooting at Charlie\n";
  num_charlie_dies = 0;
  for(int i = 0; i < total_iterations; i++) {
    aaron_state = false;
    charlie_state = true;
    bob_shoots(aaron_state, charlie_state);
    if(!charlie_state)
      num_charlie_dies++;
  }
  kill_percent = num_charlie_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tBob hits " << kill_percent * 100
       << "% of the time\n";
}

//Tests the charlie shoots method
void run_charlie_shoots_test() {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  double kill_percent{};
  double expected_kill_percent{1};
  double total_iterations{10000};
  bool aaron_state{false};
  bool bob_state{false};
  double tolerance{0.7};
  int num_aaron_dies{};
  int num_bob_dies{};
  
  ////////////////////////////////
  //Case 1: Aaron alive, Bob alive
  ///////////////////////////////
  cout << "\tCase 1: Aaron alive, Bob alive\n"
       << "\t\tCharlie is shooting at Bob\n";
  for(int i = 0; i < total_iterations; i++) {
    aaron_state = true;
    bob_state = true;
    charlie_shoots(aaron_state, bob_state);
    //aaron should not be shot at first
    assert(aaron_state);
    if(!bob_state)
      num_bob_dies++;
  }
  kill_percent = num_bob_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tCharlie hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 2: Aaron alive, Bob dead
  ///////////////////////////////
  cout << "\tCase 2: Aaron alive, Bob dead\n"
       << "\t\tCharlie is shooting at Aaron\n";
  num_aaron_dies = 0;
   for(int i = 0; i < total_iterations; i++) {
    aaron_state = true;
    bob_state = false;
    charlie_shoots(aaron_state, bob_state);
    if(!aaron_state)
      num_aaron_dies++;
  }
   kill_percent = num_aaron_dies / total_iterations;
   //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tCharlie hits " << kill_percent * 100
       << "% of the time\n";

  ////////////////////////////////
  //Case 3: Aaron dead, Bob alive
  ///////////////////////////////
  cout << "\tCase 3: Aaron dead, Bob alive\n"
       << "\t\tCharlie is shooting at Bob\n";
  num_bob_dies = 0;
  for(int i = 0; i < total_iterations; i++) {
    aaron_state = false;
    bob_state = true;
    charlie_shoots(aaron_state, bob_state);
    if(!bob_state)
      num_bob_dies++;
  }
  kill_percent = num_bob_dies / total_iterations;
  //wrong kill ratio
  assert(abs(kill_percent - expected_kill_percent) < tolerance);
  cout << "\t\tCharlie hits " << kill_percent * 100
       << "% of the time\n";
}
