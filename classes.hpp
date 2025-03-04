#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Customer {
    public:
    string C_id;
    string C_name;
    string C_address;
    string C_phone;
    string C_R_id;
    Customer() = default;
    Customer(string C_id, string C_name, string C_address, string C_phone, string C_R_id){
        this->C_id = C_id;
        this->C_name = C_name;
        this->C_address = C_address;
        this->C_phone = C_phone;
        this->C_R_id = C_R_id;
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
    // using map instead of vector because lookup is way faster
    unordered_map<string, Customer> customers;
};

class EnergyProvider {
    string E_id; // do we really need unique id if we are going to have just one Energy Provider object?
    string E_name;
    EnergyProvider(string E_id, string E_name){
        this->E_id = E_id;
        this->E_name = E_name;
    }
    // only 5 elements therefore we dont need fancy data structure for lookup
    vector<Region> regions;
};

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

#endif