#include <iostream>
#include "classes.hpp"
#include "library.hpp"


int main(){

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