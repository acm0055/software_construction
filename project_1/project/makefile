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
# filename: makefile
# Development Environment: emacs, make, gcc, Linux
# Version: 4/11/16
# Compile: n/a
# Sample usage: n/a
# Sources: two links listed below for help on errors in makefile
#

CXX = g++
CXXFLAGS = -std=c++11
game_engine_objs = encounter.o game_play.o puzzle.o user.o menu.o

#help from http://stackoverflow.com/questions/20237490/error-in-makefile-multiple-definition-of-start
#and https://bbs.archlinux.org/viewtopic.php?id=125003 for fixing some errors in makefile
game: $(game_engine_objs) acm0055-project1.cpp
	$(CXX) $(CXXFLAGS) -o game $(game_engine_objs) acm0055-project1.cpp
test: $(game_engine_objs) tests/test.cpp
	$(CXX) $(CXXFLAGS) -o test_game $(game_engine_objs) tests/test.cpp
encounter.o: include/game_engine/encounter.cpp user.o
	$(CXX) $(CXXFLAGS) -c include/game_engine/encounter.cpp user.o
game_play.o: include/game_engine/game_play.cpp
	$(CXX) $(CXXFLAGS) -c include/game_engine/game_play.cpp
puzzle.o: include/game_engine/puzzle.cpp
	$(CXX) $(CXXFLAGS) -c include/game_engine/puzzle.cpp
user.o: include/game_engine/user.cpp
	$(CXX) $(CXXFLAGS) -c include/game_engine/user.cpp
menu.o: include/game_engine/menu.cpp
	$(CXX) $(CXXFLAGS) -c include/game_engine/menu.cpp
