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
 * filename: hw6.cpp
 * Development Environment: Linux emacs gcc
 * Version: 3/8/16
 * Compile: g++ hw6.cpp -std=c++0x -o hw6
 * Sample usage: ./hw6
 * Sources: naming style influence Bjarne Stroustrup The C++ Programming Language 4th Edition &&
 *                  dynamic array indexing  influenced by Dr. Hendrix of Auburn University && friend that I cannot
 *                  remember their name that pointed out that Dr. Qin in his slides referenced a symmetric equals assignment
 */

#include<cassert>
#include<iostream>
#include<string>
using namespace std;

class doctor_t {
private:
  //Structure providing an expontial
  //growth dynamic array. Grows along
  //2^n curve from 1 element.
  struct exp_array_t {
    //metadata for array
    string* elements;
    int size;
    int max_size;

    //Constructs empty array
    //Closes program if out of memory
    exp_array_t()
      try {
	elements = new string[1];
	size = 0;
	max_size = 1;
      }
      catch(...) {
	//free store error
	cout << "Out of memory. Exiting." << endl;
        exit(1);
      }

    //Deconstructs array
    ~exp_array_t() {
      delete[] elements;
    }

    //Copies and assigns array values to another exp_array_t
    exp_array_t& operator=(exp_array_t& input) {
      //delete prevous value
      delete[] elements;

      //copy elements
      elements = new string[input.max_size];
      for (int i = 0; i < input.size; i++)
	elements[i] = input[i];

      //set metadata
      size = input.size;
      max_size = input.max_size;
      
      //return current objects address
      return *this;
    }

    //Puts array in a "freshly constructed" state
    void flush() {
      //free previous memory
      delete[] elements;

      //put it in a state similar to
      //a newly constructed state
      elements = new string[1];
      size = 0;
      max_size = 1;
    }

    //Expands the array to hold more elements
    //Expands by a factor of 2
    //Closes the program if out of memory
    void expand_array()
      try {
	//create new array to expand into
	max_size = max_size * 2;
	string* temp = new string[max_size];

	//copy elements
	for (int i = 0; i < size; i++)
	  temp[i] = elements[i];

	//free previous memory
	//and assign new memory
	delete[] elements;
	elements = &temp[0];
      }
      catch(...) {
	//free store error
	cout << "Out of memory. Exiting." << endl;
	exit(1);
      }

    //Pushes a new element onto the back of the array
    //Grows the array if more room is needed
    //naming style from Bjarne
    void push_back(string elem) {
      if (size == max_size)
	expand_array();

      //Using size as index inspiration
      //from Dr. Hendrix
      elements[size] = elem;
      size++;
    }

    //Provides indexed access to the array
    //No bounds checking
    //Checking in hands of the client
    string& operator[](int i) {
      return elements[i];
    }
  };
  string name;
  exp_array_t patient_list;
public:
  //Constructs an empty doctor
  //If out of memory closes the program
   doctor_t()
     try
       :name{}, patient_list{}
     {
     }
     catch(...) {
       //free store error
       cout << "Out of memory. Exiting." << endl;
       exit(1);
     }
  
  ~doctor_t() {
    //do nothing once doctor_t
    //goes out of scope exp_array_t's
    //deconstructor gets called
  }
  
  //A symmetric equals assignment
  //Thanks to a friend that I cannot remember
  //their name that pointed out Dr. Qin slides had
  //a symmetric equals in mind.
  doctor_t& operator=(doctor_t& rvalue) {
    this->set_doctor_name(rvalue.name);
    patient_list = rvalue.patient_list;
    return *this;
  }

  //Initializes the doctor object with user input from cin.
  void user_init_doctor();

  //Prints the doctors name and patients
  void print_doctor_t() {
    cout << "Doctor " << name
	 << endl << "Patients: " << endl;

    //print patient list
    for (int i = 0; i < get_num_patients(); i++)
      cout << '\t' << patient_list[i] << endl;
  }

  //Resets the number of patients
  //and patient list
  void reset_patient_load() {
    patient_list.flush();
  }

  //Returns the number of patients
  int get_num_patients() {
    return patient_list.size;
  }

  //Returns the doctors name
  string& get_doctor_name() {
    return name;
  }

  //Returns a patient from the doctors list
  //Returns the doctors name for bound failure
  string& get_patient_x(int i) {
    if (i > get_num_patients() || i < 0) {
      cout << "Dr. " << name
	   << " does not have a patient "
	   << i << endl;

      return name;
    }
    
    return patient_list[i];
  }

  //Adds a patient to the end of the
  //doctors list.
  void add_patient(string name) {
    patient_list.push_back(name);
  }

  //Sets the doctos name
  void set_doctor_name(string name) {
    this->name = name;
  }
};

