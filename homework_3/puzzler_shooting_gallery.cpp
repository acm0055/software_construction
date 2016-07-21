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
 * filename: puzzler_shooting_gallery.cpp
 * Development Environment: emacs, g++, Linux, make
 * Version: 2/4/16
 * Compile: compiled as part of the main program
 * Sources: I did not use any sources for this assignment.
 *
 * Methods for simulating a duel between three parties
 * Aaron, Bob, and Charlie with two seperate strategies for Aaron.
 */
#include "puzzler_shooting_gallery.h"
#include <cstdlib>
#include <iostream>
using namespace std;

const int AARON_HIT_RATIO{33};
const int BOB_HIT_RATIO{50};
const int CHARLIE_HIT_RATIO{100};

//Tests to see if at least two people are alive
//and thus the shooting game is not over.
bool at_least_two_alive(bool aaron, bool bob, bool charlie) {
  //count for the number of people still alive
  int count{};

  if(aaron)
    count++;
  if(bob)
    count++;
  if(charlie)
    count++;

  return (count > 1);
}
//Aaron shoots at the person with the
//highest possible hit chance first.
//He has a 33% hit ratio.
//Inputs are modified to reflect result of shot.
void aaron_shoots1(bool& bob, bool& charlie) {
  int rand_num{};
  if(charlie) {
    rand_num = rand() % 100;
    //cout << "rand: " << rand_num << endl;
    //Shift becuase indexing is from 0 - 99
    if(rand_num <= AARON_HIT_RATIO - 1)
      charlie = false;
    return;
  }

  if(bob) {
    rand_num = rand() % 100;
    //Shift because indexing if from 0 - 99
    if(rand_num <= AARON_HIT_RATIO - 1)
      bob = false;
    return;
  }
  cerr << "Both inputs were false in aaron_shoots1."
       << " This is a violation of the program invarient.\n";
}
  
//Aaron shoots at the person with the
//highest possible hit chance first.
//If everyone is alive (it is the first round of
//shooting), he misses, else
//he has a 33% hit ratio.
//Inputs are modified to reflect result of shot.
void aaron_shoots2(bool& bob, bool& charlie) {
  int rand_num{};

  //If bob and charlie are alive then the first turn
  //has not passed since charlie is guarenteed to
  //kill someone. Thus do nothing.
  if(bob && charlie)
    return;
  
  if(charlie) {
    rand_num = rand() % 100;
    //cout << "rand: " << rand_num << endl;
    //Shift becuase indexing is from 0 - 99
    if(rand_num <= AARON_HIT_RATIO - 1)
      charlie = false;
    return;
  }

  if(bob) {
    rand_num = rand() % 100;
    //Shift because indexing if from 0 - 99
    if(rand_num <= AARON_HIT_RATIO - 1)
      bob = false;
    return;
  }
  cerr << "Both inputs were false in aaron_shoots1."
       << " This is a violation of the program invarient.\n";
}
//Bob shoots at the person with the
//highest possible hit chance first.
//He has a 50% hit ratio.
//Inputs are modified to reflect result of shot.
void bob_shoots(bool& aaron, bool& charlie) {
  int rand_num{};
  if(charlie) {
    rand_num = rand() % 100;
    //cout << "rand: " << rand_num << endl;
    //Shift becuase indexing is from 0 - 99
    if(rand_num <= BOB_HIT_RATIO - 1)
      charlie = false;
    return;
  }

  if(aaron) {
    rand_num = rand() % 100;
    //Shift because indexing if from 0 - 99
    if(rand_num <= BOB_HIT_RATIO - 1)
      aaron = false;
    return;
  }
  cerr << "Both inputs were false in aaron_shoots1."
       << " This is a violation of the program invarient.\n";
}
//Charlie shoots at the person with the
//highest possible hit chance first.
//He has a 100% hit ratio.
//Inputs are modified to reflect result of shot.
void charlie_shoots(bool& aaron, bool& bob) {
  int rand_num{};
  if(bob) {
    rand_num = rand() % 100;
    //cout << "rand: " << rand_num << endl;
    //Shift becuase indexing is from 0 - 99
    if(rand_num <= CHARLIE_HIT_RATIO - 1)
      bob = false;
    return;
  }

  if(aaron) {
    rand_num = rand() % 100;
    //Shift because indexing if from 0 - 99
    if(rand_num <= CHARLIE_HIT_RATIO - 1)
     aaron = false;
    return;
  }
  cerr << "Both inputs were false in aaron_shoots1."
       << " This is a violation of the program invarient.\n";
}
