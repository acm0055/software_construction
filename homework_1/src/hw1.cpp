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
 * * Neither the name of Austin Chase Minor nor the
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
 * filename: hw1.cpp
 * Development Environment: emacs, g++, Linux
 * Version: 1/21/16 
 * Compile: g++ hw1.cpp -std=c++11 -o hw1
 *           or for older gcc versions
 *          g++ hw1.cpp -std=c++0x -o hw1
 * Sample usage: ./hw1
 * Sources: I did not use any external sources for
 * this assignment.
 *
 * Program for deteriming the amount of diet soda
 * a person may drink without dying from the toxicity
 * of the artifial sweetener used in diet soda.
 * Toxicity determined from the amount of sweetener
 * needed to kill a mouse of a certain weight.
 *
 */

#include <iostream>

int main() {
  //w_ denotes weights
  const double W_SWEETENER_PER_SODA{1e-3};
  double w_mouse{};
  double w_dieter{};
  double w_lethal{};
  double ratio_lethal{};
  int num_soda{};
  
  std::cout << "What is the amount of artificial"
	    << " sweetener needed to kill a mouse: ";
  std::cin >> w_lethal;
  
  std::cout << "What is the weight of the mouse: ";
  std::cin >> w_mouse;

  std::cout << "What is the weight of the dieter: ";
  std::cin >> w_dieter;

  //Calculates the lethal amount of soda
  //based on the results of dimensional
  //analysis of the variables.
  ratio_lethal = w_lethal / w_mouse;
  num_soda = static_cast<int>((ratio_lethal * w_dieter)
			      / W_SWEETENER_PER_SODA);

  std::cout << "You can drink " << num_soda << " diet soda"
	    << " without dying as a result.\n";

  return 0;
}
