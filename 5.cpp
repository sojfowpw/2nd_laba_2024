#include "avl.hpp"

int main() {
    avl tree;
    tNode* root = nullptr;
    root = new tNode(7);
    root->height = 4;
    root->left = new tNode(3);
    root->left->height = 3;
    //root->right = tree.insert(root->right, 2);
    root->left->left = new tNode(1);
    root->left->left->height = 2;
    root->left->right = new tNode(9);
    root->left->right->height = 2;
    //root->right->left = tree.insert(root->right->left, 5);
    //root->right->right = tree.insert(root->right->right, 4);
    root->left->left->left = new tNode(6);
    root->left->left->left->height = 1;
    root->left->left->right = new tNode(8);
    root->left->left->right->height = 1;
    tree.printAvl(root, 0);
    if (tree.getBalance(root) <= 1 && tree.getBalance(root) >= -1) {
        cout << "YES.\n";
    }
    else {
        cout << "NO.\n";
    }
}