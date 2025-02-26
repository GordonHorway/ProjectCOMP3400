#include <iostream>
#include <unordered_map>
#include <initializer_list>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

#pragma once

#include "library.hpp"

int main() {

    try {
        EnergyProvider BigEnergy("BigEnergy", { "Ontario", "Quebec", "Alberta", "Manitoba", "Saskatchewan" });

        std::string CustomerID, Fname, Lname, PhoneNumber, Email, Street, City, PostalCode, PName;
        double balance = 0.0;

        std::string line;
        std::ifstream inFile;
        std::string filename;
        std::string token;
        std::vector<std::string> tokens;

        int choice;
        double amount;
        std::string input;

        while (true) {
            std::cout << "\n0.) Enter input file\n1.) Make payment\n2.) Customer Information\n3.) Add Customer\n4.) Delete Customer\n5.) Show all Customers\n6.) Overdue Customers\n7.) Exit\n\n";
            std::cout << "Enter choice : ";
            std::cin >> choice;
            switch (choice) {
            case 0:
                filename = getFile(inFile);
                while (std::getline(inFile, line)) {
                    std::stringstream ss(line);
                    while (getline(ss, token, ',')) {
                        tokens.push_back(token);
                    }
                    if (tokens.size() == 10) {
                        BigEnergy.addCustomer(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], std::stod(tokens[5]), tokens[6], tokens[7], tokens[8], tokens[9]);
                    }
                    else {
                        throw std::invalid_argument("Invalid number of arguments!");
                    }
                    tokens.clear();
                }
                inFile.close();
                break;
            case 1:
                input = getCustomerID(input);
                std::cout << "Enter amount : ";
                std::cin >> amount;
                BigEnergy.makePayment(input, amount);
                break;
            case 2:
                input = getCustomerID(input);
                BigEnergy.printCustomer(input);
                break;
            case 3:
                getCustomerInfo(input, CustomerID, Fname, Lname, PhoneNumber, Email, balance, Street, City, PostalCode, PName);
                BigEnergy.addCustomer(CustomerID, Fname, Lname, PhoneNumber, Email, balance, Street, City, PostalCode, PName);
                break;
            case 4:
                input = getCustomerID(input);
                BigEnergy.removeCustomer(input);
                break;
            case 5:
                BigEnergy.printCustomers();
                break;
            case 6:
                BigEnergy.printOverdue();
                break;
            case 7:
                std::cout << "Goodbye!\n";
                std::exit(0);
            default:
                std::cout << "Not a valid choice!!\n";
            }
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

}