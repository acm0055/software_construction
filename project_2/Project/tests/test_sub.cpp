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
 * filename: test_sub.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/21/16
 * Compile: make test
 * Sample usage: ./test
 * Sources: no sources
 * 
 * Collection of tests for the audisktool's various components.
 */
#include <fstream>
#include <string>
#include <list>
#include "../include/misc/audisktool.h"
#include "../include/parser/sw_parser.h"
#include "../include/monitor/disk_monitor.h"
#include "../include/misc/command_wrapper.h"

void test_sw_parser();
void test_parse_file();
void test_set_get_file_name();
void test_set_get_rule();

void test_disk_monitor();
void test_get_set_config();
void test_run_monitor();
void test_get_set_config_file_name();
void test_get_set_output_file_name();
void test_print_config();
void test_write_config();

void test_command_wrapper();
void test_call();
void test_set_get_file_name();
void test_set_get_command();
void test_set_get_out_to_screen();
void test_set_get_command_arguments();

int main()
{
  test_disk_monitor();
  test_command_wrapper();
  test_sw_parser();
}

void print_case(int case_num, string case_name)
{
  cout << "\tCase " << case_num << ": " << case_name << endl;
}

void print_pass()
{
  cout << "\tPassed..." << endl;
}

void user_verify(string verification_message)
{
  cout << "\t\t" << verification_message << endl;
  cout << "\t\tIs case true?(y/n): ";
  
  char u_in = 'k';
  while (u_in != 'y' || u_in != 'Y') {
    cin >> u_in;
    if (u_in == 'n' || u_in == 'N')
      //stop program for failure
      assert(false);
    else if (u_in != 'y' || u_in != 'Y')
      cout << "Please enter a valid response: ";
  }
}

void test_sw_parser()
{
  void test_parse_file();
  void test_set_get_file_name();
  void test_set_get_rule();
}

void test_parse_file()
{
  SW_Parser<result> sw{"test\n"
      "\n"
      "test\n", "test_parser"};
  string prev;

  string keys[] = {"test", "", "test"};
  
  print_case(1, "Test parser on properly formated file. Parse one unit.");
  list<result> parsed_file = sw.get_list();
  int i = 0;
  for (auto r: parsed_file) {
    assert(stoi(r.value) == i);
    assert(r.key == keys[i]);
    i++;
  }
  print_pass();

  print_case(1, "Test parser on properly formated file. Parse multiple units.");
  i = 0;
  for (int j = 0; j < 3; j++) {
    parsed_file = sw.get_list();
    for (auto r: parsed_file) {
      assert(stoi(r.value) == i);
      assert(r.key == keys[i % 3]);
      i++;
    }
  }
  print_pass();
}
void test_set_get_file_name()
{
  SW_Parser<result> sw{"test\n"
      "\n"
      "test\n", "test_parser"};
  string prev;
  
  print_case(1, "Get file name after construction.");
  assert(sw.get_file_name() == "test_temp");
  print_pass();

  print_case(2, "Set file name normal. Implicit get file name check.");
  prev = sw.set_file_name("normal.txt");
  assert(sw.get_file_name() == "normal.txt");
  assert(prev == "test_temp");
  print_pass();

  print_case(3, "Set file name empty. Implicit get file name check.");
  sw.set_file_name("");
  assert(sw.get_file_name() == "");
  assert(prev == "normal.txt");
  print_pass();
}
void test_set_get_rule()
{
  SW_Parser<result> sw{"test\n"
      "\n"
      "test\n", "test_temp"};
    
  print_case(1, "Get file name after construction.");
  assert(sw.get_rule() == "test_parser");
  print_pass();

  print_case(2, "Set file name normal. Implicit get file name check.");
  sw.set_rule("normal.txt");
  assert(sw.get_rule() == "normal.txt");
  print_pass();

  print_case(3, "Set file name empty. Implicit get file name check.");
  sw.set_rule("");
  assert(sw.get_rule() == "");
    print_pass();
}

void test_disk_monitor()
{
  void test_get_set_config();
  void test_run_monitor();
  void test_get_set_config_file_name();
  void test_get_set_output_file_name();
  void test_print_config();
  void test_write_config();
}

