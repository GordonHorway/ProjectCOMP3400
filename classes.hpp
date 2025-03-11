#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <initializer_list>
#include <fstream>
#include <sstream>
#include "library.hpp"

using namespace std;

constexpr int num_provinces = 5;
constexpr int num_customers = 100;
constexpr int num_energy_types = 3;

class Bill {
    public:
    string B_id;            // (Primary Key)
    string B_C_id;          // (Foreign Key) (CUSTOMER)
    string B_issueDate;
    string B_dueDate;      // (Calculated field -> Issue Date)
    bool B_overdue;
    double B_balance;       // (Calculated field -> Counts x Costs)
    double B_amtPaid;
    double B_oilCount;
    double B_solarCount;
    double B_nuclearCount;
    double B_oilCost;       // (Recorded at BILL creation)
    double B_solarCost;     // (Recorded at BILL creation)
    double B_nuclearCost;   // (Recorded at BILL creation)
    Bill() = default;
    Bill(string B_id,          
        string B_C_id,         
        string B_issueDate,
        string B_dueDate,   
        bool B_overdue,
        double B_balance,       
        double B_amtPaid,
        double B_oilCount,
        double B_solarCount,
        double B_nuclearCount,
        double B_oilCost,    
        double B_solarCost,
        double B_nuclearCost):B_id{B_id}, B_C_id{B_C_id}, B_issueDate{B_issueDate}, B_dueDate{B_dueDate}, B_overdue{B_overdue}, B_balance{B_balance}, B_amtPaid{B_amtPaid}, B_oilCount{B_oilCount}, B_solarCount{B_solarCount}, B_nuclearCount{B_nuclearCount}, B_oilCost{B_oilCost}, B_solarCost{B_solarCost}, B_nuclearCost{B_nuclearCost} {}
    Bill &billPrinter(){
        cout << "B_id : " << B_id << endl << "B_C_id : " << B_C_id << endl << "B_issueDate : " << B_issueDate << endl;
        cout << B_dueDate << endl << (B_overdue ? "Overdue" : "Not Overdue") << endl << B_balance << endl;
        cout << B_amtPaid << endl << B_oilCount << endl << B_solarCount << endl;
        cout << B_nuclearCount << endl << B_oilCost << endl << B_solarCost << endl << B_nuclearCost << endl;
        return (*this);
    }
};

class Order {
    public:
    string O_id;            // (Primary Key)
    string O_C_id;          // (Foreign Key) (CUSTOMER)
    string O_oilCount;
    string O_solarCount;
    string O_nuclearCost;
    Order() = default;
    Order(string O_id, string O_C_id, string O_oilCount, string O_solarCount, string O_nuclearCost){
        this->O_id = O_id;
        this->O_C_id = O_C_id;
        this->O_oilCount = O_oilCount;
        this->O_solarCount = O_solarCount;
        this->O_nuclearCost = O_nuclearCost;   
    }
};

class Customer {
    public:
    string C_id;
    string C_name;
    string C_address;
    string C_phone;
    string C_R_id;
    Order order;
    Bill bill;
    Customer() = default;
    Customer(string C_id, string C_name, string C_address, string C_phone, string C_R_id){
        this->C_id = C_id;
        this->C_name = C_name;
        this->C_address = C_address;
        this->C_phone = C_phone;
        this->C_R_id = C_R_id;
    }
    void printInfo() const {
        cout << "C_id : " << C_id << endl;
        cout << "C_name : " << C_name << endl;
        cout << "C_address : " << C_address << endl;
        cout << "C_phone : " << C_phone << endl;
        cout << "C_R_id : " << C_R_id << endl;
    }
    void createOrder(string O_id, string O_C_id, string O_oilCount, string O_solarCount, string O_nuclearCost){
        order = Order(O_id, O_C_id, O_oilCount, O_solarCount, O_nuclearCost);
    }
    void editCustomerInfo(){
        int choice;
        while(true){
        cout << "1.) Customer Name\n2.) Customer Address\n3.) Customer Phone Number\n4.) Customer Province ID\n5.) Exit\n";
        cout << "Enter number to edit field : ";
        cin >> choice;
        clear();
        switch(choice){
            case 1:
                getField(C_name, name, namePrompt());
            break;
            case 2:
                getField(C_address, address, addressPrompt());
            break;
            case 3:
                getField(C_phone, phoneNumber, phoneNumberPrompt());
            break;
            case 4:
                getField(C_R_id, provinceID, provinceIDPrompt());
            break;
            case 5:
                goto out;
            default:
                cout << "Not a valid choice" << endl;
        }
        }
        out:;
    }
    void editOrder(){
        int choice;
        while(true){
        cout << "1.) Oil Count\n2.) Solar Count\n3.) Nuclear Count\n4.) Exit\n";
        cout << "Enter number to edit field : ";
        cin >> choice;
        clear();
        switch(choice){
            case 1:
                getField(order.O_nuclearCost, number, "Enter Nuclear Cost : ");
            break;
            case 2:
                getField(order.O_oilCount, number, "Enter Oil Count : ");
            break;
            case 3:
                getField(order.O_solarCount, number, "Enter Solar Count : ");
            break;
            case 4:
                goto out;
            default:
                cout << "Not a valid choice" << endl;
        }
        }
        out:;
    }
    // Bill is created here
    void checkoutOrder(){

    }
};

class Province {
    public:
    string P_id;
    string P_name;
    Province() = default;
    Province(string P_id, string P_name){
        this->P_id = P_id;
        this->P_name = P_name;
    }
    unordered_map<string, Customer> customers;
};

