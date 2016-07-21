#include <fstream>
#include <string>
#include <list>
#include "test_tools.h"
#include "../include/misc/audisktool.h"
#include "../include/parser/sw_parser.h"
using namespace std;

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
