#include <iostream>
#include <vector>
#include "exceptions.h"
#include "additionalFunctions.h"
#include "fileService.h"
#include "classes.h"
using namespace std;

void mainApp(Store *store) {
    int option;
    do {
        menu();
        option = getNum();
        switch (option) {
            case 1: {
                store->showAll();
                break;
            }
            case 2: {
                try {
                    store->makeBuy();
                } catch (out_of_range &ex) {
                    cout << "Incorrect index! Try again" << endl;
                }
                break;
            }
            case 3 : {
                try {
                    store->getCustomer()->showMyBusket();
                } catch (EmptyBusketException &ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            case 4 : {
                try {
                    store->acceptBying();
                } catch (NotEnogthMoneyException &ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            case 5 : {
                makeCheck(store->getCustomer());
                showInfoFromFile();
                break;
            }
            case 6 : {
                getParticularToy();
                break;
            }
            case 7 : {
                break;
            }
            default: {
                cout << "Wrong option, try again!\n";
            }
        }
    } while (option != 7);
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
        mainApp(&store);
        remove("result.txt");
        remove("storeBusket.dat");
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        throw;
    }
}
