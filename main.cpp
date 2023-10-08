#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

fstream fout;


const int BASE_SALARY = 2000;

enum TypeWorker {
    WORKER, MANAGER, DIRECTOR
};
enum TypeOfOffice {
    LITTLE, MIDDLE, HUGE
};

char professions[3][10] = {
        "Worker",
        "Manager",
        "Director"
};
char offices[3][19] = {
        "little Office",
        "Middle Office",
        "large Office"
};

class Employee {
private:
    TypeWorker typeWorker;
    string name;
    float stage;
public:
    Employee(TypeWorker typeWorker, const string &name, int stage) : typeWorker(typeWorker), name(name), stage(stage) {}

    TypeWorker getTypeWorker() const {
        return typeWorker;
    }

    void showInfoEmployee() {
        cout << "My name is " << name << " and my profession is " << professions[typeWorker] << endl;
        cout << "My work experience : " << stage << endl;
        cout << "My salary is " << BASE_SALARY * (typeWorker + 1);

        fout << "My name is " << name << " and my profession is " << professions[typeWorker] << endl;
        fout << "My work experience : " << stage << endl;
        fout << "My salary is " << BASE_SALARY * (typeWorker + 1);
    }
};

class Happines{
protected:
    string happy;
public:
    explicit Happines(const string &happy) : happy(happy) {}

    virtual void doWork(){
        cout << "Base work";
    };
};

class WorkingEmployee : public Employee, protected Happines{
public:
    WorkingEmployee(TypeWorker typeWorker, const string &name, int stage, const string &happy) : Employee(typeWorker,
                                                                                                          name, stage),
                                                                                                 Happines(happy) {}
    void doWork() override{
        switch (Employee::getTypeWorker()) {
            case WORKER: {
                cout << " and i like do a lot of job!!" << " I am " << Happines::happy << endl;
                fout << " and i like do a lot of job!!" << " I am " << Happines::happy << endl;
                break;
            }
            case MANAGER: {
                cout << " and i like see how someone do his job" << " I am " << Happines::happy << endl;
                fout << " and i like see how someone do his job" << " I am " << Happines::happy << endl;
                break;
            };
            case DIRECTOR: {
                cout << " and i love money" << " I am " << Happines::happy << endl;
                fout << " and i love money" << " I am " << Happines::happy << endl;
                break;
            }
        }
    }
};

class Office {
private:
    string nameOfOffice;
    TypeOfOffice typeOfOffice;
public:
    Office(const string &nameOfOffice, TypeOfOffice typeOfOffice) : nameOfOffice(nameOfOffice),
                                                                    typeOfOffice(typeOfOffice) {
    }

    void showOfficeInfo() {
        cout << "This is " << nameOfOffice << " and this is " << offices[typeOfOffice] << endl;
        fout << "This is " << nameOfOffice << " and this is " << offices[typeOfOffice] << endl;
    }

};

class RealOffice : public WorkingEmployee, protected Office {
public:
    RealOffice(TypeWorker typeWorker, const string &name, int stage, const string &work, const string &nameOfOffice,
               TypeOfOffice typeOfOffice) : WorkingEmployee(typeWorker, name, stage, work),
                                            Office(nameOfOffice, typeOfOffice) {}

    void showAllInfoAboutOffice() {
        Office::showOfficeInfo();
        WorkingEmployee::showInfoEmployee();
        WorkingEmployee::doWork();
    }
};

class Company : public RealOffice {
public:
    Company(TypeWorker typeWorker, const string &name, int stage, const string &work, const string &nameOfOffice,
            TypeOfOffice typeOfOffice) : RealOffice(typeWorker, name, stage, work, nameOfOffice, typeOfOffice) {}

    void showCompanyInfo() {
        cout << "About our Employee : " << endl;
        fout << "About our Employee : " << endl;
        showAllInfoAboutOffice();
        cout << endl;
        fout << endl;
    }
};

int main() {
    fout.open("result.txt", fstream :: app);
    Company firstEmployee = Company(TypeWorker::MANAGER, "Sofia", 7, "Trully happy", "FrynzenskiOffice", TypeOfOffice::MIDDLE);
    Company secondEmployee = Company(TypeWorker::WORKER, "Vlad", 2, "Ready for work", "RechitskiOffice", TypeOfOffice::HUGE);
    Company thirdEmployee = Company(TypeWorker::DIRECTOR, "Ksenia", 12, "Im tired...", "FrynzenskiOffice", TypeOfOffice::MIDDLE);
    vector<Company> companies = {firstEmployee, secondEmployee, thirdEmployee};

    for(Company company : companies){
        company.showCompanyInfo();
    }
    fout.close();
}