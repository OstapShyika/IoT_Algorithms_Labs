#include <iostream>

using namespace std;

struct NodeStruct {
    NodeStruct *parent;
    NodeStruct *left;
    NodeStruct *right;
    int val;
    int color;
};

typedef NodeStruct *Node;

class RedBlackTree {
private:
    Node root;
    Node Tnill;

    void leftRotate(Node x) {
        Node y = x->right;
        x->right = y->left;
        if (y->left != Tnill) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } 
        else if (x == x->parent->left) {
            x->parent->left = y;
        } 
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node x) {
        Node y = x->left;
        x->left = y->right;
        if (y->right != Tnill) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } 
        else if (x == x->parent->right) {
            x->parent->right = y;
        } 
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    Node minimum(Node node) {
        while (node->left != Tnill) {
            node = node->left;
        }
        return node;
    }

    void rbTransplant(Node x, Node y) {
        if (x->parent == nullptr) {
            root = y;
        } 
        else if (x == x->parent->left) {
            x->parent->left = y;
        } 
        else {
            x->parent->right = y;
        }
        y->parent = x->parent;
    }


    void deleteFixup(Node x) {
        Node w;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                w = x->parent->right;
                if (w->color == 1) {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == 0 && w->right->color == 0) {
                    w->color = 1;
                    x = x->parent;
                } 
                else {
                    if (w->right->color == 0) {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } 
            else {
                w = x->parent->left;
                if (w->color == 1) {
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->left->color == 0 && w->right->color == 0) {
                    w->color = 1;
                    x = x->parent;
                } 
                else {
                    if (w->left->color == 0) {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void deleteNodeGivenRoot(Node node, int key) {
        Node z = Tnill;
        Node x, y;
        while (node != Tnill) {
            if (node->val == key) {
                z = node;
            }

            if (node->val <= key) {
                node = node->right;
            } 
            else {
                node = node->left;
            }
        }

        if (z == Tnill) {
            cout << "Not found." << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == Tnill) {
            x = z->right;
            rbTransplant(z, z->right);
        } 
        else if (z->right == Tnill) {
            x = z->left;
            rbTransplant(z, z->left);
        } 
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } 
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFixup(x);
        }
    }


public:
    
    void deleteNode(int val) {
        deleteNodeGivenRoot(this->root, val);
    }
    
};

int main() {
    return 0;
}
