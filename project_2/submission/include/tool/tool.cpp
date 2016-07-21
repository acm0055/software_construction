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
 * filename: tool.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/27/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: no sources
 */

#include "tool.h"
#include "../misc/audisktool.h"
#include "../monitor/disk_monitor.h"
using namespace std;
using namespace audisktool;

void Tool::start(string disk_name, string results_name, string config_name)
{
  Disk_Monitor dm{disk_name, results_name, config_name};
  disk_config config;
  string user_input;
  string temp_arg;
  unsigned int arg_pos;
  while (user_input != "exit") {
    cout << "> ";
    getline(cin, user_input);

    arg_pos = user_input.find_last_of(' ');
    if (arg_pos <= user_input.size()) {
      temp_arg = user_input.substr(arg_pos+1);
      user_input = user_input.substr(0, arg_pos);
    }
    else {
      temp_arg = "0";
    }
    
    //may change implementation
    //based on the speed of checks
    if (user_input == "run") {
      dm.run_monitor();
    }
    else if (user_input == "set interval") {
      config = dm.get_config();

      set_value(config.interval, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set count") {
      config = dm.get_config();

      set_value(config.count, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set report") {
      cout << "> New Report Name: ";
      string temp;

      getline(cin, temp);
      dm.set_output_file_name(temp);
    }
    else if (user_input == "set blk_read") {
      config = dm.get_config();
      set_flag(config.print_blk_read, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set blk_read/s") {
      config = dm.get_config();
      set_flag(config.print_blk_read_s, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set kb_read/s") {
      config = dm.get_config();
      set_flag(config.print_kb_read_s, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set blk_write") {
      config = dm.get_config();
      set_flag(config.print_blk_write, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set blk_write/s") {
      config = dm.get_config();
      set_flag(config.print_blk_write_s, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "set kb_write") {
      config = dm.get_config();
      set_flag(config.print_kb_write_s, temp_arg);
      dm.set_config(config);
    }
    else if (user_input == "print") {
      if (temp_arg == "conf")
	dm.print_config();
      else if (temp_arg == "report")
	dm.print_report();
    }
    else if (user_input == "save")
      dm.write_config();
    else if (user_input == "help")
      cout << dm.get_help();
    else; //do nothing for now
  }
}

void Tool::set_flag(bool& flag, string user_input) {
  double temp;
  bool temp_bool;

  temp = stod(user_input);
  
  temp_bool = static_cast<int>(temp);
  if (temp == 0 || temp == 1) {
    flag = temp;
  }
  else {
    cout << "Enter 0 or 1." << endl;
  }
}

template <class T>
void Tool::set_value(T& value, string user_input) {
  double temp_in;
  T temp_cast;

  temp_in = stod(user_input);

  temp_cast = static_cast<T>(temp_in);
  if (temp_cast > 0) {
    value = temp_in;
  }
  else {
    cout << "Enter a value > 0." << endl;
  }
}
