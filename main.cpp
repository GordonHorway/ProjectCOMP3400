#include <iostream>
#include "classes.hpp"
#include "library.hpp"

int main(int argc, char **argv){

    try{
    if(argc != 2){
        throw invalid_argument("invalid number of arguments passed into the CLI!!\n");
    }

    string R_id, R_name;
    string C_id, C_name, C_address, C_phone, C_R_id;
    string number_text;

    EnergyProvider energyProvider(argv[1], "0111", "LargeCorporation", {{"1000", "Ontario"}, {"1001", "Quebec"}, {"1002", "Alberta"}, {"1003", "Manitoba"}, {"1004", "Saskatchewan"}});

    // loop for menu in terminal
    while(true){
        int choice;
        menu();
        cout << "Enter choice : ";
        cin >> choice;
        clear();
        switch(choice){
            case 0:
                energyProvider.readFile();
            break;
                case 11:
                    getField(C_id, customerID, "Enter Customer ID : ");
                    getField(C_name, name, "Enter Name : ");
                    getField(C_address, address, "Enter Address : ");
                    getField(C_phone, phoneNumber, "Enter Phone Number : ");
                    getField(C_R_id, provinceID, "Enter Province ID : ");
                    energyProvider.addNewCustomer(C_id, C_name, C_address, C_phone, C_R_id);
                break;
                case 12:
                    getField(C_id, customerID, "Enter Customer ID : ");
                    energyProvider.removeCustomer(C_id);
                break;
                case 13:
                    getField(C_id, customerID, "Enter Customer ID : ");
                    energyProvider.viewCustomer(C_id);
                break;
                case 14:
                    getField(R_id, provinceID, "Enter Province ID : ");
                    energyProvider.viewCustomersByProvince(R_id);
                break;
            break;
                case 21:
                    cout << "|Energy Prices|" << endl;
                    energyProvider.displayAllPrices();
                break;
                case 22:
                    getField(number_text, number, "Enter number : ");
                    energyProvider.editOilPrice(stod(number_text));
                break;
                case 23:
                    getField(number_text, number, "Enter number : ");
                    energyProvider.editSolarPrice(stod(number_text));
                break;
                case 24:
                    getField(number_text, number, "Enter number : ");
                    energyProvider.editNuclearPrice(stod(number_text));
                break;
            break;
            case 3:

            break;
            case 4:

            break;
            case 5:
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
}