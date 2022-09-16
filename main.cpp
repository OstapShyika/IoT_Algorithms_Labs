#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    int height;
};

typedef Node* AVLTree;

int height(AVLTree node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

AVLTree newNode(int val) {
    auto node = new Node;
    node->val = val;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return (node);
}

AVLTree leftRotate(AVLTree x) {
    AVLTree y = x->right;
    AVLTree z = y->left;
    y->left = x;
    x->right = z;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLTree rightRotate(AVLTree y) {
    AVLTree x = y->left;
    AVLTree z = x->right;
    x->right = y;
    y->left = z;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return x;
}

int balanceFactor(AVLTree node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLTree insertNode(AVLTree node, int val) {
    if (node == nullptr) { 
        return (newNode(val)); 
    }
    if (val < node->val) { 
        node->left = insertNode(node->left, val); 
    }
    else if (val > node->val) { 
        node->right = insertNode(node->right, val); 
    }
    else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    if (balanceFactor(node) > 1) {
        //ll
        if (val < node->left->val) {
            return rightRotate(node);
        }
        //lr
        else if (val > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor(node) < -1) {
        //rr
        if (val > node->right->val) {
            return leftRotate(node);
        }
        //rl
        else if (val < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

void inorder(AVLTree root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

int main() {
    AVLTree root = nullptr;

    root = insertNode(root, 22);
    root = insertNode(root, 13);
    root = insertNode(root, 74);
    root = insertNode(root, 8);
    root = insertNode(root, 45);
    root = insertNode(root, 99);
    root = insertNode(root, 3);

    inorder(root);

    return 0;
}
