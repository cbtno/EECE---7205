// case5_original_Q1.cpp - the key is not in the tree (delete 25 from tree T)
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

    // Case 5: the key is not in the tree (delete 25).
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;    // 25 < 40: go left to 20
        else                 cur = cur->right;   // 25 > 20: go right to 30
    }                                            // 25 < 30: go left, NULL
    if (cur == nullptr)
        cout << key << " is not in the tree: nothing to delete" << endl;

    show("After", root);
    freeTree(root);
    return 0;
}
