#include <ctime>
#include <iostream>
#include <fstream>
#include "../LabMain/BinaryTree.h"
#include "../LabMain/Set.h"

using namespace std;

int main()
{
    ofstream cout("Data.txt");
    cout << "Writeinfo\n";
    cout << "Append\n";
    cout << "Tree\n";
    cout << 0;
    cout << 1;
    cout << "\n Tree int \n";
    for (int i = 1; i < 21; i++) {
        int start = clock();
        Tree<int>* D1 = new Tree<int>;
        for (int j = 0; j < pow(2, i); j++) {
            D1->Append(1);
        }

        int end = clock();
        int x = end - start;
        cout << x << ";" << pow(2, i) << "\n";
    }

    cout << 2;
    cout << "\nTree double\n";
    for (int i = 1; i < 21; i++) {
        int start = clock();
        Tree<double>* D1 = new Tree<double>;
        for (int j = 0; j < pow(2, i); j++) {
            D1->Append(1);
        }
        int end = clock();
        int x = end - start;
        cout << x << ";" << pow(2, i) << "\n";
    }
    cout << 3;
    cout << "\nSearch\n";
    for (int i = 1; i < 21; i++) {

        Tree<int>* D1 = new Tree<int>();
        for (int j = 0; j < pow(2, i); j++) {
            D1->Append(j);
        }
        int start = clock();
        for (int j = 0; j < pow(2, i); j++) {
            D1->Search(j);
        }

        int end = clock();
        int x = end - start;
        cout << x << ";" << pow(2, i) << "\n";
    }
    cout << 4;
    cout << "\nSet\n";
    for (int i = 1; i < 21; i++) {
        Set<int>* D1 = new Set<int>();
        for (int j = 0; j < pow(2, i); j++) {
            D1->Add(j);
        }
        int start = clock();

        for (int j = 0; j < pow(2, i); j++) {
            D1->Add(i);
        }

        int end = clock();
        int x = end - start;
        cout << x << ";" << pow(2, i) << "\n";
    }
    cout << 5;
    cout << "\nSearch in set\n";
    for (int i = 1; i < 21; i++) {

        Set<int>* D1 = new Set<int>();
        for (int j = 0; j < pow(2, i); j++) {
            D1->Add(j);
        }
        int start = clock();
        for (int j = 1; j < pow(2, i); j++) {
            D1->Contains(j);
        }

        int end = clock();
        int x = end - start;
        cout << x << ";" << pow(2, i) << "\n";
    }
    cout << "Finish!\n";
}