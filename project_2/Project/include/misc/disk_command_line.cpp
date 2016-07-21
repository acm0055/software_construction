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
 * filename: command_wrapper.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: no sources
 */

#include <iostream>
#include <string>
#include <vector>
#include "disk_command_line.h"

{
  using namespace std;
  using namespace disk_command_line;

  void parse_command(string user_input, disk_command& cmd)
  {
    string user_input;
    string::size_t loc;

    loc = user_input.find_first_of(' ');
    //one command command so return without
    //parsing rest
    if (loc = string::npos){
      cmd.command = user_input;
      return;
    }
    
    cmd.command = user_input.substr(0, loc);
    user_input = user_input.substr(loc+1);

    loc = user_input.find_first_of(' ');
    //parse arguments
    string temp;
    while (loc != string::npos) {
      temp = user_input.substr(0, loc);
      if (temp.size() > 0) {
	if (temp == "|") {
	  user_input = user_input.substr(0, loc);
	  cmd.next = new disk_command_line;
	  parse_command(user_input, *cmd.next);
	}
	else {
	  cmd.arguments.push_back(user_input.substr(0, loc));
	  user_input = user_input.substr(0, loc);
	}
      }
      
      loc = user_input.find_first_of(' ');
    }

    //consider end case
    if (user_input.size() > 0)
      cmd.arguments.push_back(user_input);
  }
}
