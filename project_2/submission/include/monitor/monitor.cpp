#include <iostream>
#include <string>
#include <list>
#include "monitor.h"
#include "../parser/sw_parser.h"
#include "../misc/audisktool.h"
using namespace std;

template <class T>
Monitor<T>::Monitor(string res_file_name_in, string config_name_in,
		    string help_diag_in, Command_Wrapper data_grabber_in,
		    SW_Parser<T> parser_in)
{
  res_file_name = res_file_name_in;
  config_name = config_name_in;
  help_diag = help_diag_in;
  data_grabber = data_grabber_in;
  parser = parser_in;
}

template <class T>
void Monitor<T>::print_results()
{
  for (result x : results) {
    cout << x.key << " " << x.value << endl;
  }
}

template <class T>
string Monitor<T>::set_config_file_name()
{
  string temp;
  temp = config_name;

  return temp;
}

template <class T>
string Monitor<T>::set_output_file_name()
{
  string temp;
  temp = res_file_name;
  
  return res_file_name;
}

template <class T>
const string& Monitor<T>::get_config_file_name()
{
  return config_name;
}

template <class T>
const string& Monitor<T>::get_output_file_name()
{
  return res_file_name;
}
