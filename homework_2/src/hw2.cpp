/*
 * Copyright (c) 2016, Austin Minor
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
 * filename: hw2.cpp
 * Development Environment: emacs, g++, Linux
 * Version: 1/29/16 
 * Compile: g++ hw2.cpp -std=c++11 -o hw1
 *                          or for older gcc versions
 *                    g++ hw2.cpp -std=c++0x -o hw1
 * Sample usage: ./hw2
 * Sources: I did not use any sources for this assignment.
 *
 * Program for computing (if it exists) the amortization chart
 * of a given loan. Relies on user input to for the data and
 * print a formated chart with summary of the amortization.
 */

#include<iostream>
#include<iomanip>
using namespace std;

//introduce methods into the namespace
void print_menu();
void print_line(int, double, double, double, double, double);

int  TERM_WIDTH {60};
const double RATE_TO_PERCENT {1e-2};
const int NORM_COL_WIDTH {10};

//Program to calculate the amortization table
//of a given loan. Returns with an error message
//if loan cannot be repayed.
int main() {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  int month{};
  double balance = 0,
    payment = 0,
    rate = 0,
    interest = 0,
    principal = 0,
    monthly_rate = 0,
    tot_interest = 0;
    

  cout << "Loan Amount: ";
  cin >> balance;

  cout << "Interest Rate (% per year): ";
  cin >> rate;

  cout << "Monthly Payments: ";
  cin >> payment;
  cout << endl;

  monthly_rate = rate / 12;

  //Checks to see if the payment is greater than
  //the initial interest. Exits if it is not.
  if(payment < (monthly_rate * RATE_TO_PERCENT * balance)) {
    cout << "Monthly payments must be greater than"
	 << " interest. You will not pay off loan"
	 << " on this scheme. Exiting.\n";
    return 0;
  }
      
  print_menu();

  //Print the intial day 0 loan information
  print_line(month, balance, payment, rate, interest, principal);
  month++;

  //Calculate the monthly loan information
  while(balance > 0) {
    interest = balance * monthly_rate * RATE_TO_PERCENT;
    tot_interest += interest;

    principal = payment - interest;
    balance -= principal;

    //Determines if the month's payment is more
    //than what is owed and responds accordingly.
    if(balance + balance * monthly_rate * RATE_TO_PERCENT < 0) {
      principal += balance;
      payment = principal;
      balance = 0;
    }
    
    print_line(month, balance, payment, monthly_rate, interest, principal);

    month++;
  }

  //print row of stars for formating interface
  for(int i = 0; i < TERM_WIDTH; i++) {
    cout << "*";
  }
  cout << endl << endl;
  //Print end results
  //Shift month result because intecremented
  //one past on exiting result loop
  cout << "It takes " << (month - 1)
       << " months to pay off the loan." << endl
       << "Total interest paid is: $" << tot_interest << endl;
  return 0;
}

//Prints intro menu with title and
//column labels for the program.
void print_menu() {
  //print row of stars for formating interface
  for(int i = 0; i < TERM_WIDTH; i++) {
    cout << "*";
  }
  //print title
  cout << endl << "          "
       << "Amortization Table"
       << endl;
  //print row of stars for formating interface
  for(int i = 0; i < TERM_WIDTH; i++) {
    cout << "*";
  }
  cout << endl;
  
  //print columns labels
  cout << left << setw(NORM_COL_WIDTH) << "Month" << left << setw(NORM_COL_WIDTH)  << "Balance"
       << left << setw(NORM_COL_WIDTH) << "Payment" << left << setw(NORM_COL_WIDTH)
       << "Rate" <<  left << setw(NORM_COL_WIDTH) << "Interest" << left
       << setw(NORM_COL_WIDTH) << "Principal" << endl;
}

//Prints the next payment line following the spacing
//set forth by the individual description columns.
//Attempts to print the infomation left justified below each relavant
//column, but assures that at least 1 space exists between elements.
//int month: current month
//double balance: current balance
//double payment: current payment
//double rate: current rate
//double interest: current interest
//double principal: current principal
void print_line (int month, double balance, double payment,
		 double rate, double interest, double principal) {
  
  //Always starts with a balance and a month.
  //IE no possibility of a "N\A".
  cout << left << setw(NORM_COL_WIDTH) << month;
  //shift width because of $
  cout << left << "$" << setw(NORM_COL_WIDTH - 1) << balance;
  
  switch (month) {
  case 0:
    cout << left << setw(NORM_COL_WIDTH) << "N\\A";
    break;
  default:
    //shift width because of $
    cout << left << "$" << setw(NORM_COL_WIDTH - 1) << payment;
  }

  switch (month) {
  case 0:
    cout <<  left << setw(NORM_COL_WIDTH) << "N\\A";
    break;
  default:
    //change precision to print rate
    //then change it back
    cout.precision(1);

    cout << left << setw(NORM_COL_WIDTH) << rate;
    
    cout.precision(2);
  }

  switch (month) {
  case 0:
    cout << left << setw(NORM_COL_WIDTH) << "N\\A";
    break;
  default:
    //shift width because of $
    cout << left << "$" << setw(NORM_COL_WIDTH - 1) << interest;
  }

  switch (month) {
  case 0:
    cout << left << setw(NORM_COL_WIDTH) << "N\\A";
    break;
  default:
    //shift width because of $
    cout << left << "$" << setw(NORM_COL_WIDTH) << principal;
  }
  
  cout << endl;
}
