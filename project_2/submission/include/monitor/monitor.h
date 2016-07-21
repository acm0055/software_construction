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
 * filename: monitor.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: no sources
 */

#ifndef MONITOR_H
#define MONITOR_H 1

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../parser/sw_parser.h"
#include "../misc/audisktool.h"
#include "../misc/command_wrapper.h"
using namespace std;
using namespace audisktool;

template <class T>
class Monitor {
 protected:
  string help_diag;
  string res_file_name;
  //  SW_Parser<T> parser;
  Command_Wrapper data_grabber;
  string config_name;
 public:
  Monitor(string res_file_name_in, string config_name_in, string help_diag_in,
	  Command_Wrapper data_grabber_in/*, SW_Parser<T> parser_in*/)
    : /*parser{parser_in},*/data_grabber{data_grabber_in}
  {
    res_file_name = res_file_name_in;
    config_name = config_name_in;
    help_diag = help_diag_in;
  }
  virtual ~Monitor()
  {
  }
  virtual void print_config()=0;
  virtual void write_config()=0;
  virtual void print_report()=0;
  virtual void write_report()=0;
  const string& get_help() {
    return help_diag;
  }
  string set_config_file_name(string file_in)
  {
    string temp;
    temp = config_name;

    config_name = file_in;

    return temp;
  }
  string set_output_file_name(string file_in)
  {
    string temp;
    temp = res_file_name;

    res_file_name = file_in;

    return res_file_name;
  }
  const string& get_config_file_name()
  {
    return config_name;
  }
  const string& get_output_file_name()
  {
    return res_file_name;
  }
  virtual void run_monitor()=0;
};

#endif /*MONITOR_H*/
