#pragma once

template<class T> class Tree {
protected:
    class Node {
    public:
        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(T key) : key(key), height(1) {}

        Node(const Node& node) {
            if (&node == nullptr)
                throw std::range_error("Node cant be created from null");
            key = node.key;
            height = node.height;
            if (node.left) left = new Node(*node.left);
            if (node.right) right = new Node(*node.right);
        }

        Node(Node* node) {
            if (node) {
                key = node->key;
                height = node->height;
                left = new Node(*(node->left));
                right = new Node(*(node->right));
            }
        }

        Node() :Node(nullptr) {};

       
    };

private:
    void DestroyNode(Node* node) {
        if (node) {
            if (node->left) DestroyNode(node->left);
            if (node->right) DestroyNode(node->right);
            delete node;
        }
    }

    int height(Node* N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node* RightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;
        y->height = max(height(y->left),
            height(y->right)) + 1;
        x->height = max(height(x->left),
            height(x->right)) + 1;
        return x;
    }
    Node* LeftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left),
            height(x->right)) + 1;
        y->height = max(height(y->left),
            height(y->right)) + 1;

        return y;
    }
    int GetBalance(Node* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* FindMin(Node* node)
    {
        while (node->left != NULL) node = node->left;
        return node;
    }
protected:
    Node* root;

    void Mapping(T(*mapper)(T), Node* node) {
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        node->key = mapper(node->key);
        if (node->left) Mapping(mapper, node->left);
        if (node->right) Mapping(mapper, node->right);
    }

    void WherePath(bool(*predicate)(T), Node* node, Tree<T>* tree) {
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        if (predicate(node->key)) tree->Append(node->key);
        if (node->left) WherePath(predicate, node->left, tree);
        if (node->right) WherePath(predicate, node->right, tree);
    }

    T ReducePath(T(*reducer)(T, T), T const& c, Node* node) {
        if (node) {
            T res = reducer(node->key, c);
            res = ReducePath(reducer, res, node->left);
            res = ReducePath(reducer, res, node->right);
            return res;
        }
        return c;
    }
public:
    Tree() {
        root = nullptr;
    }

    Tree(T rootKey) {
        root = new Node(rootKey);
    }

    Tree(std::initializer_list<T> items) :Tree() {
        for (T item : items) {
            Append(item);
        }
    }

    Tree(const Node& root) {
        this->root = new Node(root);
    }
    Tree(Node* root) {
        this->root = new Node(root);
    }

    Tree(const Tree& tree) : Tree() {
        if (tree.root != nullptr) root = new Node(*tree.root);
    }

    ~Tree() {
        DestroyNode(root);
    }

    void Append(T key) {
        if (&key == nullptr) {
            throw std::range_error("You cant append NULL");
        }
        root = Insert(root, key);
    }

    Node* Insert(Node* node, T key)
    {
        if (node == NULL)
            return(new Node(key));

        if (key < node->key)
            node->left = Insert(node->left, key);
        else if (key > node->key)
            node->right = Insert(node->right, key);
        else

        node->height = 1 + max(height(node->left),
            height(node->right));
        int balance = GetBalance(node);
        //4
        if (balance > 1 && key < node->left->key)
            return RightRotate(node);
        if (balance < -1 && key > node->right->key)
            return LeftRotate(node);
        if (balance > 1 && key > node->left->key)
        {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
        if (balance < -1 && key < node->right->key)
        {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }
        return node;
    }
    Node* Remove(T key) {
        if (&key == nullptr || !root) {
            throw std::range_error("You cant remove NULL");
        }
        return Delete(root, key);
    }
    Node* Delete(Node* node, T key) {
        if (node == nullptr) return node;
        else if (key < node->key) node->left = Delete(node->left, key);
        else if (key > node->key) node->right = Delete(node->right, key);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == NULL) {
                struct Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == NULL) {
                struct Node* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                Node* temp = FindMin(node->right);
                node->key = temp->key;
                node->right = Delete(node->right, temp->key);
            }
        }
        return node;
    }

    bool Search(T key) {
        if (&key == nullptr || !root) {
            throw std::range_error("You cant search NULL");
        }
        Node** current = &root;
        while (*current) {
            Node& node = **current;
            if (key < node.key) {
                current = &node.left;
            }
            else {
                if (key > node.key) {
                    current = &node.right;
                }
                else {
                    return (*current)->key == key;
                }
            }
        }
        return false;
    }

    Node* SearchNode(T key) {
        Node** current = &root;
        while (*current) {
            Node& node = **current;
            if (key < node.key) {
                current = &node.left;
            }
            else {
                if (key > node.key) {
                    current = &node.right;
                }
                else {
                    return (*current);
                }
            }
        }
        return nullptr;
    }

    Tree<T> SubTree(T key) {
        Node** current = &root;
        while (*current) {
            Node& node = **current;
            if (key < node.key) {
                current = &node.left;
            }
            else {
                if (key > node.key) {
                    current = &node.right;
                }
                else {
                    return Tree(**current);
                }
            }
        }
        return Tree();
    }

    bool SearchSubTree(const Tree& tree) {
        if (&tree == nullptr || tree.root == nullptr) return false;
        Node** current = &root;
        T key = tree.root->key;
        while (*current) {
            Node& node = **current;
            if (key < node.key) {
                current = &node.left;
            }
            else {
                if (key > node.key) {
                    current = &node.right;
                }
                else {
                    bool a1 = false;
                    if ((*current)->right != nullptr && tree.root->right != nullptr)
                        a1 = tree.root->right->key == (*current)->right->key;
                    else if ((*current)->right == nullptr && tree.root->right == nullptr)
                        a1 = true;

                    bool a2 = false;
                    if ((*current)->left != nullptr && tree.root->left != nullptr)
                        a2 = tree.root->left->key == (*current)->left->key;
                    else if ((*current)->left == nullptr && tree.root->left == nullptr)
                        a2 = true;

                    bool result = key == (*current)->key && a1 && a2;

                    return result;
                }
            }
        }
        return false;
    }

    Tree<T> Map(T(*mapper)(T)) {
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Tree<T> newTree = Tree<T>(*this);
        Mapping(mapper, newTree.root);
        return newTree;
    }
    Tree<T> Where(bool(*predicate)(T)) {
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Tree<T> newTree = Tree<T>();
        WherePath(predicate, this->root, &newTree);
        return newTree;
    }
    T Reduce(T(*reducer)(T, T), T const& c) {
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = ReducePath(reducer, c, root);
        return res;
    }

    void PreOrder(Node* node, int ctr)
    {
        if (node != nullptr)
        {
            std::string brackets[] = { "{", "}", "(", ")", "[", "]" };
            std::cout << brackets[ctr] << node->key << " ";
            PreOrder(node->left, (ctr + 2) % 6);
            PreOrder(node->right, (ctr + 4) % 6);
            std::cout << brackets[ctr + 1];
        }
    }
    void Output() {
        PreOrder(root, 0);
        std::cout << "\n";
    }
};