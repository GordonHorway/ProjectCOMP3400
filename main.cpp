#include <iostream>
#include <cstdio>
#include <ctime>
#include "classes.hpp"
#include "library.hpp"
#include <list>
#include <sqlite3.h>
#include "sql_queries.h"

sqlite3 *setupDB();

int callbackPrint(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    (void) NotUsed; // This is here just to suppress a warning from the compiler
    return 0;
}

int main(int argc, char **argv){

    sqlite3 *db = setupDB();
    if(!db){
        cerr << "There was an issue setting up the database!" << endl;
        return 1;
    }

    cout << "Our database is ready to use!" << endl;

    char* errMsg = 0;

    sqlite3_exec(db, sql, callbackPrint, 0, &errMsg);

    cout << "(A test of a sql query to print out the contents of the region table)" << endl;

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

    // I'll try to have it so that the Region ID and Names are not hard coded
    EnergyProvider energyProvider(argv[1], "0111", "LargeCorporation", {{"1001", "Ontario"}, {"1002", "Quebec"}, {"1003", "Alberta"}, {"1004", "Manitoba"}, {"1005", "Saskatchewan"}});

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
                    energyProvider.addNewCustomer(C_id, C_name, C_address, C_phone, C_Pr_id);
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
                isCustomer = energyProvider.viewCustomer(C_id);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;

            case 14:    // Edit Customer
                getField(C_id, customerID, customerIDPrompt());
                if(!(isCustomer = energyProvider.editCustomerInfo(C_id))){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;
            case 15: 
               // View Customers by Province
                getField(R_id, provinceID, provinceIDPrompt());
                isProvince = energyProvider.viewCustomersByProvince(R_id);
                if(!isProvince){
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
                sqlite3_exec(db, unpaidBillCheck, callbackPrint, 0, &errMsg);
            break;

            case 44:    // Check Overdue Bills
                sqlite3_exec(db, overdueQuery, callbackPrint, 0, &errMsg);
            break;

            case 45:    // View Customers with Unpaid Bills
                sqlite3_exec(db, unpaidBillView, callbackPrint, 0, &errMsg);
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

    sqlite3_close(db);

    return 0;
}

sqlite3 *setupDB(){
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if(rc != SQLITE_OK){
        fprintf(stderr, "cannot open database %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}