void test_get_set_config()
{
  Disk_Monitor dm{"sda", "results", "test_config"};
  print_case(1, "Get config after construction.");
  disk_config temp = dm.get_config();
  assert(temp.count == 5);
  assert(temp.interval == 5);
  assert(temp.print_blk_read == 1);
  assert(temp.print_blk_read_s == 0);
  assert(temp.print_kb_read_s == 1);
  assert(temp.print_blk_write == 0);
  assert(temp.print_blk_write_s == 1);
  assert(temp.print_kb_write_s == 0);
  print_pass();

  print_case(2, "Set and reset config params. Implicit get name check.");
  int prev = temp.count;

  print_case(2.1, "\tCount.");
  temp.count = 2;
  dm.set_config(temp);
  assert(dm.get_config().count == 2);
  temp.count = prev;
  dm.set_config(temp);

  print_case(2.2, "\tInterval.");
  prev = temp.interval;
  temp.interval = 2;
  dm.set_config(temp);
  assert(dm.get_config().interval == 2);
  temp.interval = prev;
  dm.set_config(temp);

  print_case(2.3, "\tPrint Blk Read.");
  prev = temp.print_blk_read;
  temp.print_blk_read = 0;
  dm.set_config(temp);
  assert(dm.get_config().print_blk_read == 0);
  temp.print_blk_read = prev;
  dm.set_config(temp);

  print_case(2.4, "\tPrint Blk Read/s.");
  prev = temp.print_blk_read_s;
  temp.print_blk_read_s = 1;
  dm.set_config(temp);
  assert(dm.get_config().print_blk_read_s == 1);
  temp.print_blk_read_s = prev;
  dm.set_config(temp);

  print_case(2.5, "\tPrint KB Read/s.");
  prev = temp.print_kb_read_s;
  temp.print_kb_read_s = 0;
  dm.set_config(temp);
  assert(dm.get_config().print_kb_read_s == 0);
  temp.print_kb_read_s = prev;
  dm.set_config(temp);

  print_case(2.6, "\tPrint Blk Write.");
  prev = temp.print_blk_write;
  temp.print_blk_write = 1;
  dm.set_config(temp);
  assert(dm.get_config().print_blk_write == 1);
  temp.print_blk_write = prev;
  dm.set_config(temp);

  print_case(2.7, "\tPrint Blk Write/s.");
  prev = temp.print_blk_write_s;
  temp.print_blk_write_s = 0;
  dm.set_config(temp);
  assert(dm.get_config().print_blk_write_s == 0);
  temp.print_blk_write_s = prev;
  dm.set_config(temp);

  print_case(2.8, "\tPrint KB Write/s.");
  prev = temp.print_kb_write_s;
  temp.print_kb_write_s = 0;
  dm.set_config(temp);
  assert(dm.get_config().print_kb_write_s == 0);
  temp.print_kb_write_s = prev;
  dm.set_config(temp);
  
  print_pass();
}
void test_get_set_config_file_name()
{
  Disk_Monitor dm{"sda", "results", "test_config"};
  string prev;
  
  print_case(1, "Get config file name after construction.");
  assert(dm.get_config_file_name() == "test_config");
  print_pass();

  print_case(2, "Set config file name normal. Implicit get config file name check.");
  prev = dm.set_config_file_name("normal.txt");
  assert(dm.get_config_file_name() == "normal.txt");
  assert(prev == "test_config");
  print_pass();

  print_case(3, "Set config file name empty. Implicit get config file name check.");
  dm.set_config_file_name("");
  assert(dm.get_config_file_name() == "");
  assert(prev == "normal.txt");
  print_pass();
}
void test_get_set_output_file_name()
{
  Disk_Monitor dm{"sda", "results", "test_config"};
  string prev;
  
  print_case(1, "Get output file name after construction.");
  assert(dm.get_output_file_name() == "results");
  print_pass();

  print_case(2, "Set output file name normal. Implicit get output file name check.");
  prev = dm.set_output_file_name("normal.txt");
  assert(dm.get_output_file_name() == "normal.txt");
  assert(prev == "test_config");
  print_pass();

  print_case(3, "Set output file name empty. Implicit get output file name check.");
  dm.set_output_file_name("");
  assert(dm.get_output_file_name() == "");
  assert(prev == "normal.txt");
  print_pass();
}
void test_print_config()
{
  Disk_Monitor dm{"sda", "results", "test_config"};
  print_case(1,"Print test config.");
  user_verify("User should verify that the following config information\n"
	      "\t\tis printed. Count: 5, Interval: 5, print_blk_read: 1\n"
	      "\t\tprint_blk_read/s: 0, print_kb_read/s: 1, print_blk_write: 0\n"
	      "\t\tprint_blk_write/s: 1, print_kb_write/s: 0.");
  print_pass();
}
void test_write_config()
{
  Disk_Monitor dm{"sda", "results", "test_config"};
  disk_config restore = dm.get_config();
  disk_config modifications = restore;

  modifications.count = 2;
  modifications.interval = 2;
  modifications.print_blk_read = 0;
  modifications.print_blk_read_s = 1;
  modifications.print_kb_read_s = 0;
  modifications.print_blk_write = 1;
  modifications.print_blk_write_s = 0;
  modifications.print_kb_write_s = 1;
  dm.set_config(modifications);
  dm.write_config();
  
  print_case(1, "Test write config.");
  user_verify("User should verify that the following config information\n"
	      "\t\tis printed and written to test_config. Count: 2, Interval: 2, print_blk_read: 0\n"
	      "\t\tprint_blk_read/s: 1, print_kb_read/s: 0, print_blk_write: 1\n"
	      "\t\tprint_blk_write/s: 0, print_kb_write/s: 1.");
  print_pass();

  //restore
  dm.set_config(restore);
  dm.write_config();

  //write on deconstruction
  Disk_Monitor* dm2 = new Disk_Monitor{"sda", "results", "test_config"};
  print_case(2, "Test write on deconstruction.");
  dm2->set_config(modifications);
  delete dm2;
  user_verify("User should verify that the following config information\n"
	      "\t\tis printed and written to test_config. Count: 2, Interval: 2, print_blk_read: 0\n"
	      "\t\tprint_blk_read/s: 1, print_kb_read/s: 0, print_blk_write: 1\n"
	      "\t\tprint_blk_write/s: 0, print_kb_write/s: 1.");
  print_pass();
  //restore
  dm.set_config(restore);
  dm.write_config();
}


