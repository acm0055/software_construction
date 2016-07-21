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
 * filename: user.cpp
 * Development Environment: emacs, make, gcc, Linux
 * Version: 4/10/16
 * Compile: make
 * Sample usage: n/a
 * Sources: no sources
 */
#include "user.h"

//Modifies the users properties
//based on the modifications presented.
void mod_user_prop(user_prop& prop, const user_prop& mods)
{
  prop.intelligence += mods.intelligence;
  prop.money += mods.money;
  prop.time += mods.time;
}

//Makes a new user from user inputs.
void init_user(user& user_in, string name, unsigned short pos,
	       user_prop init_props)
{
  user_in.name = name;
  user_in.pos = pos;
  user_in.attr = init_props;
}

//Checks is a user is dead
//'a': user died from time
//'b': user died from money
//'c': user died from intelligence
// 0 : not dead
char is_user_dead(const user& user_in)
{
  if (user_in.attr.time <= 0)
    return 'a';
  else if (user_in.attr.money <= 0)
    return 'b';
  else if (user_in.attr.intelligence <= 0)
    return 'c';
  else
    return 0;
}
