#pragma once

#include "BinaryTree.h"
#include "ArraySequence.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T> class Set : public Tree<T>{
protected:
    void UnionPath(typename Tree<T>::Node* node, Set<T>* set) {
        if (node) {
            set->Add(node->key);
            UnionPath(node->left, set);
            UnionPath(node->right, set);    
        }
    }

    Set<T> IntersectionPath(typename Tree<T>::Node* root1, typename Tree<T>::Node::Node* root2)
    {
        Set<T> result = Set<T>();
        ArraySequence<typename Tree<T>::Node*> s1, s2;

        while (true)
        {
            if (root1)
            {
                s1.Append(root1);
                root1 = root1->left;
            }
            else if (root2)
            {
                s2.Append(root2);
                root2 = root2->left;
            }
            else if (s1.GetLength() > 0 && s2.GetLength() > 0)
            {
                root1 = s1.GetLast();
                root2 = s2.GetLast();
                if (root1->key == root2->key)
                {
                    result.Append(root1->key);
                    s1.PopLast();
                    s2.PopLast();
                    root1 = root1->right;
                    root2 = root2->right;
                }

                else if (root1->key < root2->key)
                {
                    s1.PopLast();
                    root1 = root1->right;
                    root2 = NULL;
                }
                else if (root1->key > root2->key)
                {
                    s2.PopLast();
                    root2 = root2->right;
                    root1 = NULL;
                }
            }
            else  break;
        }
        return result;
    }

    Set<T> SubstractionPath(typename Tree<T>::Node* root1, typename Tree<T>::Node* root2, Set<T> set)
    {
        Set<T> result = Set<T>(set);
        ArraySequence<typename Tree<T>::Node*> s1, s2;

        while (true)
        {
            if (root1)
            {
                s1.Append(root1);
                root1 = root1->left;
            }
            else if (root2)
            {
                s2.Append(root2);
                root2 = root2->left;
            }
            else if (s1.GetLength() > 0 && s2.GetLength() > 0)
            {
                root1 = s1.GetLast();
                root2 = s2.GetLast();
                if (root1->key == root2->key)
                {
                    result.Delete(root1->key);
                    s1.PopLast();
                    s2.PopLast();
                    root1 = root1->right;
                    root2 = root2->right;
                }

                else if (root1->key < root2->key)
                {
                    s1.PopLast();
                    root1 = root1->right;
                    root2 = NULL;
                }
                else if (root1->key > root2->key)
                {
                    s2.PopLast();
                    root2 = root2->right;
                    root1 = NULL;
                }
            }
            else  break;
        }
        return result;
    }

    bool SubSetPath(typename Tree<T>::Node* root1, typename Tree<T>::Node* root2, Set<T> set)
    {
        Set<T> result = Set<T>();
        ArraySequence<typename Tree<T>::Node*> s1, s2;
        while (true)
        {
            if (root1)
            {
                s1.Append(root1);
                root1 = root1->left;
            }
            else if (root2)
            {
                s2.Append(root2);
                root2 = root2->left;
            }
            else if (s1.GetLength() > 0 && s2.GetLength() > 0)
            {
                root1 = s1.GetLast();
                root2 = s2.GetLast();

                if (root1->key == root2->key)
                {
                    result.Append(root1->key);
                    s1.PopLast();
                    s2.PopLast();

                    root1 = root1->right;
                    root2 = root2->right;
                }

                else if (root1->key < root2->key)
                {
                    s1.PopLast();
                    root1 = root1->right;
                    root2 = NULL;
                }
                else if (root1->key > root2->key)
                {
                    s2.PopLast();
                    root2 = root2->right;
                    root1 = NULL;
                }
            }
            else  break;
        }
        return set.IsEqual(result);
    }

    bool IsEqualNode(typename Tree<T>::Node* node1, typename Tree<T>::Node* node2) {
        if (node1 && node2) {
            if (node1->key == node2->key) {
                bool result = IsEqualNode(node1->left, node2->left) && IsEqualNode(node1->right, node2->right);
                return result;
            }
            else {
                return false;
            }
        }
        if (!node1 && !node2) {
            return true;
        }
        return false;
    }

    void DisplayNode(typename Tree<T>::Node* node) {
        if (node) {
            DisplayNode(node->left);
            cout << node->key << ", ";
            DisplayNode(node->right);
        }
    }
    void DisplayNode(typename Tree<T>::Node* node, bool isList) {
        if (node) {
            if (!isList) {
                DisplayNode(node->left);
                cout << node->key << ", ";
                DisplayNode(node->right);
            }
            else {
                DisplayNode(node->left, isList);
                cout << node->key << "\n";
                DisplayNode(node->right, isList);
            }
        }
    }
public:
    Set() = default;
    Set(initializer_list<T> items) {
        for (T item : items) {
            this->Append(item);
        }
    }
    Set(const Set& set) : Tree<T>(set) {

    }
    Set(const typename Tree<T>::Node& node) : Tree<T>(node) {

    }

    void Add(T value) {
        this->Append(value);
    }

    void Delete(T value) {
        this->Remove(value);
    }
    bool Contains(T value) {
        return this->Search(value);
    }
    Set<T> MapSet(T(*mapper)(T)) {
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Set<T> newSet = Set<T>(*this);
        Mapping(mapper, newSet.root);
        return newSet;
    }
    Set<T> WhereSet(bool(*predicate)(T)) {
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Set<T> newSet = Set<T>();
        WherePath(predicate, this->root, &newSet);
        return newSet;
    }
    T ReduceSet(T(*reducer)(T, T), T const& c) {
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = ReducePath(reducer, c, this->root);
        return res;
    }

    Set<T> Intersection(Set<T> set) {
        return IntersectionPath(set.root, this->root);
    }

    Set<T> Union(Set<T> set) {
        Set<T> result = Set<T>(*this);
        UnionPath(set.root, &result);
        return result;
    }

    Set<T> Substraction(Set<T> set) {
        return SubstractionPath(set.root, this->root, *this);
    }

    bool IsEqual(Set<T> set) {
        return IsEqualNode(set.root, this->root);
    }

    bool IsSubSet(Set<T> set) {
        return SubSetPath(set.root, this->root, set);
    }

    bool operator==(Set<T> set) {
        return IsEqual(set);
    }
    Set<T> operator&(Set<T> set) {
        return Intersection(set);
    }
    Set<T> operator|(Set<T> set) {
        return Union(set);
    }
    Set<T> operator-(Set<T> set) {
        return Substraction(set);
    }

    void Display() {
        cout << "(";
        if (Tree<T>::root) DisplayNode(Tree<T>::root);
        cout << ")\n";
    }
    void Display(bool isList) {
        cout << "(\n";
        if (Tree<T>::root) DisplayNode(Tree<T>::root, isList);
        cout << ")\n";
    }
};