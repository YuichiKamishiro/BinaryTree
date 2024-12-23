#include <iostream>
#include <format>

template <typename T>
concept isValid = requires(T a, T b) {
    std::cout << a;
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a >= b } -> std::convertible_to<bool>;
};

template <isValid T>
struct Node {
    T val;
    Node *right = nullptr;
    Node *left = nullptr;

    Node(T val) : val{val} {}

    ~Node() {}
};

template <typename T>
struct Tree {
    Node<T> *root;
    int size = 0;

    Tree(T val) {
        root = new Node<T>(val);
        size = 1;
    }

    ~Tree() { clearRecursive(root); }

    int getSize() const { return size; }

    void clearRecursive(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }

    void clear() {
        clearRecursive(root);
        root = nullptr;
        size = 0;
    }

    void insert(T val) {
        Node<T> *bufNode = root;
        while (true) {
            if (val < bufNode->val) {
                if (bufNode->left == nullptr) {
                    bufNode->left = new Node<T>(val);
                    this->size++;
                    break;
                } else {
                    bufNode = bufNode->left;
                }
            } else if (val > bufNode->val) {
                if (bufNode->right == nullptr) {
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

    Node<T>* getSuccessor(Node<T> *currentNode) {
        currentNode = currentNode->right;
        while(currentNode != nullptr && currentNode->left != nullptr) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    Node<T>* eraseRecursive(Node<T> *root, T val, bool &deleted) {
        if (root == nullptr) return root;

        if (val < root->val) {
            root->left = eraseRecursive(root->left, val, deleted);
        } else if (val > root->val) {
            root->right = eraseRecursive(root->right, val, deleted); 
        } else { 
            deleted = true; 
            if (root->left == nullptr) {
                Node<T> *temp = root->right;
                delete root;
                return temp;
            }
            if (root->right == nullptr) {
                Node<T> *temp = root->left;
                delete root;
                return temp;
            }
            Node<T> *succ = getSuccessor(root);
            root->val = succ->val; 
            root->right = eraseRecursive(root->right, succ->val, deleted); 
        }

        return root;
    }

    void erase(T x) {
        bool nodeDeleted = false; 
        root = eraseRecursive(root, x, nodeDeleted);
        
        if (nodeDeleted) {
            size--;
        }
    }

    void inorderRecursive(Node<T> *node) const {
        if (node != nullptr) {
            inorderRecursive(node->left);
            std::cout << node->val << " ";
            inorderRecursive(node->right);
        }
    }

    bool empty() const { 
        return size == 0; 
    }

    void print() const {
        inorderRecursive(root);
        std::cout << "\n";
    }
};

void test() {
    Tree<int> t(12);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);

    std::cout << "Initial tree: ";
    t.print();
    std::cout << std::format("Size: {}\n", t.getSize());

    t.erase(222);
    std::cout << "After attempting to delete 222: ";
    t.print();
    std::cout << std::format("Size: {}\n", t.getSize());
}

int main() {
    test();

    return 0;
}