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
 * filename: disk_report.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: cplusplus.com for ios_base modes (mentioned below)
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "../misc/audisktool.h"
#include "disk_report.h"
using namespace std;
using namespace audisktool;

Disk_Report::Disk_Report(disk_config config_in, string res_file_name)
  : config{config_in},
    parser{"major_dev_num\n"
	"minor_dev_num\n"
	"dev_name\n"
	"num_read_comp\n"
	"num_reads_merged\n"
	"num_sector_read\n"
	"num_milli_read\n"
	"num_writes_comp\n"
	"num_writes_merged\n"
	"num_sector_written\n"
	"num_milli_write\n"
	"num_io_cur\n"
	"num_milli_io\n"
	"weighted_num_milli_io\n", res_file_name+".temp"}
{
}

void Disk_Report::add_entry(string file_name)
{
  ifstream file{file_name};
  
  parser.parse_file(file);

  results.push_back(this->parse_result(parser.get_list()));
}

void Disk_Report::change_config(disk_config config_in)
{
  config = config_in;
}

void Disk_Report::print_report()
{
  cout << this->to_str();
}

void Disk_Report::write_report(string file_name)
{
  //http://www.cplusplus.com/reference/fstream/fstream/fstream/
  //for ios_base modes
  ofstream file{file_name, ios_base::trunc};

  file << this->to_str();
}

string Disk_Report::to_str()
{
  string output;
  
  for (int i = 1; i < results.size(); i++) {
    output += string{"Device Name: "} + string{results[i].dev_name} + '\n';
    if (config.print_blk_read)
      output += string{"Blocks Read: "} + to_string(results[i].num_sector_read -
						    results[i-1].num_sector_read)
					  + '\n';
    if (config.print_blk_read_s)
      output += string{"Blocks Read/s: "} + to_string((results[i].num_sector_read -
						       results[i-1].num_sector_read) /
						       config.interval)
					    + '\n';
    if (config.print_kb_read_s)
      output += string{"KB Read/s: "} + to_string((results[i].num_sector_read -
						   results[i-1].num_sector_read) /
						  (2 * config.interval))
					+ '\n';
    if (config.print_blk_write)
      output += string{"Blocks Written: "} + to_string(results[i].num_sector_written -
						       results[i-1].num_sector_written)
					     + '\n';
    if (config.print_blk_write_s)
      output += string{"Blocks Written/s: "} + to_string((results[i].num_sector_written -
							  results[i-1].num_sector_written) /
							  config.interval)
					       + '\n';
    if (config.print_kb_write_s)
      output += string{"KB Written/s: "} + to_string((results[i].num_sector_written -
						      results[i-1].num_sector_written) /
						     (2 * config.interval))
					   + '\n';

    //add spacing between entries
    output += '\n';
  }

  return output;
}

disk_result Disk_Report::parse_result(list<result> list_res)
{
  result temp;
  disk_result disk_res;

  while (!list_res.empty()) {
    temp = list_res.front();
    list_res.pop_front();

    if (temp.key == "major_dev_num")
      disk_res.major_dev_num = stoi(temp.value);
    else if (temp.key == "minor_dev_num")
      disk_res.minor_dev_num = stoi(temp.value);
    else if (temp.key == "dev_name")
      disk_res.dev_name = temp.value;
    else if (temp.key == "num_read_comp")
      disk_res.num_read_comp = stoi(temp.value);
    else if (temp.key == "num_reads_merged")
      disk_res.num_reads_merged = stoi(temp.value);
    else if (temp.key == "num_sector_read")
      disk_res.num_sector_read = stoi(temp.value);
    else if (temp.key == "num_milli_read")
      disk_res.num_milli_read = stoi(temp.value);
    else if (temp.key == "num_writes_comp")
      disk_res.num_writes_comp = stoi(temp.value);
    else if (temp.key == "num_writes_merged")
      disk_res.num_writes_merged = stoi(temp.value);
    else if (temp.key == "num_sector_written")
      disk_res.num_sector_written = stoi(temp.value);
    else if (temp.key == "num_milli_write")
      disk_res.num_milli_write = stoi(temp.value);
    else if (temp.key == "num_io_cur")
      disk_res.num_io_cur = stoi(temp.value);
    else if (temp.key == "num_milli_io")
      disk_res.num_milli_io = stoi(temp.value);
    else
      //weighted_num_milli_io
      disk_res.weighted_num_milli_io = stoi(temp.value);
  }

  return disk_res;
}
