#include <iostream>

#define ENABLE_LOGING 1

template<typename T>
struct Node {
    T val;
    Node *right = nullptr;
    Node *left = nullptr;

    Node(T val) : val{val} {}
    ~Node() {
        if (ENABLE_LOGING) {
            std::cout << "~Node()\n";
        }
    }
};

template<typename T>
struct Tree {
    Node<T> *root;
    int size = 1;

    Tree(T val) {
        root = new Node<T>(val);
    }
    ~Tree() {
        deleteNodeRecursive(root);
    }

    int getSize() {
       return size; 
    }

    void deleteNodeRecursive(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        deleteNodeRecursive(node->left);
        deleteNodeRecursive(node->right);
        delete node;
    }

    void clear() {
        deleteNodeRecursive(root);
        root = nullptr;
        size = 0;
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
            else if (val > bufNode->val) {
                if(bufNode->right == nullptr) {
                    bufNode->right = new Node<T>(val);
                    this->size++;
                    break;
                } else {
                    bufNode = bufNode->right;
                }
            } else {
                break;
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
    Tree t("123");
    t.insert("12");
    
    t.print();
    std::cout << t.getSize() << "\n";
    t.clear();
    std::cout << t.getSize() << "\n";
}   