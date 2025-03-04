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
                // read from file into data structures
                energyProvider.readFile();
            break;
            case 1:
                case 11:

                break;
                case 12:

                break;
                case 13:
                    getField(C_id, customerID);
                    energyProvider.viewCustomer(C_id);
                break;
                case 14:

                break;
            break;
            case 2:
                case 21:

                break;
                case 22:

                break;
                case 23:

                break;
                case 24:
                    
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