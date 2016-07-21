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
 * filename: encounter.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/10/16
 * Compile: make
 * Sample usage: n/a
 * Sources: no sources
 *
 * Methods and structures for dealing with encounters.
 */
#ifndef ENCOUNTER_H
#define ENCOUNTER_H 1
#include "user.h"

//various chances for generate encounter function
const int GRUNT_WORK_CHANCE{14};
const int DO_NOTHING_CHANCE{39};
const int PUZZLE_CHANCE{69};
const int PROFESSOR_CHANCE{79};
const int GRAD_STUDENT_CHANCE{89};

//Pointer to generic encounter function
//syntax fix from http://stackoverflow.com/
//  questions/4295432/typedef-function-pointer
typedef void(*encounter_func)(user& user_in, void* special);

/////////////////////
//Encounter methods//
/////////////////////

//Returns an encounter based on the random
//probilities specified in the program design doc.
encounter_func generate_encounter();
//Modifies user according to the specifications of grunt work
void grunt_work(user& user_in, void*);
//Modifies user according to the specifications of do nothing
void do_nothing(user& user_in, void*);
//Modifies user according to the specifications of puzzle.
//Asks user a puzzle question and removes that question from
//the puzzle list.
void puzzle(user& user_in, void* puzzle_list);
//Modifies user according to the specifications of professor
void professor(user& user_in, void*);
//Modifies user according to the specifications of grad student
void grad_student(user& user_in, void*);
//Modifies user according to the specifications of grade papers
void grade_papers(user& user_in, void*);
#endif /*ENCOUNTER_H*/
