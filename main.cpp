#include<iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;
ofstream fout;

class Set {
private :
    vector<int> vect;
public:
    Set() {};

    Set(const vector<int> &vect);

    Set(const Set *set) {
        this->vect = set->vect;
    }

    ~Set();

    vector<int> operator&(const Set &set);

    vector<int> operator|(const Set &set);

    friend void showGeneralElements(Set &set);

    friend void showAllElements(Set &set);
};

vector<int> Set::operator&(const Set &set) {
    vector<int> answer;
    for (int i: vect) {
        for (int j: set.vect) {
            if (i == j) {
                answer.push_back(i);
                break;
            }
        }
    }
    return answer;
}

vector<int> Set::operator|(const Set &set) {
    vector<int> answer;
    for (int number: vect) {
        answer.push_back(number);
    }
    for (int number: set.vect) {
        answer.push_back(number);
    }
    for (int i = 1; i < answer.size(); ++i) {
        for (int k = 0; k < i; ++k) {
            if (answer.at(i) == answer.at(k)) {
                answer.erase(answer.begin() + i);
                --i;
                break;
            }
        }
    }
    return answer;
}

Set::Set(const vector<int> &vect) : vect(vect) {}

Set::~Set() {
    vect.clear();
}

void showGeneralElements(Set &set) {
    cout << "Result of general elements : " << endl;
    fout << "Result of general elements : " << endl;
    for (int number: set.vect) {
        cout << number << " ";
        fout << number << " ";
    }
    fout << endl;
    cout << endl;
}

void showAllElements(Set &set) {
    cout << "Result of merging elements : " << endl;
    fout << "Result of general elements : " << endl;
    for (int number: set.vect) {
        cout << number << " ";
        fout << number << " ";
    }
    fout << endl;
    cout << endl;
}

int getIntValue() {
    int value = 0;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input " << endl;
        } else
            break;
        cout << "Try again" << endl;
    }
    return value;
}

vector<int> createVector() {
    int size;
    cout << "Write size of your vector : ";
    size = getIntValue();
    vector<int> endVector;
    int values;
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". number : ";
        values = getIntValue();
        endVector.push_back(values);
    }
    return endVector;
}

void menuFunction() {
    fout.open("values.txt", ofstream::app);
    string quit = "";
    for (;;) {
        vector<int> arr = createVector();
        vector<int> arr2 = createVector();

        Set set(arr);
        Set set2(arr2);

        Set setAll = (set | set2);
        Set setGeneral = (set & set2);

        showGeneralElements(setGeneral);
        showAllElements(setAll);

        cout << "quit/continue : ";
        cin >> quit;
        if (quit == "quit") {
            cout << "end of programm !";
            break;
        } else {
            cout << "Will continue...." << endl;
        }
        cin.ignore();
    }
    fout.close();
}

int main() {

    menuFunction();

    return 0;
}
