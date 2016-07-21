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
#include "../misc/disk_command_line.h"
using namespace std;
using namespace audisktool;

void Tool::start(string disk_name, string results_name, string config_name)
{
  Disk_Monitor dm{disk_name, results_name, config_name};
  disk_config config;
  string user_input;
  while (user_input != "exit") {
    cout << "> ";
    getline(cin, user_input);

    //may change implementation
    //based on the speed of checks
    if (user_input == "run") {
      dm.run_monitor();
    }
    else if (user_input == "set interval") {
      config = dm.get_config();

      set_value(config.interval);
      dm.set_config(config);
    }
    else if (user_input == "set count") {
      config = dm.get_config();

      set_value(config.count);
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
      set_flag(config.print_blk_read);
      dm.set_config(config);
    }
    else if (user_input == "set blk_read/s") {
      config = dm.get_config();
      set_flag(config.print_blk_read_s);
      dm.set_config(config);
    }
    else if (user_input == "set kb_read/s") {
      config = dm.get_config();
      set_flag(config.print_kb_read_s);
      dm.set_config(config);
    }
    else if (user_input == "set blk_write") {
      config = dm.get_config();
      set_flag(config.print_blk_write);
      dm.set_config(config);
    }
    else if (user_input == "set blk_write/s") {
      config = dm.get_config();
      set_flag(config.print_blk_write_s);
      dm.set_config(config);
    }
    else if (user_input == "set kb_write") {
      config = dm.get_config();
      set_flag(config.print_kb_write_s);
      dm.set_config(config);
    }
    else if (user_input == "print conf")
      dm.print_config();
    else if (user_input == "print report")
      dm.print_report();
    else if (user_input == "save")
      dm.write_config();
    else if (user_input == "help")
      cout << dm.get_help();
    else; //do nothing for now
  }
}

void run_command(disk_command_line::disk_command& cmd)
{
  //parse command
  if (cmd.command == "run");
  else if (cmd.command == "set") {
    if (cmd.arguments.size() >= 2) {
      cout << "Malformed command" << endl;
      return;
    }
    
    if (cmd.arguments[0] == "interval") {
      config = dm.get_config();

      set_value(cmd.arguments[1], config.interval);
      dm.set_config(config);
    }
    else if (user_input == "count") {
      config = dm.get_config();

      set_value(cmd.arguments[1], config.count);
      dm.set_config(config);
    }
    else if (user_input == "report") {
      dm.set_output_file_name(cmd.arguments[1]);
    }
    else if (user_input == "blk_read") {
      config = dm.get_config();
      
      set_value(cmd.arguments[1], config.print_blk_read);
      dm.set_config(config);
    }
    else if (user_input == "blk_read/s") {
      config = dm.get_config();
      
      set_value(cmd.arguments[1], config.print_blk_read_s);
      dm.set_config(config);
    }
    else if (user_input == "kb_read/s") {
      config = dm.get_config();
      
      set_value(cmd.arguments[1], config.print_kb_read_s);
      dm.set_config(config);
    }
    else if (user_input == "blk_write") {
      config = dm.get_config();
      
      set_value(cmd.arguments[1], config.print_blk_write);
      dm.set_config(config);
    }
    else if (user_input == "blk_write/s") {
      config = dm.get_config();
      set_value(cmd.arguments[1], config.print_blk_write_s);
      dm.set_config(config);
    }
    else if (user_input == "kb_write") {
      config = dm.get_config();
      set_value(cmd.arguments[1], config.print_kb_write_s);
      dm.set_config(config);
    }
  }
  else if (cmd.command == "print");
  else if (cmd.command == "save");
  else if (cmd.command == "help");

  //additional command exists
  if (cmd.next)
    run_command(*cmd.command.next)
}

template <class T>
void set_value(string val, T& val)
{
  //parse to most generic value
  //all valid numbers parse to double
  double temp;
  temp = stod(val);
  while (val < 0) {
    cout << "Please enter a non-negative value" << endl;
    cout << "> ";
    getline(cin, val);
    temp = stod(val);
  }
  val = static_cast<T>(temp);
}
