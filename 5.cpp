#include "avl.hpp"

int main() {
    avl tree;
    tNode* root = nullptr;
    root = tree.insert(root, 1);
    root = tree.insert(root, 2);
    root = tree.insert(root, 3);
    root = tree.insert(root, 4);
    root = tree.insert(root, 5);
    root = tree.insert(root, 6);
    root = tree.insert(root, 7);
    root = tree.insert(root, 0);
    //root = tree.insert(root, 8);
    //root = tree.insert(root, 0);
    tree.printAvl(root, 0);
    if (tree.getBalance(root) <= 1 && tree.getBalance(root) >= -1) {
        cout << "YES.";
    }
    else {
        cout << "NO.";
    }
}