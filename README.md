# Red-Black Tree Implementation in C++

## Overview

This is a C++ implementation of a Red-Black Tree data structure. Red-Black Trees are self-balancing binary search trees that maintain balance during insertions and deletions, ensuring efficient tree operations.

A Red-Black Tree satisfies the following properties:

1. Each node is either RED or BLACK.
2. The root is always BLACK.
3. Every leaf (NIL) is BLACK.
4. If a node is RED, both its children are BLACK.
5. Every simple path from a node to its descendant leaves must have the same number of BLACK nodes.

## Contents

- [Red-Black Tree Implementation in C++](#red-black-tree-implementation-in-c)
  - [Overview](#overview)
  - [Contents](#contents)
  - [Usage](#usage)
  - [Compilation and Execution](#compilation-and-execution)
  - [Methods and Operations](#methods-and-operations)
  - [Example Usage](#example-usage)
  - [Contributing](#contributing)
  - [License](#license)

## Usage

To use this Red-Black Tree implementation, follow these steps:

1. Include the necessary header files at the beginning of your C++ code:

```cpp
#include <iostream>
#include <vector>
#include <limits>
using namespace std;
```

2. Define the `Color` enumeration and the `Node` struct for your Red-Black Tree. Each node has an integer data value and a color (either RED or BLACK), as well as pointers to its left child, right child, and parent node.

```cpp
enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
```

3. Define the `RedBlackTree` class, which contains the root of the Red-Black Tree and various methods for tree operations such as insertion, deletion, searching, and printing.

```cpp
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
```

4. Implement the methods for insertion, deletion, rotations, and balancing of the Red-Black Tree in the `RedBlackTree` class.

5. Implement a helper function `printHelper` to print the Red-Black Tree structure.

6. In the `main()` function, you can create a Red-Black Tree object, and use it to perform various operations such as insertion, deletion, searching, and printing.

```cpp
int main() {
    RedBlackTree rbt;
    int choice, data;

    // Loop for menu-based user interaction
    while (true) {
        // Display menu options
        cout << "\nRed-Black Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input
        if (cin.fail()) {
            handleInvalidInput();
            continue;
        }

        // Perform the chosen operation
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
```

## Compilation and Execution

Compile your C++ code containing this Red-Black Tree implementation using a C++ compiler (e.g., g++) and run the resulting executable. Follow the on-screen menu to perform various Red-Black Tree operations.

Please note that this code is a standalone implementation, and you can integrate it into your projects as needed.

## Methods and Operations

This Red-Black Tree implementation provides the following methods and operations:

- `insert(const int &n)`: Inserts a node with the given data into the Red-Black Tree while maintaining the tree's properties.
- `deleteNode(const int &data)`: Deletes a node with the given data from the Red-Black Tree while ensuring the tree remains a valid Red-Black Tree.
- `search(int n)`: Searches for a node with the specified data and returns a pointer to the node if found; otherwise, returns nullptr.
- `printTree()`: Prints the structure of the Red-Black Tree to visualize its hierarchy and colors.

## Example Usage

Here's an example of how to use this Red-Black Tree implementation:

```cpp
RedBlackTree rbt;

// Insert nodes
rbt.insert(10);
rbt.insert(20);
rbt.insert(30);

// Search for a node
Node* foundNode = rbt.search(20);
if (foundNode != nullptr) {
    cout << "Node with data 20 found in the tree." << endl;
}

// Delete a node
rbt.deleteNode(20);
```

## Contributing

If you'd like to contribute to this project or report issues, please open an issue or submit a pull request on the GitHub repository: [https://github.com/123456Arshia/Red-Black](https://github.com/123456Arshia/Red-Black)

## License

This Red-Black Tree implementation is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Feel free to modify and use this code in your projects, and make sure to include the appropriate attribution.
