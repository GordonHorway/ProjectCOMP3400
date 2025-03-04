#include <iostream>
#include "classes.hpp"
#include "library.hpp"

int main(){

    EnergyProvider energyProvider("0111", "LargeCorporation", {{"1000", "Ontario"}, {"1001", "Quebec"}, {"1002", "Alberta"}, {"1003", "Manitoba"}, {"1004", "Saskatchewan"}});

    // loop for menu in terminal
    while(true){
        int choice;
        cout << "Enter choice : ";
        cin >> choice;
        clear();
        menu();
        // will add stuff to cases later
        switch(choice){
            case 1:
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