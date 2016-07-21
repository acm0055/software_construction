#include "command_wrapper_test.h"
#include "disk_monitor_test.h"
#include "sw_parser_test.h"

int main()
{
  test_disk_monitor();
  test_command_wrapper();
  test_sw_parser();
}
