#include <iostream>

using namespace std;

enum Color {
    BLACK, RED
};

struct NodeStruct {
    NodeStruct* parent;
    NodeStruct* left;
    NodeStruct* right;
    int val;
    Color color;
};

typedef NodeStruct* Node;

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

    void inorderGivenRoot(Node node) {
        if (node != Tnill) {
            inorderGivenRoot(node->left);
            cout << " (" << node->color << " " << node->val << ") ";
            inorderGivenRoot(node->right);
        }
    }

    void insertFixup(Node z) {
        Node y;
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->right) {
                y = z->parent->parent->left;
                if (y->color == RED) {
                    y->color = BLACK;
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
            else {
                y = z->parent->parent->right;

                if (y->color == RED) {
                    y->color = BLACK;
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            if (z == root) {
                break;
            }
        }
        root->color = BLACK;
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
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                w = x->parent->right;

                //x’s sibling w is red
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                //x’s sibling w is black, and both of w’s children are black
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } 
                else {
                    //x’s sibling w is black, w’s left child is red, and w’s right child is black
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    //x’s sibling w is black, and w’s right child is red
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } 
            else {
                w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } 
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void deleteNodeGivenRoot(Node node, int key) {
        Node z = Tnill;
        Node x, y;

        //Search of key
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
        if (y_original_color == BLACK) {
            deleteFixup(x);
        }
    }

public:

    RedBlackTree() {
        Tnill = new NodeStruct;
        Tnill->left = nullptr;
        Tnill->right = nullptr;
        Tnill->color = BLACK;
        root = Tnill;
    }

    void deleteNode(int val) {
        deleteNodeGivenRoot(this->root, val);
    }

    void inorderPrint() {
        inorderGivenRoot(this->root);
    }

    void insert(int key) {
        Node node = new NodeStruct;
        node->parent = nullptr;
        node->val = key;

        Node y = nullptr;
        Node x = this->root;

        while (x != Tnill) {
            y = x;
            if (node->val < x->val) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->val < y->val) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        node->left = Tnill;
        node->right = Tnill;
        node->color = RED;

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFixup(node);
    }

};

int main() {
    RedBlackTree bst;

    bst.insert(21);
    bst.insert(34);
    bst.insert(4);
    bst.insert(62);
    bst.insert(81);

    bst.inorderPrint();

    cout << endl
         << "62 deleted..." << endl;

    bst.deleteNode(62);
    bst.inorderPrint();

    return 0;
}
