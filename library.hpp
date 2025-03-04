#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <regex>
#include <initializer_list>

using namespace std;

// function to clear standard input buffer
// it is necessary
void clear();

// here we will add menu options
void menu();
// I overloaded all the validation functions

// functions of this form are to be passed into another function as a function pointer
string energyProviderID();

// functions of this form are to be used for direct validation of a string
bool energyProviderID(const string &input);

string provinceID();

bool provinceID(const string& input);

string CustomerID();

bool customerID(const string& input);

string BillingID();

bool BillingID(const string& input);

string phoneNumber();

bool phoneNumber(const string& input);

string number();

bool number(const string &input);

string date();

bool date(const string &input);

string name();

bool name(const string& input);

// Second parameter is a function pointer to any of the regex functions of the form having the signature string identifier();
void getField(string &input, const string (*re_ptr)());

#endif