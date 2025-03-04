#include <iostream>
#include <regex>
#include <initializer_list>
#include "library.hpp"

using namespace std;

// function to clear standard input buffer
void clear(){
    int c;
    while((c = getchar()) != '\n' && c != EOF)
        continue;
}

void menu(){
	cout << "0.) Read Input File" << endl;
	cout << "1.) Manage Customer" << endl;
	cout << "	11.) Add New Customer" << endl;
	cout << "	12.) Remove Customer" << endl;
	cout << "	13.) View/Edit Customer" << endl;
	cout << "	14.) View Customers by Province" << endl;
    cout << "2.) Manage Prices" << endl;
    cout << "	21.) Display All Prices" << endl;
    cout << "   	22.) Edit Oil Price" << endl;
    cout << "   	23.) Edit Solar Price" << endl;
    cout << "   	24.) Edit Nuclear Price" << endl;
	cout << "3.) Manage Orders" << endl;
	cout << "	31.) Create Order" << endl;
	cout << "	32.) Edit Order" << endl;
	cout << "	33.) Check-out Order" << endl;
	cout << "5.) Exit" << endl;
}

bool energyProviderID(const string &input) {
	return regex_match(input, regex{ "0[0-9]{3}" });
}

bool provinceID(const string& input) {
	return regex_match(input, regex{ "1[0-9]{3}" });
}

bool customerID(const string& input) {
	return regex_match(input, regex{ "2[0-9]{3}" });
}

bool billingID(const string& input) {
	return regex_match(input, regex{ "3[0-9]{3}" });
}

bool orderID(const string& input){
	return regex_match(input, regex("4[0-9]{3}"));
}

bool phoneNumber(const string& input) {
	return regex_match(input, regex{ "[0-9]{3}-[0-9]{3}-[0-9]{4}|[0-9]{10}" });
}

bool number(const string &input) {
	return regex_match(input, regex{ "[+-]?(\\d+|(\\d*\\.\\d+))" });
}

bool date(const string &input) {
	return regex_match(input, regex{ "(\\d{2}-(0?[1-9]|1[012])-\\d{4})|(0?[1-9]|1[012])-\\d{2}-\\d{4}" });
}

bool name(const string& input) {
	return regex_match(input, regex{ "\\s*[a-zA-Z]+\\s+[a-zA-Z]+\\s*" });
}

bool address(const string& input){
	return regex_match(input, regex{"[0-9]{4}\\s+[a-zA-Z]+\\s+[a-zA-Z]+"});
}

void getField(string &input, bool (*re_ptr)(const string&), string prompt) {
	do {
		cout << prompt;
		getline(cin, input);
	} while (!re_ptr(input));
}