#include <iostream>

template<typename T>
struct Node {
    T val;
    Node *right = nullptr;
    Node *left = nullptr;

    Node(T val) : val{val} {}
};

template<typename T>
struct Tree {
    Node<T> *root;
    int size = 0;

    Tree(T val) {
        root = new Node<T>(val);
    }

    T getSize() {
       return size; 
    }
    void insert(T val) {
        Node<T> *bufNode = root;
        while(true) {
            if (val < bufNode->val) {
                if(bufNode->left == nullptr) {
                    bufNode->left = new Node<T>(val);
                    this->size++;
                    break;
                } else {
                    bufNode = bufNode->left;
                }
            }
            if (val > bufNode->val) {
                if(bufNode->right == nullptr) {
                    bufNode->right = new Node<T>(val);
                    this->size++;
                    break;
                } else {
                    bufNode = bufNode->right;
                }
            } 

        }
    }
     void inorderRecursive(Node<T>* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            std::cout << node->val << " ";
            inorderRecursive(node->right);
        }
    }
    void print() {
        Node<T> *bufNode = root;
        inorderRecursive(bufNode);
    }
};


int main() {
    Tree<int> t(6);
    t.insert(1);
    t.insert(3);
    t.insert(22);
    t.insert(18);
    t.print();
}   