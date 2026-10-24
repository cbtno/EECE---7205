// case3_modified_q2_q3.cpp - Case 3 Questions 2 and 3: delete 35, then 55, from tree P
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

// Delete a node with ONE child (rule B4), remembering its parent (rule B1)
void deleteOneChild(Node* root, int key)
{
    // 1. search for key, remembering its parent
    Node* parent = nullptr;
    Node* cur = root;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 2. its only child takes its place
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent->left == cur) parent->left = child;    // Q3: 65->left = 60
    else                     parent->right = child;   // Q2: 25->right = 30
    delete cur;
}

int main()
{
    // Question 2: delete 35 from tree P
    Node* root = buildP();
    show("Before", root);
    deleteOneChild(root, 35);
    show("After (delete 35)", root);
    freeTree(root);

    // Question 3: start again from the original P and delete 55
    root = buildP();
    deleteOneChild(root, 55);
    show("After (delete 55)", root);
    freeTree(root);
    return 0;
}