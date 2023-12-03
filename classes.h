#ifndef MAINSOLUTION_CLASSES_H
#define MAINSOLUTION_CLASSES_H
#include <iostream>
#include <vector>
#include "exceptions.h"
#include "additionalFunctions.h"

using namespace std;

class AbstractToy {
protected:
    string name;
    float cost;
public:
    AbstractToy() {}

    AbstractToy(const string &name, float cost) : name(name), cost(cost) {
        if (cost < 0) {
            throw NegativeNumberException("Negative number was used while creation object!");
        }
    }

    virtual void description() = 0;

    string &getName() {
        return name;
    }

    float getCost() {
        return cost;
    }

};

class CarToy : public AbstractToy {
public:
    CarToy() {}

    CarToy(const string &name, float cost) : AbstractToy(name, cost) {
        if (cost < 0) {
            throw NegativeNumberException("Negative number was used while creation object!");
        }
    }

    void description() override {
        cout << "This is toy " << name << endl;
        cout << "Its cost : " << cost << endl;
    }
};

class DollToy : public AbstractToy {
public:
    DollToy() {}

    DollToy(const string &name, float cost) : AbstractToy(name, cost) {}

    void description() override {
        cout << "This is toy " << name << endl;
        cout << "Its cost : " << cost << endl;
    }
};

class WhareHouse {
protected:
    vector<AbstractToy *> arrToys;
public:
    WhareHouse() {}

    WhareHouse(const vector<AbstractToy *> &arrToys) : arrToys(arrToys) {}

    void showAllToys() {
        for (int i = 0; i < arrToys.size(); i++) {
            cout << i + 1 << ". ";
            arrToys[i]->description();
        }
        cout << endl;
    }
};

class Customer {
private:
    string name;
    float countOfMoney;
    vector<AbstractToy *> busket;
public:
    Customer() {}

    Customer(const string &name, float countOfMoney, const vector<AbstractToy *> &whatToBy) : name(name), countOfMoney(
            countOfMoney), busket(whatToBy) {
        if (countOfMoney < 0) {
            throw NegativeNumberException("Negative number was used while creation object!");
        }
    }

    vector<AbstractToy *> &getWhatToBy() {
        return busket;
    }

    void showMyBusket() {
        if (!busket.empty()) {
            cout << "I want to buy : " << endl;
            for (auto &toy: busket) {
                cout << toy->getName() << endl;
            }
        } else {
            cout << "My money : " << countOfMoney << endl;
            throw EmptyBusketException("You didnt decide what to buy : busket is empty!");
        }
        if (countSumOfBuying() != 0) {
            cout << "Total sum of your purchase is " << countSumOfBuying() << endl;
        }
        cout << "My money : " << countOfMoney << endl;
    }

    float countSumOfBuying() {
        float totalSum = 0;
        for (auto &toy: busket) {
            totalSum += toy->getCost();
        }
        return totalSum;
    }

    float getCountOfMoney() {
        return countOfMoney;
    }

    void setCountOfMoney(float countOfMoney) {
        Customer::countOfMoney = countOfMoney;
    }

    const string &getName() const {
        return name;
    }

};
class Store : WhareHouse {
private:
    Customer *customer;
public:
    Store(const vector<AbstractToy *> &arrToys, Customer *customer) : WhareHouse(arrToys), customer(customer) {}

    void showAll() {
        if (!arrToys.empty()) {
            WhareHouse::showAllToys();
        } else {
            throw EmptyWhareHouseException("Empty store!!!Nothing to buy yet");
        }
    }

    void makeBuy() {
        int index;
        for (int i = 0; i < arrToys.size(); i++) {
            cout << i << ". " << arrToys.at(i)->getName() << " : costs " << arrToys.at(i)->getCost() << endl;
        }
        cout << "Write index of product : " << endl;
        index = getNum();
        try {
            customer->getWhatToBy().push_back(arrToys.at(index));
        } catch (out_of_range &ex) {
            cout << "Out of range!" << endl;
            throw;
        }
    }
    void saveToFile(vector<AbstractToy *> busket) {
        fstream file;
        file.open("storeBusket.dat", ios::binary | ios::app | ios::out);
        for (auto toy: busket) {
            file.write(reinterpret_cast<char *>(&toy), sizeof(&toy));
        }
        file.close();
    }

    void acceptBying() {
        if (!customer->getWhatToBy().empty()) {
            if (customer->getCountOfMoney() < customer->countSumOfBuying()) {
                customer->getWhatToBy().clear();
                throw NotEnogthMoneyException("Not enough money for purchase");
            } else {
                saveToFile(customer->getWhatToBy());
            }
        } else {
            cout << "Nothing to buy !" << endl;
        }
    }

    Customer *getCustomer() {
        return customer;
    }
};
#endif
