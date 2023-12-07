#ifndef MAINSOLUTION_ADDITIONALFUNCTIONS_H
#define MAINSOLUTION_ADDITIONALFUNCTIONS_H
#include <iostream>

using namespace std;
int getNum(){
    int number ;
    while (true){
        cin >> number;

        if (cin.fail() || number <= 0){
            cin.clear();
            cin.ignore(512, '\n');
            cout << "Only numerical values accepted. And number should be positive\n";
        }
        else {
            break;
        }
    }
    return number;
}
void menu(){
    cout << "1. Find enemy \n";
    cout << "2. Show achievements \n";
    cout << "3. Show treasures \n";
    cout << "4. Show info about player \n";
    cout << "5. Quit \n";
}
int makeRandom(int min, int max){
    return (rand() % (max - min + 1)) + min;
}
#endif
