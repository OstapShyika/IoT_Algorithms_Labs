#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    int height;
};

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

Node* newNode(int val) {
    Node* node = new Node();
    node->val = val;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return (node);
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* z = y->left;
    y->left = x;
    x->right = z;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* z = x->right;
    x->right = y;
    y->left = z;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return x;
}

int balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* insertNode(Node* node, int val) {
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

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

int main() {

    return 0;
}
