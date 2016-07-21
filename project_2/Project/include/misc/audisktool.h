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
 * filename: audisktool.h
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/26/16
 * Compile: n/a
 * Sample usage: n/a
 * Sources: no sources
 */

#ifndef AUDISKTOOL_H
#define AUDISKTOOL_H 1

#include <string>
#include <ctime>
using namespace std;

namespace audisktool {
  template <typename T>
    struct sm_key_val
    {
      string key;
      T value;
    };

  struct result : sm_key_val<string>
  {
  };

  struct disk_item : sm_key_val<string>
  {
  };

  struct config_item : sm_key_val<string>
  {
  };

  struct disk_config {
    double interval;
    unsigned int count;
    bool print_blk_read;
    bool print_blk_read_s;
    bool print_kb_read_s;
    bool print_blk_write;
    bool print_blk_write_s;
    bool print_kb_write_s;
  };

  struct disk_result {
    unsigned int major_dev_num;
    unsigned int minor_dev_num;
    string dev_name;
    unsigned int num_read_comp;
    unsigned int num_reads_merged;
    unsigned int num_sector_read;
    unsigned int num_milli_read;
    unsigned int num_writes_comp;
    unsigned int num_writes_merged;
    unsigned int num_sector_written;
    unsigned int num_milli_write;
    unsigned int num_io_cur;
    unsigned int num_milli_io;
    unsigned int weighted_num_milli_io;
  };

  void delay(double delay);
}

#endif /*AUDISKTOOL_H*/
