//
//  main.cpp
//  soal
//
//  Created by Arshia Taghavinejad on 2024-01-11.
//
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
class RedBlackTree {
    Node *root;
    
public:
    RedBlackTree() : root(nullptr) {}
    
    void insert(const int &n);
    
    void deleteNode(const int &n);
    
    void rotateLeft(Node *&ptr);
    
    void rotateRight(Node *&ptr);
    
    void fixViolation(Node *&ptr);
    

    void rbTransplant(Node *u, Node *v);
    
    Node* minimum(Node *node);
    
    Node* search(int n);

    void fixDelete(Node *x);
    
    void printTree();
    
};



void RedBlackTree::insert(const int &n) {
    Node *newNode = new Node(n);
    
    if (root == nullptr) {
        root = newNode;
    } else {
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (newNode->data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parent;
        if (newNode->data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    fixViolation(newNode);
}



void RedBlackTree::fixViolation(Node *&ptr) {
    Node *parent_ptr = nullptr;
    Node *grand_parent_ptr = nullptr;

    while ((ptr != root) && (ptr != nullptr) && (ptr->color == RED) && (ptr->parent->color == RED)) {
        parent_ptr = ptr->parent;
        grand_parent_ptr = parent_ptr->parent;

        // Parent of ptr is left child of grandparent
        if (parent_ptr == grand_parent_ptr->left) {
            Node *uncle_ptr = grand_parent_ptr->right;

            // Case 1: Uncle of ptr is also red
            if (uncle_ptr != nullptr && uncle_ptr->color == RED) {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            } else {
                
                // Case 2: ptr is right child of its parent
                if (ptr == parent_ptr->right) {
                    rotateLeft(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                // Case 3: ptr is now left child of its parent
                rotateRight(grand_parent_ptr);
                swap(parent_ptr->color, grand_parent_ptr->color);
                ptr = parent_ptr;
            }
        } else {
            // Parent of ptr is right child of grandparent
            Node *uncle_ptr = grand_parent_ptr->left;

            // Case 1: Uncle of ptr is also red
            if (uncle_ptr != nullptr && uncle_ptr->color == RED) {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            } else {
                // Case 2: ptr is left child of its parent
                if (ptr == parent_ptr->left) {
                    rotateRight(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                // Case 3: ptr is now right child of its parent
                rotateLeft(grand_parent_ptr);
                swap(parent_ptr->color, grand_parent_ptr->color);
                ptr = parent_ptr;
            }
        }
    }

    root->color = BLACK;
}

void RedBlackTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr) {
        ptr->right->parent = ptr;
    }

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr) {
        root = right_child;
    } else if (ptr == ptr->parent->left) {
        ptr->parent->left = right_child;
    } else {
        ptr->parent->right = right_child;
    }

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RedBlackTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr) {
        ptr->left->parent = ptr;
    }

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr) {
        root = left_child;
    } else if (ptr == ptr->parent->left) {
        ptr->parent->left = left_child;
    } else {
        ptr->parent->right = left_child;
    }

    left_child->right = ptr;
    ptr->parent = left_child;
}

Node* RedBlackTree::search(int n) {
    Node* temp = root;
    while (temp != nullptr) {
        if (n < temp->data) {
            temp = temp->left;
        } else if (n > temp->data) {
            temp = temp->right;
        } else {
            return temp;
        }
    }
    return nullptr;
}

void RedBlackTree::deleteNode(const int &data) {
    Node *node = root;
    Node *x, *y, *z;

    while (node != nullptr) {
        if (node->data == data) {
            z = node;
            break;
        } else if (node->data < data) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (node == nullptr) {
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == nullptr) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
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
        fixDelete(x);
    }
}

void RedBlackTree::fixDelete(Node *x) {
    while (x != root && x != nullptr && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *s = x->parent->right;
            if (s == nullptr) {
                x = x->parent;
                continue;
            }

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                s = x->parent->right;
            }

            if ((s->left == nullptr || s->left->color == BLACK) && (s->right == nullptr || s->right->color == BLACK)) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right == nullptr || s->right->color == BLACK) {
                    if (s->left != nullptr) {
                        s->left->color = BLACK;
                    }
                    s->color = RED;
                    rotateRight(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                if (s->right != nullptr) {
                    s->right->color = BLACK;
                }
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node *s = x->parent->left;
            if (s == nullptr) {
                x = x->parent;
                continue;
            }

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                s = x->parent->left;
            }

            if ((s->right == nullptr || s->right->color == BLACK) && (s->left == nullptr || s->left->color == BLACK)) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left == nullptr || s->left->color == BLACK) {
                    if (s->right != nullptr) {
                        s->right->color = BLACK;
                    }
                    s->color = RED;
                    rotateLeft(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                if (s->left != nullptr) {
                    s->left->color = BLACK;
                }
                rotateRight(x->parent);
                x = root;
            }
        }
    }

    if (x != nullptr) {
        x->color = BLACK;
    }
}


void RedBlackTree::rbTransplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

Node* RedBlackTree::minimum(Node *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


void printHelper(Node* node, string indent, bool isLast) {

    if (node == nullptr) {
        return;
    }

    cout << indent;

    if (isLast) {
        cout << "R----";
        indent += "     ";
    } else {
        cout << "L----";
        indent += "|    ";
    }

    string color = node->color == RED ? "RED" : "BLACK";
    cout << node->data << "(" << color << ")" << endl;

    printHelper(node->left, indent, false);
    printHelper(node->right, indent, true);
}

void RedBlackTree::printTree() {
    printHelper(root, "", true);
}


void handleInvalidInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input, please enter a valid number.\n";
}

int main() {
    RedBlackTree rbt;
    int choice, data;

    while (true) {
        cout << "\nRed-Black Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number!\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                if (cin.fail()) {
                    handleInvalidInput();
                    continue;
                }
                rbt.insert(data);
                break;
            case 2:
                cout << "Enter data to delete: ";
                cin >> data;
                if (cin.fail()) {
                    handleInvalidInput();
                    continue;
                }
                rbt.deleteNode(data);
                break;
            case 3:
                cout << "Enter data to search: ";
                cin >> data;
                if (cin.fail()) {
                    handleInvalidInput();
                    continue;
                }
                if (rbt.search(data) != nullptr) {
                    cout << "Data found in the tree.\n";
                } else {
                    cout << "Data not found in the tree.\n";
                }
                break;
            case 4:
                cout << "Red-Black Tree:\n";
                rbt.printTree();
                break;
            case 5:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice, please try again!\n";
        }
    }

    return 0;
}


