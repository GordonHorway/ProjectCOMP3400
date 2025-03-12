#include <iostream>
#include <cstdio>
#include <ctime>
#include "classes.hpp"
#include "library.hpp"

int main(int argc, char **argv){

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

    EnergyProvider energyProvider(argv[1], "0111", "LargeCorporation", {{"1000", "Ontario"}, {"1001", "Quebec"}, {"1002", "Alberta"}, {"1003", "Manitoba"}, {"1004", "Saskatchewan"}});

    cout << "Ontario Province ID : 1000\nQuebec Province ID : 1001\nAlberta Province ID : 1002\nManitoba Province ID : 1003\nSaskatchewan Province ID : 1004\n";

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
            case 11:
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
            case 12:
                getField(C_id, customerID, customerIDPrompt());
                isCustomer = energyProvider.removeCustomer(C_id);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;
            case 13:
                getField(C_id, customerID, customerIDPrompt());
                isCustomer = energyProvider.viewCustomer(C_id);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;
            case 14:
                getField(C_id, customerID, customerIDPrompt());
                energyProvider.editCustomerInfo(C_id);
            break;
            case 15:
                getField(R_id, provinceID, provinceIDPrompt());
                isProvince = energyProvider.viewCustomersByProvince(R_id);
                if(!isProvince){
                    cout << "Could not find province associated with this Province ID" << endl;
                }
            break;
            case 21:
                cout << "|Energy Prices|" << endl;
                energyProvider.displayAllPrices();
            break;
            case 22:
                getField(number_text, number, "Enter new oil price : ");
                energyProvider.editOilPrice(stod(number_text));
            break;
            case 23:
                getField(number_text, number, "Enter new solar price : ");
                energyProvider.editSolarPrice(stod(number_text));
            break;
            case 24:
                getField(number_text, number, "Enter new nuclear price : ");
                energyProvider.editNuclearPrice(stod(number_text));
            break;
            case 31:
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
            case 32:
                getField(C_id, customerID, customerIDPrompt());
                isCustomer = energyProvider.editOrder(C_id);
                if(!isCustomer){
                    cout << "Could not find customer associated with this Customer ID" << endl;
                }
            break;
            case 4:
                case 41:
                    getField(C_id, customerID, customerIDPrompt());
                    isCustomer = energyProvider.hasCustomer(C_id);
                    if(isCustomer){
                        energyProvider.printBill(C_id);
                    } else {
                        cout << "Could not find customer associated with this Customer ID" << endl;
                    }
                break;
                case 42:
                    getField(C_id, customerID, customerIDPrompt());
                    getField(number_text, number, "Enter amount to pay : ");
                    amtPaid = stod(number_text);
                    energyProvider.payBill(C_id, amtPaid);
                break;
                case 43:
                    cout << "To be done in SQL" << endl;
                break;
                case 44:
                    cout << "To be done in SQL" << endl;
                break;
                case 45:
                    cout << "To be done in SQL" << endl;
                break;
                case 46:
                    cout << "To be done in SQL" << endl;
                break;
            break;
            case 5:
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