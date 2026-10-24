// case1_original_Q1_Q2.cpp - delete the root (40) of tree T using the inorder successor
#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Inorder (Left, Node, Right) prints a BST in sorted order
void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

// Preorder (Node, Left, Right) shows the shape of the tree
void printPreorder(Node* node)
{
    if (node == nullptr) return;
    cout << node->data << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

// Free every node (postorder: children before parent)
void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

// Usual BST insert (iterative, remembers the parent)
Node* insert(Node* root, int key)
{
    Node* n = new Node(key);
    if (root == nullptr) return n;
    Node* parent = nullptr;
    Node* cur = root;
    while (cur != nullptr)
    {
        parent = cur;
        cur = (key < cur->data) ? cur->left : cur->right;
    }
    if (key < parent->data) parent->left = n;
    else                    parent->right = n;
    return root;
}

Node* build(const vector<int>& keys)
{
    Node* root = nullptr;
    for (int k : keys) root = insert(root, k);
    return root;
}

// Tree T: 40 20 60 10 30 50 70
Node* buildT() { return build({40, 20, 60, 10, 30, 50, 70}); }
// Tree P: 45 25 65 15 35 55 75 30 60
Node* buildP() { return build({45, 25, 65, 15, 35, 55, 75, 30, 60}); }

// Height in edges (empty tree = -1, single node = 0)
int height(Node* node)
{
    if (node == nullptr) return -1;
    int l = height(node->left), r = height(node->right);
    return 1 + (l > r ? l : r);
}

void show(const char* label, Node* root)
{
    cout << label << ": ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
}

int main()
{
    Node* root = buildT();
    show("Before", root);

    // Case 1: delete the root (40). It has two children.
    // 1. find the inorder successor: the smallest value in the right subtree
    Node* parent = root;
    Node* succ = root->right;               // go right once (60)
    while (succ->left != nullptr)           // then left as far as possible
    {
        parent = succ;
        succ = succ->left;                  // succ = 50, parent = 60
    }
    // 2. copy the successor's value into the root
    root->data = succ->data;                // root now holds 50
    // 3. remove the successor node (it has no left child)
    if (parent == root)
        parent->right = succ->right;
    else
        parent->left = succ->right;         // 60->left = NULL
    delete succ;

    show("After", root);
    cout << "Preorder: ";
    printPreorder(root);
    cout << endl;
    freeTree(root);
    return 0;
}
