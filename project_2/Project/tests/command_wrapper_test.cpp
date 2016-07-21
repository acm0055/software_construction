#include <cassert>
#include <string>
#include "../include/misc/command_wrapper.h"
#include "test_tools.h"
#include "command_wrapper_test.h"

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
