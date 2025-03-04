#include <iostream>
#include "classes.hpp"
#include "library.hpp"

int main(){

    EnergyProvider energyProvider("0111", "LargeCorporation", {{"1000", "Ontario"}, {"1001", "Quebec"}, {"1002", "Alberta"}, {"1003", "Manitoba"}, {"1004", "Saskatchewan"}});

    // loop for menu in terminal
    while(true){
        int choice;
        menu();
        cout << "Enter choice : ";
        cin >> choice;
        clear();
        switch(choice){
            case 1:
                case 11:
                    
                break;
                case 12:

                break;
                case 13:

                break;
                case 14:

                break;
            break;
            case 2:

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

}