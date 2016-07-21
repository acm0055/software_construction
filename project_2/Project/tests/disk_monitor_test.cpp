#include "test_tools.h"
#include "../include/misc/audisktool.h"
#include "../include/monitor/disk_monitor.h"

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
