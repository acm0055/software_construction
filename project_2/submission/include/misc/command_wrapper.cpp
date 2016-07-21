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

#include <cstdlib>
#include <string>
#include "command_wrapper.h"
using namespace std;

Command_Wrapper::Command_Wrapper(string command_in,string arguments_in,
				 string file_name_in,bool out_to_screen_in)
{
  command = command_in;
  arguments = arguments_in;
  file_name = file_name_in;
  out_to_screen = out_to_screen_in;
}

void Command_Wrapper::call()
{
  string full_command;
  full_command = command;
  full_command.push_back(' ');
  full_command += arguments;
  full_command += " | ";
  full_command += out_to_screen ? " tee > " : " cat > ";
  full_command += file_name;
  system(full_command.c_str());
}

string Command_Wrapper::set_file_name(string name_in)
{
  string temp = file_name;
  file_name = name_in;
  return temp;
}

string Command_Wrapper::set_command(string command_in)
{
  string temp = command;
  command = command_in;
  return temp;
}

bool Command_Wrapper::set_out_to_screen(bool toggle)
{
  bool temp = out_to_screen;
  out_to_screen = toggle;
  return temp;
}

string Command_Wrapper::set_command_arguments(string args_in)
{
  string temp = arguments;
  arguments = args_in;
  return temp;
}

const string& Command_Wrapper::get_file_name()
{
  return file_name;
}

const string& Command_Wrapper::get_command()
{
  return command;
}

bool Command_Wrapper::get_out_to_screen()
{
  return out_to_screen;
}

const string& Command_Wrapper::get_command_arguments()
{
  return arguments;
}
