#ifndef MAINSOLUTION_ADDITIONALFUNCTIONS_H
#define MAINSOLUTION_ADDITIONALFUNCTIONS_H
#include <iostream>
#include <fstream>
ofstream ofs;
ifstream infile;
using namespace std;
int getNum(){
    int number ;
    while (true){
        cin >> number;

        if (cin.fail()){
            cin.clear();
            cin.ignore(512, '\n');
            cout << "Only numerical values accepted.\n";
        }
        else {
            break;
        }
    }
    return number;
}
void menu() {
    cout << "1. Show all toys\n";
    cout << "2. Make buy\n";
    cout << "3. Show my storage\n";
    cout << "4. Accept purchase \n";
    cout << "5. Show history of purchase\n";
    cout << "6. Get particular toy\n";
    cout << "7. Get all sold toys\n";
    cout << "8. Sort all \n";
    cout << "9. Quit\n";
}
#endif //MAINSOLUTION_ADDITIONALFUNCTIONS_H
