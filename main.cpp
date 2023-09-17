#include <iostream>
#include <fstream>

using namespace std;

class MyString {
private:
    string value;
public:
    MyString() {}

    ~MyString() {};

    MyString(const MyString &t) {
        value = t.value;
    };

    MyString(const string &value) : value(value) {}

    void trim();

    bool isEmpty();

    int length();

    const string &getValue() const;

    void setValue(const string &value);
};

bool MyString::isEmpty() {
    return value.length() == 0;
}

void MyString::trim() {
    int start = 0, end = value.size() - 1;

    for (int i = 0; i < value.size(); i++) {
        if (value[i] != ' ') {
            start = i;
            break;
        }
    }
    for (int i = end; i >= 0; i--) {
        if (value[i] != ' ') {
            end = i;
            break;
        }
    }

    string stringNoSpaces = "";

    for (int i = start; i <= end; i++) {
        stringNoSpaces += value[i];
    }
    value = stringNoSpaces;
}

int MyString::length() {
    int sizeWithSpaces = 0;
    for (int i = 0; i < value.size(); i++) {
        sizeWithSpaces++;
    }
    return sizeWithSpaces;
}

const string &MyString::getValue() const {
    return value;
}

void MyString::setValue(const string &value) {
    MyString::value = value;
}

void menuFunction() {
    string quit = "";
    for (;;) {
        cout << "Write value : ";
        string val = "";
        getline(cin, val);
        MyString str = MyString(val);

        if (str.isEmpty()) {
            cout << "This value is empty!" << endl;
        } else {
            cout << "This value doesnt empty!" << endl;
        }

        cout << "value : " << endl;
        cout << str.getValue() << " its length : " << str.length() << endl;

        cout << "after trim : " << endl;
        str.trim();

        cout << str.getValue() << " its length : " << str.length() << endl;
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
}

int main() {

    menuFunction();

    return 0;
}