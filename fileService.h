#ifndef MAINSOLUTION_FILESERVICE_H
#define MAINSOLUTION_FILESERVICE_H

#include <iostream>
#include<algorithm>
#include "exceptions.h"
#include "classes.h"
#include "additionalFunctions.h"

using namespace std;

int TOTAL_COUNT = 0;

void makeCheck(Customer *customer) {
    fstream file;
    file.open("storeBusket.dat", ios::binary | ios::app | ios::in);
    ofs.open("result.txt", ios::app);
    AbstractToy *abstractToy;
    if(!customer->getWhatToBy().empty()) {
        if (ofs.is_open()) {
            ofs.setf(ios::right);
            ofs.width(40);
            ofs << " Info about purchases : " << endl;
            ofs.unsetf(ios::left);
        }
        file.seekg(sizeof(abstractToy) * TOTAL_COUNT);
        file.read(reinterpret_cast<char *>(&abstractToy), sizeof(abstractToy));
        int counter = 0;
        ofs << customer->getName() << " bought : " << endl;
        while (!file.eof()) {
            ofs << counter++ << ". " << abstractToy->getName() << " for " << abstractToy->getCost() << "$" << endl;
            file.read(reinterpret_cast<char *>(&abstractToy), sizeof(abstractToy));
        }
        ofs << "total sum of purchase : " << customer->countSumOfBuying() << "$" << endl;
        ofs << "customer gave : " << customer->getCountOfMoney() << "$" << endl;
        ofs << "change : " << customer->getCountOfMoney() - customer->countSumOfBuying() << "$" << endl;
        customer->setCountOfMoney(customer->getCountOfMoney() - customer->countSumOfBuying());
        if(customer->getWhatToBy().size() != 0) {
           TOTAL_COUNT += customer->getWhatToBy().size();
        }
        customer->getWhatToBy().clear();
        ofs.close();
    }
    file.close();
}

void showInfoFromFile() {
    infile.open("result.txt");
    const int MAX = 80;
    char buffer[MAX];
    if (infile.is_open()) {
        while (!infile.eof()) {
            infile.getline(buffer, MAX);
            cout << buffer << endl;
        }
    }
    infile.close();
}
void getParticularToy(){
    AbstractToy* toy;
    ifstream infile;
    infile.open("storeBusket.dat", ios::in | ios::binary);
    infile.seekg(0, ios::end);
    int endposition = infile.tellg();
    int size = endposition / sizeof(toy);
    if(size != -1) {
        cout << "Were found " << size << " toys" << endl;
        cout << "Write number of toy : " << endl;
        int index = -1;
        while (index < 0 || index > size) {
            cout << "Write index from 1 to " << size << endl;
            index = getNum();
        }
        int position = (index - 1) * sizeof(toy);
        infile.seekg(position);
        infile.read(reinterpret_cast<char *>(&toy), sizeof(toy));
        toy->description();
        cout << endl;
    } else {
        cout << "No toys detected ! " << endl;
    }
    infile.close();
}
void showAllSoldToys(){
    fstream file;
    file.open("storeBusket.dat", ios::binary | ios::app | ios::in);
    AbstractToy *abstractToy;
        file.seekg(0);
        file.read(reinterpret_cast<char *>(&abstractToy), sizeof(abstractToy));
        int counter = 0;
        while (!file.eof()) {
            cout << counter++ << ". " << abstractToy->getName() << " for " << abstractToy->getCost() << "$" << endl;
            file.read(reinterpret_cast<char *>(&abstractToy), sizeof(abstractToy));
        }
    file.close();
}
void sortAll(){
    fstream file;
    vector<AbstractToy*> result;
    file.open("storeBusket.dat", ios::binary | ios::app | ios::in);
    AbstractToy *abstractToy;
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&abstractToy), sizeof(abstractToy));
    while (!file.eof()) {
        result.push_back(abstractToy);
        file.read(reinterpret_cast<char *>(&abstractToy), sizeof(abstractToy));
    }
    sort(result.begin(), result.end(), [](AbstractToy *first, AbstractToy *second){
        return (first->getCost() < second->getCost());
    });
    file.close();
    file.open("storeBusket.dat", ios::binary | ios::out);
    for (auto toy: result) {
        file.write(reinterpret_cast<char *>(&toy), sizeof(toy));
    }
    file.close();
}
#endif
