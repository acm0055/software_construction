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
 * filename: disk_config.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: cplusplus.com for ios_base mode reference (mentioned below)
 */

#include <string>
#include <iostream>
#include <fstream>
#include "audisktool.h"
#include "../parser/sw_parser.h"
#include "disk_config.h"
using namespace std;
using namespace audisktool;

Disk_Config::Disk_Config(string file_name)
{
  parse_config(file_name);
}

void Disk_Config::parse_config(string file_name)
{
  string config_parse_rule{"Interval\nCount\n"
      "print_blk_read\nprint_blk_read/s\n"
      "print_kb_read/s\nprint_blk_write\n"
      "print_blk_write/s\nprint_kb_write/s\n"};
  
  SW_Parser<config_item> sw{config_parse_rule,
      file_name};

  sw.parse_file();
  list<config_item> temp_list = sw.get_list();
  config_item temp_elem;

  //Put in disk config file
  //verbose for readability
  //may remove verbose and
  //assume more about the formating
  //if speed becomes an issue.
  while (!temp_list.empty()) {
    temp_elem = temp_list.front();
    temp_list.pop_front();
    if (temp_elem.key == "Interval")
      config.interval = stod(temp_elem.value);
    else if (temp_elem.key == "Count")
      config.count = stoi(temp_elem.value);
    else if (temp_elem.key == "print_blk_read")
      config.print_blk_read = stoi(temp_elem.value);
    else if (temp_elem.key == "print_blk_read/s")
      config.print_blk_read_s = stoi(temp_elem.value);
    else if (temp_elem.key == "print_kb_read/s")
      config.print_kb_read_s = stoi(temp_elem.value);
    else if (temp_elem.key == "print_blk_write")
      config.print_blk_write = stoi(temp_elem.value);
    else if (temp_elem.key == "print_blk_write/s")
      config.print_blk_write_s = stoi(temp_elem.value);
    else
      //print_kb_write/s
      config.print_kb_write_s = stoi(temp_elem.value);
  }
}

disk_config Disk_Config::get_config()
{
  return config;
}

disk_config Disk_Config::set_config(disk_config new_config)
{
  config = new_config;
}

void Disk_Config::print_config()
{
  cout << "Interval: " << config.interval
       << "s" << endl
       << "Count: " << config.count
       << endl
       << "blk_read: " << config.print_blk_read
       << endl
       << "blk_read/s: " << config.print_blk_read_s
       << endl
       << "kb_read/s: " << config.print_kb_read_s
       << endl
       << "blk_write: " << config.print_blk_write
       << endl
       << "blk_write/s: " << config.print_blk_write_s
       << endl
       << "kb_write/s: " << config.print_kb_write_s
       << endl;
}

void Disk_Config::write_config(string file_name)
{
  //http://www.cplusplus.com/reference/fstream/fstream/fstream/
  //for ios_base modes
  ofstream file{file_name, ios_base::trunc};

  file << config.interval << ' '
       << config.count << ' '
       << config.print_blk_read << ' '
       << config.print_blk_read_s << ' '
       << config.print_kb_read_s << ' '
       << config.print_blk_write << ' '
       << config.print_blk_write_s << ' '
       << config.print_kb_write_s;
}
