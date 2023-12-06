//
// Created by HUAWEI on 06.12.2023.
//

#ifndef MAINSOLUTION_ADDITIONALFUNCTIONS_H
#define MAINSOLUTION_ADDITIONALFUNCTIONS_H
#include <iostream>

using namespace std;
void menu(){
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
}
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
#endif //MAINSOLUTION_ADDITIONALFUNCTIONS_H
