#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <regex>
#include <initializer_list>

using namespace std;

// function to clear standard input buffer
void clear();

void menu();

bool energyProviderID(const string &input);

bool provinceID(const string& input);

string provinceIDPrompt();

bool customerID(const string& input);

string customerIDPrompt();

bool billingID(const string& input);

string billingIDPrompt();

bool phoneNumber(const string& input);

string phoneNumberPrompt();

bool number(const string &input);

bool name(const string& input);

string namePrompt();

bool address(const string& input);

string addressPrompt();

bool orderID(const string& input);

string orderIDPrompt();

bool fileName(const string& input);

string filenamePrompt();

// Second parameter is a function pointer to any of the regex functions of the form having the signature string identifier();
void getField(string &input,  bool (*re_ptr)(const string&), string prompt);

#endif