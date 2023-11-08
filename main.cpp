#include <iostream>
#include <vector>

using namespace std;
class AbstractToy{
protected:
    string name;
    float cost;
    int count;
public:
    virtual void description() {

    };
    AbstractToy(const string &name, float cost, int count) : name(name), cost(cost), count(count) {}
};

class CarToy : public AbstractToy{
public:
    CarToy(const string &name, float cost, int count) : AbstractToy(name, cost, count) {}

    void description() override {
        cout << "This is toy " << name << endl;
        cout << "Its cost : " << cost << endl;
        cout << "Count : " << count << endl;
    }
};
class DollToy : public AbstractToy{
public:
    DollToy(const string &name, float cost, int count) : AbstractToy(name, cost, count) {}

    void description() override {
        cout << "This is toy " << name << endl;
        cout << "Its cost : " << cost << endl;
        cout << "Count : " << count << endl;
    }
};
class WhareHouse{
protected:
    vector<AbstractToy*> arrToys;
public:
    explicit WhareHouse(const vector<AbstractToy *> &arrToys) : arrToys(arrToys) {}

    void showAllToys(){
            for (int i = 0; i < arrToys.size(); i++) {
                cout << i + 1 << ". ";
                arrToys[i]->description();
            }

    }
};
class Customer{
private:
    string name;
    float countOfMoney;
    vector<AbstractToy> whatToBy;
public:
    Customer(string name, float countOfMoney) : name(name), countOfMoney(countOfMoney) {}

    vector<AbstractToy> getWhatToBy(){
        return whatToBy;
    }

    void setCountOfMoney(float countOfMoney) {
        Customer::countOfMoney = countOfMoney;
    }

};
class Store : WhareHouse{
private:
    Customer customer;
public:
    Store(const vector<AbstractToy *> &arrToys, const Customer &customer) : WhareHouse(arrToys), customer(customer) {}

    void makeBuy(){
        WhareHouse::showAllToys();
    }
};
bool checkCharacter(char letter){
    for(char a = '1'; a < '10'; a++){
        if(letter != a){
            return false;
        }
    }
    return true;

}
int main() {
    Customer customer("Vlad", 1250);
    CarToy carToy("Car", 100.50, 23);
    DollToy doll("DollToy", 176.52, 12);
    vector<AbstractToy*> arrToys;
    arrToys.push_back(&carToy);
    arrToys.push_back(&doll);
    Store store(arrToys, customer);
    store.makeBuy();
    char option = ' ';
    do{
        switch (option) {
            case '1':{
                break;
            }
            case '2':{
                break;
            }
            default:{
                cout << "Wrong option, try again!";
            }
        }
    } while ()
    return 0;
}
