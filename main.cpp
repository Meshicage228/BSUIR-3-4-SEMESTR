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
    AbstractToy(const string &name, float cost) : name(name), cost(cost) {
        if (cost < 0) {
            throw NegativeNumberException("Negative number was used while creation object!");
        }
    }

    virtual void description() {

    };

    string &getName(){
        return name;
    }

    float getCost(){
        return cost;
    }

};

class CarToy : public AbstractToy {
public:
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
        cout << "0. Car" << endl;
        cout << "1. Doll" << endl;
        cout << "Write index of product : " << endl;
        index = getNum();
        try{
            customer->getWhatToBy().push_back(arrToys.at(index));
        } catch (std::out_of_range &ex){
            cout << "Out of range!" << endl;
            throw;
        }
    }

    void acceptBying() {
        if (!customer->getWhatToBy().empty()) {
            if (customer->getCountOfMoney() - customer->countSumOfBuying() < 0) {
                customer->getWhatToBy().clear();
                throw NotEnogthMoneyException("Not enough money for purchase");
            } else {
                customer->setCountOfMoney(customer->getCountOfMoney() - customer->countSumOfBuying());
                customer->getWhatToBy().clear();
            }
        } else {
            cout << "Nothing to buy !" << endl;
        }
    }

    Customer *getCustomer(){
        return customer;
    }
};
void mainApp(Store store) {
    int option;
    do {
        menu();
        option = getNum();
        switch (option) {
            case 1: {
                store.showAll();
                break;
            }
            case 2: {
                try {
                    store.makeBuy();
                } catch (std::out_of_range &ex) {
                    cout << "Incorrect index! Try again" << endl;
                }
                break;
            }
            case 3 : {
                try{
                    store.getCustomer()->showMyBusket();
                } catch (EmptyBusketException & ex){
                    cout << ex.what() << endl;
                }
                break;
            }
            case 4 : {
                try {
                    store.acceptBying();
                } catch (NotEnogthMoneyException &ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            case 5 : {
                cout << "End of progtramm..." << endl;
            }
            default: {
                cout << "Wrong option, try again!\n";
            }
        }
    } while (option != 5);
}
void termFunc() {
    cout << "Something went wrong! Ending app..." << endl;
    exit(-1);
}

int main() {
    try {
        set_terminate(termFunc);
        vector<AbstractToy *> abs;
        Customer customer("Vlad", 300, abs);
        CarToy carToy("Car", 100.50);
        DollToy doll("DollToy", 176.52);
        vector<AbstractToy *> arrToys = {&carToy, &doll};
        WhareHouse whareHouse(arrToys);
        Store store(arrToys, &customer);
        mainApp(store);
    }
    catch (NegativeNumberException &ex) {
        cout << ex.what() << endl;
        throw;
    }
}