void test_command_wrapper()
{
  test_call();
  test_set_get_file_name();
  test_set_get_command();
  test_set_get_out_to_screen();
  test_set_get_command_arguments();
}

void test_call()
{
  Command_Wrapper cw{"ls", "", "test.temp", 1};
  print_case(1, "Test call system with out to screen and no arguments.");
  user_verify("User should verify that current dir printed to screen\n"
	      "\t\tand that it printed into the output file test.temp");
  print_pass();

  print_case(2, "Test call system with out to screen and arguments.");
  user_verify("User should verify that current dir printed to screen\n"
	      "\t\tand that it printed into the output file test.temp.\n"
	      "\t\tFurthermore it should have outputed hidden files.(../, etc.)");
  print_pass();
}
void test_set_get_file_name()
{
  Command_Wrapper cw{"find .", "| grep test", "test.temp", 1};
  print_case(1, "Get name after construction.");
  assert(cw.get_file_name() == "test.temp");
  print_pass();

  print_case(2, "Set name normal. Implicit get name check.");
  cw.set_file_name("normal.txt");
  assert(cw.get_file_name() == "normal.txt");
  print_pass();

  print_case(3, "Set name empty. Implicit get name check.");
  cw.set_file_name("");
  assert(cw.get_file_name() == "");
  print_pass();
}
void test_set_get_command()
{
  Command_Wrapper cw{"find .", "| grep test", "test.temp", 1};
  print_case(1, "Get command after construction.");
  assert(cw.get_command() == "find .");
  print_pass();

  print_case(2, "Set command normal. Implicit get command check.");
  cw.set_command("ls");
  assert(cw.get_command() == "ls");
  print_pass();

  print_case(3, "Set command empty. Implicit get command check.");
  cw.set_file_name("");
  assert(cw.get_command() == "");
  print_pass();
}
void test_set_get_out_to_screen()
{
  Command_Wrapper cw{"find .", "| grep test", "test.temp", true};
  print_case(1, "Get out_to_screen (ots) after construction (true).");
  assert(cw.get_out_to_screen() == true);
  print_pass();

  Command_Wrapper cw2{"find .", "| grep test", "test.temp", false};
  print_case(2, "Get out_to_screen (ots) after construction (false).");
  assert(cw2.get_out_to_screen() == false);
  print_pass();

  Command_Wrapper cw3{"find .", "| grep test", "test.temp", 12};
  print_case(3, "Get out_to_screen (ots) after construction (true (int cast)).");
  assert(cw3.get_out_to_screen() == true);
  print_pass();

  print_case(4, "Set ots true. Implicit get ots check.");
  cw.set_out_to_screen(true);
  assert(cw.get_out_to_screen() == true);
  print_pass();

  print_case(5, "Set ots true (int cast). Implicit get ots check.");
  cw.set_out_to_screen(12);
  assert(cw.get_out_to_screen() == true);
  print_pass();

  print_case(6, "Set ots false. Implicit get ots check.");
  cw.set_out_to_screen(false);
  assert(cw.get_out_to_screen() == false);
  print_pass();
}
void test_set_get_command_arguments()
{
  Command_Wrapper cw{"find .", "| grep test", "test.temp", 1};
  print_case(1, "Get command arguments after construction.");
  assert(cw.get_command_arguments() == "| grep test");
  print_pass();

  print_case(2, "Set command arguments normal. Implicit get command argumentscheck.");
  cw.set_command_arguments("| grep t");
  assert(cw.get_command_arguments() == "| grep t");
  print_pass();

  print_case(3, "Set command arguments empty. Implicit get command arguments check.");
  cw.set_command_arguments("");
  assert(cw.get_command_arguments() == "");
  print_pass();
}
