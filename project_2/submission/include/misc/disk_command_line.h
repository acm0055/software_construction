#ifndef DISK_COMMAND_LINE_H
#define DISK_COMMAND_LINE_H 1

#include <vector>
#include <string>
using namespace std;

namespace disk_command_line {
  struct disk_command {
    string command;
    vector<string> arguments;
    disk_command_line* next; //used for piped commands "|"
  }

  void parse_command(disk_command& cmd);
}
#endif /*DISK_COMMAND_LINE_H*/
