#include <iostream>
#include <cstdio>
#include <ctime>
#include "classes.hpp"
#include "library.hpp"
#include <list>
#include <unordered_map>
#include <fstream>
#include <sstream>

void addREGION(std::unordered_map<int, std::string> &REGIONS, const std::string &R_id, const std::string &R_name) {
    // Convert R_id to an integer
    int regionId = std::stoi(R_id);

    // Add the region to the unordered map
    REGIONS[regionId] = R_name;

    // Print confirmation
    std::cout << "Region with ID " << regionId << " and name \"" << R_name << "\" has been added successfully." << std::endl;
}

void addCUSTOMER(std::unordered_map<std::string, Customer> &CUSTOMERS, 
    const std::string &C_id, const std::string &C_name, 
    const std::string &C_address, const std::string &C_phone, 
    const std::string &C_R_id) {

    // Create a new Customer object
    Customer newCustomer;
    newCustomer.C_id = C_id;
    newCustomer.C_name = C_name;
    newCustomer.C_address = C_address;
    newCustomer.C_phone = C_phone;
    newCustomer.C_R_id = C_R_id;

    // Add the new Customer object to the unordered map
    CUSTOMERS[C_id] = newCustomer;

    // Print confirmation
    std::cout << "Customer with ID " << C_id << " has been added successfully." << std::endl;
}

void addBILL(std::unordered_map<std::string, Bill> &BILLS, 
             const std::string &B_id, const std::string &B_C_id, 
             const std::string &B_issueDate, const std::string &B_dueDate, 
             bool B_overdue, double B_balance, double B_amtPaid, 
             double B_oilCount, double B_solarCount, double B_nuclearCount, 
             double B_oilCost, double B_solarCost, double B_nuclearCost) {
    
                // Create a new Bill object
    Bill newBill;
    newBill.B_id = B_id;
    newBill.B_C_id = B_C_id;
    newBill.B_issueDate = B_issueDate;
    newBill.B_dueDate = B_dueDate;
    newBill.B_overdue = B_overdue;
    newBill.B_balance = B_balance;
    newBill.B_amtPaid = B_amtPaid;
    newBill.B_oilCount = B_oilCount;
    newBill.B_solarCount = B_solarCount;
    newBill.B_nuclearCount = B_nuclearCount;
    newBill.B_oilCost = B_oilCost;
    newBill.B_solarCost = B_solarCost;
    newBill.B_nuclearCost = B_nuclearCost;

    // Add the new Bill object to the unordered map
    BILLS[B_id] = newBill;

    // Print confirmation
    std::cout << "Bill with ID " << B_id << " has been added successfully." << std::endl;
}

