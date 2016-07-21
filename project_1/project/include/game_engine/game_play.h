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
 * filename: game_play.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/10/16
 * Compile: make
 * Sample usage: n/a
 * Sources: no sources
 *
 * Methods for dealing with an instance of the game.
 */
#ifndef GAME_PLAY_H
#define GAME_PLAY_H 1

#include "user.h"
#include "puzzle.h"

//constants for various functions and readability
const int TECH_PAPER_INT_BOOST{2};
const int LOOSE_CHANGE_MNY_BOOST{2};

//Move the character and generate a random encounter.
void move_character(user& user_in, quiz_list& list);
//Reading tech papers boosts intelligence and loses time.
void read_technical_paper(user& user_in);
//Searches for loose change boosts money and loses time.
void search_for_loose_change(user& user_in);
//Displays character and his/her stats
void view_character(user& user_in);
//Select character difficulty
user select_difficulty(string user_name);
//Process character move.
void process_move(user& user_in, quiz_list& quiz, char move);
//Start the game
void game();
//handles end game scenario
void game_over(const user& user_in);
#endif /*GAME_PLAY_H*/
