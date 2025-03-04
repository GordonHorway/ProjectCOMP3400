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

bool energyProviderID(const string &input);

bool provinceID(const string& input);

bool customerID(const string& input);

bool BillingID(const string& input);

bool phoneNumber(const string& input);

bool number(const string &input);

bool date(const string &input);

bool name(const string& input);

bool address(const string& input);

// Second parameter is a function pointer to any of the regex functions of the form having the signature string identifier();
void getField(string &input,  bool (*re_ptr)(const string&), string prompt);

#endif