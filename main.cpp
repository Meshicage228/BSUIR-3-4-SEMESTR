#include<iostream>
#include<windows.h>
#include <vector>
#include <fstream>

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
    return answer;
}

Set::Set(const vector<int> &vect) : vect(vect) {}

Set::~Set() {
    vect.clear();
}

void showGeneralElements(vector<int> vect){
    cout << "Result of general elements : " << endl;
    fout << "Result of general elements : " << endl;
    for (int number: vect) {
        cout << number << " ";
        fout << number << " ";
    }
    fout << endl;
    cout << endl;
}

void showAllElements(vector<int> vect){
    cout << "Result of merging elements : " << endl;
    fout << "Result of general elements : " << endl;
    for (int number: vect) {
        cout << number << " ";
        fout << number << " ";
    }
    fout << endl;
    cout << endl;
}
vector<int> createVector(){
    int size = 0;
    cout << "Write size of your vector : ";
    cin >> size;

    vector<int> endVector;
    int values = 0;
    for(int i = 0; i < size; i++){
        cout << i+1  << ". number : ";
        cin >> values;
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

        showGeneralElements((set & set2));
        showAllElements((set | set2));

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