//Initializes the doctor object with user input from cin.
void doctor_t::user_init_doctor() {
  //start anew with a "freshly constructed" state
  //doctor object
  reset_patient_load();
  
  cout << "User initalization of a doctor." << endl
       << "Enter name of doctor: ";
  getline(cin, name);
  cin.clear();

  char user_input{};
  cout << "Would you like to create patient(s) for"
       << " Doctor " << name << ". Yes/No (y/n)? ";
  cin >> user_input;
  //flush input stream of newline char
  (cin.peek() == '\r') ? cin.ignore() : cin;
  (cin.peek() == '\n') ? cin.ignore() : cin;

  switch(user_input) {
  case 'y':
  case 'Y':
    string temp;
    do {
      cout << "Enter name of patient: ";
      getline(cin, temp);

      patient_list.push_back(temp);

      cout << "Would you like to create more patient(s) for"
	   << " Doctor " << name << ". Yes/No (y/n)? ";
      cin >> user_input;

      //flush input stream of newline char
      (cin.peek() == '\r') ? cin.ignore() : cin;
      (cin.peek() == '\n') ? cin.ignore() : cin;
    } while(user_input != 'n' && user_input != 'N');
  }
}


#define UNIT_TESTING

//Testing for the doctor_t class
//if UNIT_TESTING is defined
#ifdef UNIT_TESTING
//testing methods impilicitly test accessors and mutators
void test_constructor();
void test_equ_operator();
void test_user_init();
void test_print();
void test_reset();

int main() {
   cout << "*** Unit testing for the doctor_t class ***"
       << endl << "***    Author: Austin Chase Minor     ***"
       << endl << "***   Email: acm0055@auburn.edu   ***"
       << endl;

   test_constructor();
   test_user_init();
   test_equ_operator();
   test_print();
   test_reset();

   cout << "*** End of unit testing for doctor_t class ***" << endl;
}

void test_constructor() {
  cout << "-> Testing doctor_t constructor:" << endl;
  doctor_t chad{};
  //no patients and no name is default constructor invarient
  assert(chad.get_num_patients() == 0);
  assert(chad.get_doctor_name() == string{});
  cout << "\t+ Passed..." << endl;
}

void test_user_init() {
  cout << "-> Testing user initalization. Please do the following:" << endl
       << "\t- Enter no doctor name" << endl
       << "\t- Enter no patients" << endl;

  doctor_t chad{};
  chad.user_init_doctor();

  //Test invarient
  assert(chad.get_doctor_name() == string{});
  assert(chad.get_num_patients() == 0);

  cout << "-> Testing user initalization. Please do the following:" << endl
       << "\t- Enter a doctor name (Chad Oval)" << endl
       << "\t- Enter no patients" << endl;

  chad.user_init_doctor();

  //Test invarient
  assert(chad.get_doctor_name() == "Chad Oval");
  assert(chad.get_num_patients() == 0);

  cout << "-> Testing user initalization. Please do the following:" << endl
       << "\t- Enter a doctor name (Chad Oval)" << endl
       << "\t- Enter one patient (Fyodor Rominov)" << endl;

  chad.user_init_doctor();

  //Test invarient
  assert(chad.get_doctor_name() == "Chad Oval");
  assert(chad.get_num_patients() == 1);
  assert(chad.get_patient_x(0) == "Fyodor Rominov");

  cout << "-> Testing user initalization. Please do the following:" << endl
       << "\t- Enter a doctor name (Chad Oval)" << endl
       << "\t- Enter multiple patients" << endl
       << "\t-Varify them with a console printed list" << endl;

  chad.user_init_doctor();

  //Test invarient
  assert(chad.get_doctor_name() == "Chad Oval");

  cout  << endl;
  chad.print_doctor_t();
  cout << endl;
  
  cout << "\t+ Passed..." << endl;
}

void test_equ_operator() {
  cout << "-> Testing doctor_t =operator" << endl;
  
  doctor_t chad{};
  chad.set_doctor_name("chad");
  chad.add_patient("test");
  chad.add_patient("testing");
  chad.add_patient("last test");

  doctor_t copy{};
  copy = chad;
  
  //Testing Invarient
  assert(chad.get_num_patients() == copy.get_num_patients());
  assert(chad.get_doctor_name() == copy.get_doctor_name());
  assert(chad.get_patient_x(0) == copy.get_patient_x(0));
  assert(chad.get_patient_x(1) == copy.get_patient_x(1));
  assert(chad.get_patient_x(2) == copy.get_patient_x(2));

  chad.reset_patient_load();
  chad.set_doctor_name("");

  copy = chad;
  
  //Testing Invarient
  assert(chad.get_num_patients() == copy.get_num_patients());
  assert(chad.get_doctor_name() == copy.get_doctor_name());

  cout << "\t-Tester should check that error message appears:" << endl;
  chad.get_patient_x(1);

  cout << "\t+ Passed..." << endl;
}

void test_print() {
  cout << "-> Testing doctor_t print" << endl;
  cout << "\t- Tester should verify that the proper"
       << " doctor name and list prints" << endl
       << "\t- Doctor: chad Patient List: 'test' 'testing' 'last test'"
       << endl << endl;

  doctor_t chad{};
  chad.set_doctor_name("chad");
  chad.add_patient("test");
  chad.add_patient("testing");
  chad.add_patient("last test");

  chad.print_doctor_t();
  cout << endl;

  cout << "\t+ Passed..." << endl;
}

void test_reset() {
  cout << "-> Testing doctor_t reset" << endl;
  
  doctor_t chad{};
  chad.set_doctor_name("chad");
  chad.add_patient("test");
  chad.add_patient("testing");
  chad.add_patient("last test");

  chad.reset_patient_load();

  //Testing invarient
  assert(chad.get_doctor_name() == "chad");
  assert(chad.get_num_patients() == 0);

  cout << "\t+ Passed..." << endl;
}
#endif
