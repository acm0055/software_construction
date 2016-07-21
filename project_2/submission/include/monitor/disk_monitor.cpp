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
 * filename: disk_tool.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/29/16
 * Compile: make
 * Sample usage: ./audisktool
 * Sources: derived class syntax help from stackoverflow
 *          chrono library help from Bjarne Stroustrup's
 *          The C++ Programming Language 4th Edition
 */

#include <fstream>
#include <string>
#include <list>
#include <chrono>
#include "../misc/disk_config.h"
#include "../misc/disk_report.h"
#include "../misc/audisktool.h"
#include "../parser/sw_parser.h"
#include "../misc/command_wrapper.h"
#include "disk_monitor.h"
#include "monitor.h"
using namespace std;
using namespace audisktool;

//for help with syntax
//http://stackoverflow.com/questions/10282787/calling-the-base-class-constructor-in-the-derived-class-constructor
Disk_Monitor::Disk_Monitor(string disk_name, string res_file_name,
			   string config_name)
  : config{config_name},
    report{config.get_config(), res_file_name},
    Monitor<result>{res_file_name, config_name,
	"set interval - set sampling period\n"
	"set count - set the number of records\n"
	"set report - set report file name\n"
	"set blk_read - set print_blk_read\n"
	"set blk_read/s - set print_blk_read/s\n"
	"set kb_read/s - set print_kb_read/s\n"
	"set blk_write - set print_blk_write\n"
	"set blk_write/s - set print_blk_write/s\n"
	"set kb_write - set print_kb_write\n"
	"print conf - display all the parameters\n"
	"print report - open and display the report file\n"
	"save - the configuration file audistool.conf is updated\n"
	"exit - exit the tool\n",
	Command_Wrapper{"grep",disk_name+" /proc/diskstats",res_file_name+".temp",0}}
{
  report.change_config(config.get_config());
  config_update = false;
}

Disk_Monitor::~Disk_Monitor() {
  if (config_update)
    config.write_config(config_name);

  report.write_report(res_file_name+".adt");
}

disk_config Disk_Monitor::get_config()
{
  return config.get_config();
}

disk_config Disk_Monitor::set_config(disk_config new_config)
{
  config_update = true;
  
  config.set_config(new_config);
  report.change_config(config.get_config());
}

void Disk_Monitor::run_monitor()
{
  //information on how to use the chrono
  //library from Bjarne Stroustrup The
  //C++ Programming Language 4th Edition
  chrono::system_clock::time_point start;
  for (int i = 0; i < config.get_config().count; i++) {
    start = chrono::system_clock::now();
    data_grabber.call();
    report.add_entry(data_grabber.get_file_name());
    delay(config.get_config().interval -
	  chrono::duration_cast<chrono::milliseconds>
	  (chrono::system_clock::now() - start).count()/1000.0);
  }
}

void Disk_Monitor::print_config()
{
  config.print_config();
}

void Disk_Monitor::write_config() {
  config.write_config(config_name);

  config_update = false;
}

void Disk_Monitor::print_report()
{
  report.print_report();
}

void Disk_Monitor::write_report()
{
  report.write_report(res_file_name+".adt");
}
