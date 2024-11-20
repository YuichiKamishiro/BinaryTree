#include <iostream>

#define ENABLE_LOGGING 0

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

    ~Node() {
        if (ENABLE_LOGGING)
            std::cout << "~Node()\n";
    }
};

template <typename T>
struct Tree {
    Node<T> *root;
    int size = 1;

    Tree(T val) { root = new Node<T>(val); }
    ~Tree() { deleteNodesRecursive(root); }

    int getSize() { return size; }

    void deleteNodesRecursive(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        deleteNodesRecursive(node->left);
        deleteNodesRecursive(node->right);
        delete node;
    }

    void clear() {
        deleteNodesRecursive(root);
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
        while(currentNode->left != nullptr && currentNode != nullptr) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    Node<T>* deleteNodeRecursive(Node<T> *root, int val) {
        if (root == nullptr) return root;

        if (val < root->val) {
            root->left = deleteNodeRecursive(root->left, val);
        } else if (val > root->val) {
            root->right = deleteNodeRecursive(root->left, val);
        } else {
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
            root->right = deleteNodeRecursive(root->right, succ->val);
        }

        return root;
    }
    void deleteNode(T x) {
        root = deleteNodeRecursive(root, x);
        size--;
    }

    void inorderRecursive(Node<T> *node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            std::cout << node->val << " ";
            inorderRecursive(node->right);
        }
    }

    void print() {
        inorderRecursive(root);
        std::cout << "\n";
    }
};

int main() {
    Tree<int> t(12);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);

    std::cout << "Initial tree: ";
    t.print();
    std::cout << "Size: " << t.getSize() << "\n";

    t.deleteNode(5);
    std::cout << "After deleting 5: ";
    t.print();
    std::cout << "Size: " << t.getSize() << "\n";

    return 0;
}