int main(int argc, char **argv){

    // this is the map of all data 
    std::unordered_map<int, std::string> REGIONS;
    std::unordered_map<std::string, Customer> CUSTOMERS;
    std::unordered_map<std::string, Bill> BILLS;

    try{
    if(argc != 2){
        throw invalid_argument("invalid number of arguments passed into the CLI!!\n");
    }

    string R_id, R_name;
    string C_id, C_name, C_address, C_phone, C_Pr_id;

    string number_text;

    string O_id;            // (Primary Key)
    string O_C_id;          // (Foreign Key) (CUSTOMER)
    double O_oilCount;
    double O_solarCount;
    double O_nuclearCount;

    bool isCustomer;
    bool isProvince;
    double amtPaid;

    std::ifstream file("info.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open info.csv" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstValue;
        std::getline(ss, firstValue, ',');
    
        int id = std::stoi(firstValue);
    
        if (id >= 1000 && id < 2000) {
            // Process as a REGION
            std::string R_name;
            std::getline(ss, R_name, ',');
            addREGION(REGIONS, firstValue, R_name);
    
            // Print confirmation
            cout << "Added Region: " << endl;
            cout << "ID: " << firstValue << ", Name: " << R_name << endl;
            cout << "---------------------------------" << endl;
    
        } else if (id >= 2000 && id < 3000) {
            // Process as a CUSTOMER
            std::string C_name, C_phone, C_R_id;
            std::getline(ss, C_name, ',');
            std::getline(ss, C_phone, ',');
            std::getline(ss, C_R_id, ',');
            addCUSTOMER(CUSTOMERS, firstValue, C_name, "", C_phone, C_R_id);
    
            // Print confirmation
            cout << "Added Customer: " << endl;
            cout << "ID: " << firstValue << ", Name: " << C_name << endl;
            cout << "Phone: " << C_phone << ", Region ID: " << C_R_id << endl;
            cout << "---------------------------------" << endl;
    
        } else if (id >= 3000 && id < 4000) {
            // Process as a BILL
            std::string B_C_id, B_issueDate, B_dueDate;
            bool B_overdue;
            double B_balance, B_amtPaid, B_oilCount, B_solarCount, B_nuclearCount, B_oilCost, B_solarCost, B_nuclearCost;
    
            std::getline(ss, B_C_id, ',');
            std::getline(ss, B_issueDate, ',');
            std::getline(ss, B_dueDate, ',');
            ss >> B_overdue;
            ss.ignore(1, ',');
            ss >> B_balance;
            ss.ignore(1, ',');
            ss >> B_amtPaid;
            ss.ignore(1, ',');
            ss >> B_oilCount;
            ss.ignore(1, ',');
            ss >> B_solarCount;
            ss.ignore(1, ',');
            ss >> B_nuclearCount;
            ss.ignore(1, ',');
            ss >> B_oilCost;
            ss.ignore(1, ',');
            ss >> B_solarCost;
            ss.ignore(1, ',');
            ss >> B_nuclearCost;
    
            addBILL(BILLS, firstValue, B_C_id, B_issueDate, B_dueDate, B_overdue, B_balance, B_amtPaid, B_oilCount, B_solarCount, B_nuclearCount, B_oilCost, B_solarCost, B_nuclearCost);
    
            // Print confirmation
            cout << "Added Bill: " << endl;
            cout << "ID: " << firstValue << ", Customer ID: " << B_C_id << endl;
            cout << "Issue Date: " << B_issueDate << ", Due Date: " << B_dueDate << endl;
            cout << "Overdue: " << (B_overdue ? "Yes" : "No") << ", Balance: $" << B_balance << endl;
            cout << "Amount Paid: $" << B_amtPaid << endl;
            cout << "Oil Count: " << B_oilCount << ", Solar Count: " << B_solarCount << ", Nuclear Count: " << B_nuclearCount << endl;
            cout << "Oil Cost: $" << B_oilCost << ", Solar Cost: $" << B_solarCost << ", Nuclear Cost: $" << B_nuclearCost << endl;
            cout << "---------------------------------" << endl;
    
        } else {
            std::cerr << "Error: Invalid ID range in line: " << line << std::endl;
        }
    }

    file.close();

    EnergyProvider energyProvider(argv[1], "0111", "LargeCorporation", REGIONS);

    // loop for menu in terminal
    int choice;
    while(true){
        menu();
        cout << "Enter choice : ";
        cin >> choice;
        clear();
        switch(choice){
            case 0:
                energyProvider.readFile();
            break;
            case 11:    // Add New Customer
                getField(C_id, customerID, customerIDPrompt());
                getField(C_Pr_id, provinceID, provinceIDPrompt());
                isCustomer = energyProvider.hasCustomer(C_id);
                if(!isCustomer){
                    getField(C_name, name, namePrompt());
                    getField(C_phone, phoneNumber, phoneNumberPrompt());
                    getField(C_address, address, addressPrompt());
                    // energyProvider.addNewCustomer(C_id, C_name, C_address, C_phone, C_Pr_id); // Old addition method
                    addCUSTOMER(CUSTOMERS, C_id, C_name, C_address, C_phone, C_Pr_id);
                } else {
                    cout << "Customer ID already exists" << endl;
                }
            break;
            case 12:    // Remove Customer
                getField(C_id, customerID, customerIDPrompt());
                isCustomer = energyProvider.removeCustomer(C_id);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;
            case 13:    // View Customer
                getField(C_id, customerID, customerIDPrompt());
            
                // Check if the customer exists in the map
                if (CUSTOMERS.find(C_id) != CUSTOMERS.end()) {
                    // Retrieve the customer
                    const Customer &customer = CUSTOMERS[C_id];
            
                    // Display customer details
                    cout << "Customer Details:" << endl;
                    cout << "ID: " << customer.C_id << endl;
                    cout << "Name: " << customer.C_name << endl;
                    cout << "Address: " << customer.C_address << endl;
                    cout << "Phone: " << customer.C_phone << endl;
                    cout << "Region ID: " << customer.C_R_id << endl;
                } else {
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;
            case 14:    // Edit Customer
                getField(C_id, customerID, customerIDPrompt());
            
                // Check if the customer exists in the map
                if (CUSTOMERS.find(C_id) != CUSTOMERS.end()) {
                    // Retrieve the customer
                    Customer &customer = CUSTOMERS[C_id];
            
                    // Print current customer details
                    cout << "Current Customer Details:" << endl;
                    cout << "ID: " << customer.C_id << endl;
                    cout << "Name: " << customer.C_name << endl;
                    cout << "Address: " << customer.C_address << endl;
                    cout << "Phone: " << customer.C_phone << endl;
                    cout << "Region ID: " << customer.C_R_id << endl;
            
                    // Prompt for updated information
                    cout << "\nEnter updated information for this customer:" << endl;
                    getField(customer.C_name, name, "Enter new name: ");
                    getField(customer.C_address, address, "Enter new address: ");
                    getField(customer.C_phone, phoneNumber, "Enter new phone number: ");
                    getField(customer.C_R_id, provinceID, "Enter new region ID: ");
            
                    // Confirmation message
                    cout << "Customer information updated successfully!" << endl;
                } else {
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;    

            case 15:    // View Customers by Province
                getField(R_id, provinceID, provinceIDPrompt());
            
                // Check if the province exists in the REGIONS map
                if (REGIONS.find(std::stoi(R_id)) != REGIONS.end()) {
                    cout << "Customers in Province: " << REGIONS[std::stoi(R_id)] << endl;
            
                    // Iterate through the CUSTOMERS map and find customers in the specified province
                    bool found = false;
                    for (const auto &entry : CUSTOMERS) {
                        const Customer &customer = entry.second;
                        if (customer.C_R_id == R_id) {
                            found = true;
                            cout << "---------------------------------" << endl;
                            cout << "Customer Details:" << endl;
                            cout << "ID: " << customer.C_id << endl;
                            cout << "Name: " << customer.C_name << endl;
                            cout << "Address: " << customer.C_address << endl;
                            cout << "Phone: " << customer.C_phone << endl;
                            cout << "Region ID: " << customer.C_R_id << endl;
                        }
                    }
            
                    if (!found) {
                        cout << "No customers found in this province." << endl;
                    }
                } else {
                    cout << "Could not find province associated with this Province ID" << endl;
                }
            break;

            case 21:    // Display All Prices
                cout << "|Energy Prices|" << endl;
                energyProvider.displayAllPrices();
            break;

            case 22:    // Edit Oil Price
                getField(number_text, number, "Enter new oil price : ");
                energyProvider.editOilPrice(stod(number_text));
            break;

            case 23:    // Edit Solar Price
                getField(number_text, number, "Enter new solar price : ");
                energyProvider.editSolarPrice(stod(number_text));
            break;

            case 24:    // Edit Nuclear Price
                getField(number_text, number, "Enter new nuclear price : ");
                energyProvider.editNuclearPrice(stod(number_text));
            break;

            case 31:    // Create Order
                getField(O_id, orderID, orderIDPrompt());
                getField(O_C_id, customerID, customerIDPrompt());
                getField(number_text, number, "Enter Oil Count : ");
                O_oilCount = stod(number_text);
                getField(number_text, number, "Enter Solar Count : ");
                O_solarCount = stod(number_text);
                getField(number_text, number, "Enter Nuclear Count : ");
                O_nuclearCount = stod(number_text);
                isCustomer = energyProvider.createOrder(O_id, O_C_id, O_oilCount, O_solarCount, O_nuclearCount);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                } else {
                    cout << "Order Success!" << endl;
                }
            break;
            case 32:    // Edit Order
                getField(C_id, customerID, customerIDPrompt());
                isCustomer = energyProvider.editOrder(C_id);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;

            case 41:    // View Bills
                getField(C_id, customerID, customerIDPrompt());
                isCustomer = energyProvider.hasCustomer(C_id);
                if(isCustomer){
                    energyProvider.printBill(C_id);
                } else {
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;

            case 42:    // Pay Bills
                getField(C_id, customerID, customerIDPrompt());
                getField(number_text, number, "Enter amount to pay : ");
                amtPaid = stod(number_text);
                energyProvider.payBill(C_id, amtPaid);
            break;

            case 43:    // Check Unpaid Bills
                cout << "To be done in SQL" << endl;
            break;

            case 44:    // Check Overdue Bills
                cout << "To be done in SQL" << endl;
            break;

            case 45:    // View Customers with Unpaid Bills
                cout << "To be done in SQL" << endl;
            break;
            
            case 46:    // View Customers with Overdue Bills
                cout << "To be done in SQL" << endl;
            break;
            
            case 5:    // Exit
                energyProvider.updateFile();
                cout << "Goodbye!" << endl;
                exit(EXIT_SUCCESS);
            break;
            default:
                cout << "Not a valid choice!" << endl;
        }
    }
    }catch(invalid_argument &e){
        cerr << e.what();
    }

    return 0;
}