#include <iostream>
#include "Person.h"
#include "BinaryTree.h"
#include "Set.h"

using namespace std;


const char* MSGS[] = { "0. Quit",
                      "1. Add value",
                      "2. Remove value",
                      "3. Print",
                      "4. Print like list" };

const char* MSGS1[] = { "0. Quit",
                      "1. Int",
                      "2. Double",
                      "3. String" };

template<int N>
int Dialog(const char* (&msgs)[N]) {
    string error;
    int choice = -1;
    do {
        cout << error;
        error = "You're wrong. Try again!\n";
        for (int i = 0; i < N; ++i) {
            cout << msgs[i] << endl;
        }
        cout << "Make your choice: \n";
        cin >> choice;
    } while (choice < 0 || choice >= N);
    return choice;
}

template<typename T>
void StartUI() {
    int res = 1;
    string tmp;
    Set<T> set = Set<T>();
    while (res != 0) {
        res = Dialog(MSGS);
        switch (res) {
        case 0:
            break;
        case 1: {
            T value;
            cin >> value;
            set.Add(value);
        }
              break;
        case 2: {
            T value1;
            cin >> value1;
            set.Tree<T>::Remove(value1);
        }
              break;
        case 3:
            set.Display();
            break;
        case 4:
            set.Display(true);
            break;
        default: {
            break;
        }
        }
    }
}

int main() {
    int res = 1;
    cout << "Enter data type:" << endl;
    res = Dialog(MSGS1);
    switch (res) {
    case 0:
        break;
    case 1:
        StartUI<int>();
        break;
    case 2:
        StartUI<double>();
        break;
    case 3:
        StartUI<string>();
        break;
    default: {
        break;
    }
    }
    return 0;
}
