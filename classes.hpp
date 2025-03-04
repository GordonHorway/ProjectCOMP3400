#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <initializer_list>
#include <fstream>
#include <sstream>

using namespace std;

constexpr int num_regions = 5;
constexpr int num_customers = 100;
constexpr int num_energy_types = 3;

class Bill {
    public:
    string B_id;            // (Primary Key)
    string B_C_id;          // (Foreign Key) (CUSTOMER)
    string B_issueDate;
    string B_dueDate;      // (Calculated field -> Issue Date)
    string B_overdue;
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
        string B_overdue,
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
        cout << B_dueDate << endl << B_overdue << endl << B_balance << endl;
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
};

class Region {
    public:
    string R_id;
    string R_name;
    Region() = default;
    Region(string R_id, string R_name){
        this->R_id = R_id;
        this->R_name = R_name;
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
        regions.reserve(num_regions);
        for(auto const &pair : list){
            Region region(pair.first, pair.second);
            regions.push_back(region);
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
        cout << "Oil Price :     $" << oilPrice << endl;
        cout << "Solar Price :   $" << solarPrice << endl;
        cout << "Nuclear Price : $" << nuclearPrice << endl;
    }
    EnergyProvider &viewCustomer(string C_id){
        for(auto const &region : regions){
            auto it = region.customers.find(C_id);
            if(it != region.customers.end()){
                it->second.printInfo();
            }
        }
        return (*this);
    }
    EnergyProvider &viewCustomersByProvince(string R_id){
        for(auto const &region : regions){
            if(region.R_id == R_id){
                for(auto const &customer : region.customers){
                    customer.second.printInfo();
                }
                break;
            }
        }
        return (*this);
    }
    EnergyProvider &addNewCustomer(string C_id, string C_name, string C_address, string C_phone, string C_R_id){
        for(auto &region : regions){
            if(region.R_id == C_R_id){
                region.customers.insert({C_id, Customer(C_id, C_name, C_address, C_phone, C_R_id)});
                break;
            }
        }
        return (*this);
    }
    EnergyProvider &removeCustomer(string C_id){
        for(auto &region : regions){
            if(region.customers.find(C_id) != region.customers.end()){
                region.customers.erase(C_id);
                break;
            }
        }
        return (*this);
    }
    bool editOilPrice(double newOilPrice){
        return newOilPrice > 0 ? (oilPrice = newOilPrice, true) : (cout << "price cannot be less than or equal to 0", false);
    }
    bool editSolarPrice(double newSolarPrice){
        return newSolarPrice > 0 ? (solarPrice = newSolarPrice, true) : (cout << "price cannot be less than or equal to 0", false);
    }
    bool editNuclearPrice(double newNuclearPrice){
        return nuclearPrice > 0 ? (nuclearPrice = newNuclearPrice, true) : (cout << "price cannot be less than or equal to 0", false);
    }
    void readFile(){
        cout << "Enter name of file in current working directory : ";
        string filename;
        cin >> filename;
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
    vector<Region> regions;
};

#endif