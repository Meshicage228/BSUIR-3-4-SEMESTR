#include <iostream>
#include <vector>

using namespace std;

class IndexOutOfBoundsException : public exception{
private:
    char * message;

public:
    explicit IndexOutOfBoundsException(char *message) : message(message) {}

    char * what () {
        return message;
    }
};

class AbstractToy {
protected:
    string name;
    float cost;
public:
    virtual void description() {

    };
    AbstractToy(const string &name, float cost, int count) : name(name), cost(cost){}

    const string &getName() const {
        return name;
    }

    float getCost() const {
        return cost;
    }

};

class CarToy : public AbstractToy {
public:
    CarToy(const string &name, float cost, int count) : AbstractToy(name, cost, count) {}

    void description() override {
        cout << "This is toy " << name << endl;
        cout << "Its cost : " << cost << endl;
    }
};

class DollToy : public AbstractToy {
public:
    DollToy(const string &name, float cost, int count) : AbstractToy(name, cost, count) {}

    void description() override {
        cout << "This is toy " << name << endl;
        cout << "Its cost : " << cost << endl;
    }
};

class WhareHouse {
protected:
    vector<AbstractToy *> arrToys;
public:
    explicit WhareHouse(const vector<AbstractToy *> &arrToys) : arrToys(arrToys) {}

    void showAllToys() {
        for (int i = 0; i < arrToys.size(); i++) {
            cout << i + 1 << ". ";
            arrToys[i]->description();
        }

    }
};

class Customer {
private:
    string name;
    float countOfMoney;
    vector<AbstractToy *> whatToBy;
public:
    Customer(const string &name, float countOfMoney, const vector<AbstractToy *> &whatToBy) : name(name), countOfMoney(
            countOfMoney), whatToBy(whatToBy) {}

    vector<AbstractToy *> &getWhatToBy(){
        return whatToBy;
    }
    void showStorage(){
        cout << "I want to buy : " << endl;
        if(!whatToBy.empty()) {
            for (auto &toy: whatToBy) {
                cout << toy->getName() << endl;
            }
        } else{
            cout << "Emty storage exception!" << endl;
            cout << "I didnt decide what to buy..." << endl;
        }
        if(countSumOfBuying() != 0){
            cout << "Total pokypka is " << countSumOfBuying() << endl;
        }
        cout << "My money : " << countOfMoney << endl;
    }
    float countSumOfBuying(){
        float totalSum = 0;
        for (auto &toy: whatToBy) {
            totalSum += toy->getCost();
        }
        return totalSum;
    }

    float getCountOfMoney() const {
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
        if(!arrToys.empty()) {
            WhareHouse::showAllToys();
        } else{
            cout << "WhareHouse exception : is empty!" << endl;
        }
    }
    void makeBuy(){
        int index;
        cout << "0. Car" << endl;
        cout << "1. Doll" << endl;
        cout << "Write index of product : " << endl;
        cin >> index;
       if(index >= 0 & index < arrToys.size()) {
               customer->getWhatToBy().push_back(arrToys.at(index));
       } else{
           throw IndexOutOfBoundsException("Index out of bounds exception");
        }
    }
    void acceptBying(){
        if(!customer->getWhatToBy().empty()){
             for(auto & a : customer->getWhatToBy()){
                    if(customer->getCountOfMoney() - a->getCost() < 0){
                        break;
                    }
                    customer->setCountOfMoney(customer->getCountOfMoney() - a->getCost());
                    customer->getWhatToBy().pop_back();
             }
        }else{
            cout << "Nothing to buy !" << endl;
        }
    }
};
void menu(){
    cout << "1. Show all toys" << endl;
    cout << "2. Make buy" << endl;
    cout << "3. Show my storage" << endl;
    cout << "4. Accept purchase " << endl;
    cout << "5. Quit" << endl;
}
int main() {
    vector<AbstractToy*> abs;
    Customer customer ("Vlad", 1250, abs);
    CarToy carToy("Car", 100.50, 23);
    DollToy doll("DollToy", 176.52, 12);
    vector<AbstractToy *> arrToys = {&carToy, &doll};
    Store store(arrToys, &customer);
    int option = 0;
    do {
        menu();
        cin >> option;
        switch (option) {
            case 1: {
                store.showAll();
                break;
            }
            case 2: {
                try {
                    store.makeBuy();
                } catch (IndexOutOfBoundsException& ex){
                    cout << ex.what() << endl;
                }
                break;
            }
            case 3 : {
                customer.showStorage();
                break;
            }
            case 4 : {
                store.acceptBying();
                break;
            }
            case 5 : {
                return 0;
            }
            default: {
                cout << "Wrong option, try again!";
            }
        }
    } while (option != 5);
}
