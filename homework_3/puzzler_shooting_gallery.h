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
 * DISCLAIMED. IN NO EVENT SHALL Austin Chase Minor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Name: Austin Minor
 * Auburn UserID: 903223922
 * filename: puzzler_shooting_gallery.h
 * Development Environment: emacs, g++, Linux, make
 * Version: 2/4/16
 * Compile: compiled as part of the main program
 * Sources: I did not use any sources for this assignment.
 *
 * Methods for simulating a duel between three parties
 * Aaron, Bob, and Charlie with two seperate strategies for Aaron.
 */

//Tests to see if at least two people are alive
//and thus the shooting game is not over.
bool at_least_two_alive(bool, bool, bool);
//Aaron shoots at the person with the
//highest possible hit chance first.
//He has a 33% hit ratio.
//Inputs are modified to reflect result of shot.
void aaron_shoots1(bool&, bool&);
//Aaron shoots at the person with the
//highest possible hit chance first.
//If everyone is alive (it is the first round of
//shooting), he misses, else
//he has a 33% hit ratio.
//Inputs are modified to reflect result of shot.
void aaron_shoots2(bool&, bool&);
//Bob shoots at the person with the
//highest possible hit chance first.
//He has a 50% hit ratio.
//Inputs are modified to reflect result of shot.
void bob_shoots(bool&, bool&);
//Charlie shoots at the person with the
//highest possible hit chance first.
//He has a 100% hit ratio.
//Inputs are modified to reflect result of shot.
void charlie_shoots(bool&, bool&);
