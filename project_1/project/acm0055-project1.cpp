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
 * Version: 4/10/16
 * Compile: make
 * Sample usage: ./game
 * Sources: no sources
 */
#include "include/game_engine/menu.h"
#include "include/game_engine/user.h"
#include "include/game_engine/game_play.h"
#include "include/game_engine/puzzle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
  menu main_menu = init_main_menu();
  char main_action{'a'};
  srand(time(0));
  while (main_action != 'c') {
    display_menu(main_menu);
    main_action = main_select();
    switch (main_action) {
    case 'a':
      game();
      break;
    case 'b':
      display_high_scores("highscores.txt");
      break;
    }
  }
}