class EnergyProvider {
    public:
    string E_id;
    string E_name;
    double oilPrice;
    double solarPrice;
    double nuclearPrice;
    EnergyProvider(string filename, string E_id, string E_name, initializer_list<pair<string, string>> list){
        this->E_id = E_id;
        this->E_name = E_name;
        provinces.reserve(num_provinces);
        for(auto const &pair : list){
            Province province(pair.first, pair.second);
            provinces.push_back(province);
        }
        /* 
           you can add database connection functionality
           Write infomation to database as well
        */
        ifstream inFile(filename);
        string energyType;
        string cost;
        inFile >> energyType >> cost;
        oilPrice = stod(cost);
        inFile >> energyType >> cost;
        solarPrice = stod(cost);
        inFile >> energyType >> cost;
        nuclearPrice = stod(cost);
        inFile.close();
    }
    void displayAllPrices(){
        cout << "Oil Price :$" << oilPrice << endl;
        cout << "Solar Price :$" << solarPrice << endl;
        cout << "Nuclear Price :$" << nuclearPrice << endl;
    }
    bool viewCustomer(string C_id){
        for(auto const &province : provinces){
            auto it = province.customers.find(C_id);
            if(it != province.customers.end()){
                it->second.printInfo();
                return true;
            }
        }
        return false;
    }
    EnergyProvider &viewCustomersByProvince(string P_id){
        for(auto const &province : provinces){
            if(province.P_id == P_id){
                for(auto const &customer : province.customers){
                    customer.second.printInfo();
                }
                break;
            }
        }
        return (*this);
    }
    bool hasCustomer(string customerID){
        for(auto &province : provinces){
            if(province.customers.find(customerID) != province.customers.end()){
                return true;
            }
        }
        return false;
    }
    void addNewCustomer(string C_id, string C_name, string C_address, string C_phone, string C_R_id){
        for(auto &province : provinces){
            if(province.P_id == C_R_id){
                province.customers.insert({C_id, Customer(C_id, C_name, C_address, C_phone, C_R_id)});
                break;
            }
        }
        // add to SQL database here
    }
    bool removeCustomer(string C_id){
        for(auto &province : provinces){
            if(province.customers.find(C_id) != province.customers.end()){
                province.customers.erase(C_id);
                return true;
            }
        }
        // remove from SQL database here
        return false;
    }
    // REFACTOR
    bool editOilPrice(double newOilPrice){
        return newOilPrice > 0 ? (oilPrice = newOilPrice, true) : (cout << "price cannot be less than or equal to 0", false);
    }
    bool editSolarPrice(double newSolarPrice){
        return newSolarPrice > 0 ? (solarPrice = newSolarPrice, true) : (cout << "price cannot be less than or equal to 0", false);
    }
    bool editNuclearPrice(double newNuclearPrice){
        return nuclearPrice > 0 ? (nuclearPrice = newNuclearPrice, true) : (cout << "price cannot be less than or equal to 0", false);
    }
    void updateFile(){
        ofstream outFile;
        outFile.open("customers.output");
        if(!outFile){
            cerr << "Error opening output file..." << endl;
            return;
        }
        for(auto &province : provinces){
            for(auto &customer : province.customers){
                outFile << customer.second.C_id << "," << customer.second.C_name << "," << customer.second.C_address << "," << customer.second.C_phone << "," << customer.second.C_R_id << endl;
            }
        }
        /*
        This update occurs right before exit and creates output 
        of final customer information for the last run of the program.
        No need to do anything in database, because the database is updated as the program runs.
        */
        outFile.close();
    }
    void readFile(){
        /*
            Read file contents into database
            Append to previous database instance or overwrite it everytime is up to you
        */
        string filename;
        getField(filename, fileName, filenamePrompt());
        ifstream inFile(filename);
        if(inFile.is_open()){
        string line;
        vector<string> tokens;
        string token;
        while(getline(inFile, line)){
            stringstream ss(line);
            while(getline(ss, token, ',')){
                tokens.push_back(token);
            }
            if(tokens.size() == 5){
                addNewCustomer(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
            } else {
                cerr << "Error reading line! (Invalid number of tokens parsed...)" << endl;
            }
            tokens.clear();
        }
        } else {
            cerr << "Error opening file..." << endl;
        }
        inFile.close();
    }
    bool createOrder(string O_id, string O_C_id, string O_oilCount, string O_solarCount, string O_nuclearCost){
        for(auto &province : provinces){
            if(province.customers.find(O_C_id) != province.customers.end()){
                province.customers[O_C_id].createOrder(O_id, O_C_id, O_oilCount, O_solarCount, O_nuclearCost);
                return true;
            }
        }
        // Update in SQL database
        return false;
    }
    bool editOrder(string customerID){
        for(auto &province : provinces){
            if(province.customers.find(customerID) != province.customers.end()){
                province.customers[customerID].editOrder();
                return true;
            }
        }
        // Update in SQL database
        return false;
    }
    bool editCustomerInfo(string customerID){
        for(auto &province : provinces){
            if(province.customers.find(customerID) != province.customers.end()){
                province.customers[customerID].editCustomerInfo();
                return true;
            }
        }
        // Update in SQL database
        return false;
    }
    // Need to finish...
    void checkoutOrder(string customerID){
        if(!hasCustomer(customerID)){
            cout << "Could not find Customer ID or Province ID" << endl;
            return;
        }
        
    }
    void printBill(string customerID){
        for(auto &province : provinces){
           if(province.customers.find(customerID) != province.customers.end()){
            province.customers[customerID].bill.billPrinter();
            break;
           }
        }
    }
    vector<Province> provinces;
};

#endif