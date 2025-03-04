#include <iostream>
#include <regex>
#include <initializer_list>
#include "library.hpp"

using namespace std;

// function to clear standard input buffer
// it is necessary
void clear(){
    int c;
    while((c = getchar()) != '\n' && c != EOF)
        continue;
}

// here we will add menu options
void menu(){
	cout << "1.) Manage Customer" << endl;
	cout << "	11.) Add New Customer" << endl;
	cout << "	12.) Remove Customer" << endl;
	cout << "	13.) View/Edit Customer" << endl;
	cout << "	14.) View Customers by Province" << endl;
}

// I overloaded all the validation functions

// functions of this form are to be passed into another function as a function pointer
string energyProviderID() {
	return string("0[0-9]{3}");
}

// functions of this form are to be used for direct validation of a string
bool energyProviderID(const string &input) {
	return regex_match(input, regex{ "0[0-9]{3}" });
}

string provinceID() {
	return string("1[0-9]{3}");
}

bool provinceID(const string& input) {
	return regex_match(input, regex{ "1[0-9]{3}" });
}

string CustomerID() {
	return string("2[0-9]{3}");
}

bool customerID(const string& input) {
	return regex_match(input, regex{ "2[0-9]{3}" });
}

string BillingID() {
	return string("3[0-9]{3}");
}

bool BillingID(const string& input) {
	return regex_match(input, regex{ "3[0-9]{3}" });
}

string phoneNumber() {
	return string("[0-9]{3}-[0-9]{3}-[0-9]{4}|[0-9]{10}");
}

bool phoneNumber(const string& input) {
	return regex_match(input, regex{ "[0-9]{3}-[0-9]{3}-[0-9]{4}|[0-9]{10}" });
}

string number() {
	return string("[+-]?(\\d+|(\\d*\\.\\d+)?)");
}

bool number(const string &input) {
	return regex_match(input, regex{ "[+-]?(\\d+|(\\d*\\.\\d+))" });
}

string date(){
    return string("(\\d{2}-(0?[1-9]|1[012])-\\d{4})|(0?[1-9]|1[012])-\\d{2}-\\d{4}");
}

bool date(const string &input) {
	return regex_match(input, regex{ "(\\d{2}-(0?[1-9]|1[012])-\\d{4})|(0?[1-9]|1[012])-\\d{2}-\\d{4}" });
}

string name(){
    return string("\\s*[a-zA-Z]+\\s+[a-zA-Z]+\\s*");
}

bool name(const string& input) {
	return regex_match(input, regex{ "\\s*[a-zA-Z]+\\s+[a-zA-Z]+\\s*" });
}

// Second parameter is a function pointer to any of the regex functions of the form having the signature string identifier();
void getField(string &input, const string (*re_ptr)()) {
	do {
		cout << "Enter field : ";
		getline(cin, input);
        clear();
	} while (!regex_match(input, regex(re_ptr())));
}