#
# Copyright (c) 2016, Austin Chase Minor
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
# * Neither the name of the copyright holder nor the
#      names of its contributors may be used to endorse or promote products
#      derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL AUSTIN CHASE MINOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# Name: Austin Chase Minor
# Auburn UserID: 903223922
# filename: disk_tool.cpp
# Development Environment: emacs, make, gcc, Linux
# Version: 4/27/16
# Compile: n/a
# Sample usage: n/a
# Sources: no sources
#

CXX = g++
CXXFLAGS = -g -std=c++11

OBJS = disk_report.o disk_config.o command_wrapper.o disk_monitor.o audisktool.o tool.o
TEST_OBJS = command_wrapper_test.o disk_monitor_test.o sw_parser_test.o test_tools.o
PARP = include/parser
MISP = include/misc
MONP = include/monitor
TOOP = include/tool

all: $(OBJS) disk_tool.o
	$(CXX) $(CXXFLAGS) $(OBJS) disk_tool.o -o audisktool
disk_tool.o: include/disk_tool.cpp
	$(CXX) $(CXXFLAGS) -c include/disk_tool.cpp
tool.o: $(TOOP)/tool.cpp
	$(CXX) $(CXXFLAGS) -c $(TOOP)/tool.cpp
command_wrapper.o: $(MISP)/command_wrapper.cpp $(MISP)/command_wrapper.h audisktool.o
	$(CXX) $(CXXFLAGS) -c $(MISP)/command_wrapper.cpp
disk_monitor.o: $(MONP)/disk_monitor.cpp $(MONP)/disk_monitor.h $(MONP)/monitor.h $(MISP)/disk_report.h $(MISP)/disk_config.h audisktool.o
	$(CXX) $(CXXFLAGS) -c $(MONP)/disk_monitor.cpp
audisktool.o: $(MISP)/audisktool.h $(MISP)/audisktool.cpp
	$(CXX) $(CXXFLAGS) -c $(MISP)/audisktool.cpp
disk_report.o :
	$(CXX) $(CXXFLAGS) -c $(MISP)/disk_report.cpp
disk_config.o :
	$(CXX) $(CXXFLAGS) -c $(MISP)/disk_config.cpp
test: $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) tests/tester.cpp -o test
test_tools.o:
	$(CXX) $(CXXFLAGS) -c tests/test_tools.cpp
command_wrapper_test.o: $(OBJS) test_tools.o
	$(CXX) $(CXXFLAGS) -c test_tools.o tests/command_wrapper_test.cpp
sw_parser_test.o: $(OBJS) $(PARP)/sw_parser.h test_tools.o
	$(CXX) $(CXXFLAGS) -c test_tools.o tests/sw_parser_test.cpp 
disk_monitor_test.o: $(OBJS) tests/disk_monitor_test.cpp test_tools.o
	$(CXX) $(CXXFLAGS) -c test_tools.o tests/disk_monitor_test.cpp
