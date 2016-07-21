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
 * filename: sw_parser.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: no sources
 */

#ifndef SW_PARSER_H
#define SW_PARSER_H 1

#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "../misc/audisktool.h"
#include "../misc/command_wrapper.h"
using namespace std;
using namespace audisktool;

template <class T>
class SW_Parser {
 private:
  list<T> items;
  vector<string> parsed_rule;
  string rule;
  string file_name;
 public:
  SW_Parser(string rule_in, string file_name_in)
    {
      set_rule(rule_in);
      file_name = file_name_in;
    }
  list<T> get_list()
    {
      return items;
    }
  string set_file_name(string file_name_in)
  {
    string temp;
    temp = file_name;

    file_name = file_name_in;
    return temp;
  }
  const string& get_file_name()
  {
    return file_name;
  }
  void parse_file(ifstream& file_in)
  {
    T kv;
    items.clear();

    int i = 0;
    while (i < parsed_rule.size()) {
      kv.key = parsed_rule[i];
      file_in >> kv.value;
      items.push_back(kv);
      i++;
    }
  }
  void parse_file()
  {
    ifstream file{file_name};
    T kv;
    items.clear();

    int i = 0;
    while (i < parsed_rule.size()) {
      kv.key = parsed_rule[i];
      file >> kv.value;
      items.push_back(kv);
      i++;
    }
  }
  void set_rule(string rule_in)
  {
    rule = rule_in;
    string rule_temp = rule;
    istringstream temp{rule_temp};
    string key;
    while (temp) {
      getline(temp, key);
      if (key.size() != 0)
	parsed_rule.push_back(key);
    }
  }
  const string& get_rule()
  {
    return rule;
  }
};

#endif /*SW_PARSER*/
