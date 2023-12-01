#include <iostream>
#include <vector>
#include <fstream>
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

    string &getName(){
        return name;
    }

    float getCost(){
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
void saveInformation(Customer* customer){
    ofs.open("result.txt", ios::app);
    if (ofs.is_open()) {
        ofs.setf(ios::right);
        ofs.width(40);
        ofs << " Info about purchases : " << endl;
        ofs.unsetf(ios::left);
    }
    auto toys = customer->getWhatToBy();
    ofs << customer->getName() << " bought : " << endl;
    for(int i = 0 ; i < toys.size(); i++){
        ofs << i << ". " <<  toys.at(i)->getName() << " for " << toys.at(i)->getCost() << "$" << endl;
    }
    ofs << "total sum of purchase : " << customer->countSumOfBuying() << "$" << endl;
    ofs << "customer gave : " << customer->getCountOfMoney() << "$" << endl;
    ofs << "change : " << customer->getCountOfMoney() - customer->countSumOfBuying() << "$" << endl;
    ofs.close();
}
void showInfoFromFile(){
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
/*void smth(){
    AbstractToy abstractToy;
    ifstream infile;//создать входной файл
    infile.open("result.txt", ios::in | ios::binary);
    infile.seekg(0, ios::end);//установить указатель на 0 байт от конца файла
    int endposition = infile.tellg();//найти позицию в файле
    int n = endposition / sizeof(customer);//число человек
    cout << "\nIn file " << n << " persons(s)";
    cout << "\nWrite number of person: ";
    cin >> n;
    int position = (n - 1) * sizeof(customer);//умножить размер созданных данных на число персон
    infile.seekg(position);//число байт от начала
    //прочитать одну персону
    infile.read(reinterpret_cast<char*>(&customer), sizeof(customer));//вывести одну персону
    cout << customer.getName();
    cout << endl;
}*/
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
        for(int i = 0; i < arrToys.size(); i++){
            cout << i << ". " << arrToys.at(i)->getName() << " : costs " << arrToys.at(i)->getCost() << endl;
        }
        cout << "Write index of product : " << endl;
        index = getNum();
        try{
            customer->getWhatToBy().push_back(arrToys.at(index));
        } catch (out_of_range &ex){
            cout << "Out of range!" << endl;
            throw;
        }
    }

    void acceptBying() {
        if (!customer->getWhatToBy().empty()) {
            if (customer->getCountOfMoney() < customer->countSumOfBuying()) {
                customer->getWhatToBy().clear();
                throw NotEnogthMoneyException("Not enough money for purchase");
            } else {
                saveInformation(customer);
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
                } catch (out_of_range &ex) {
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
                showInfoFromFile();

                smth();
                break;
            }
            case 6 : {
                cout << "End of program..." << endl;
                break;
            }
            default: {
                cout << "Wrong option, try again!\n";
            }
        }
    } while (option != 6);
}
void termFunc() {
    cout << "Something went wrong! Ending app..." << endl;
    exit(-1);
}
int main() {
    try {
        set_terminate(termFunc);
        vector<AbstractToy *> abs;
        Customer customer("Vlad", 1000, abs);
        CarToy carToy("Car", 100.50);
        DollToy doll("DollToy", 176.52);
        vector<AbstractToy *> arrToys = {&carToy, &doll};
        WhareHouse whareHouse(arrToys);
        Store store(arrToys, &customer);
        mainApp(store);
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        throw;
    }
}
