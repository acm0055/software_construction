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
 * filename: disk_monitor.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: no sources
 */

#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H 1

#include <string>
#include "monitor.h"
#include "../misc/audisktool.h"
#include "../misc/disk_report.h"
#include "../misc/disk_config.h"
using namespace std;
using namespace audisktool;

class Disk_Monitor : public Monitor<result>
{
 private:
  Disk_Config config;
  bool config_update;
  Disk_Report report;

  void parse_config();
  void write_result();
 public:
  Disk_Monitor(string disk_name, string res_file_name,
	       string config_name);
  ~Disk_Monitor();
  disk_config get_config();
  disk_config set_config(disk_config new_config);
  void run_monitor();
  void print_config();
  void write_config();
  void print_report();
  void write_report();
};

#endif /*DISK_MONITOR_H*/
