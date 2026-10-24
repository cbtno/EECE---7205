#include <iostream>
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
 
void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}
 
void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
 
Node* insert(Node* root, int value)
{
    if (root == nullptr) return new Node(value);
    if (value < root->data) root->left = insert(root->left, value);
    else                    root->right = insert(root->right, value);
    return root;
}
 
int main()
{
    // Tree T
    Node* root = nullptr;
    int keys[] = {40, 20, 60, 10, 30, 50, 70};
    for (int k : keys) root = insert(root, k);
 
    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
 
    // Case 1 (Q3): delete the root (40) using the inorder PREDECESSOR.
    // 1. find the predecessor: the largest value in the left subtree
    Node* parent = root;
    Node* pred = root->left;               // CHANGED: go left once (20)
    while (pred->right != nullptr)         // CHANGED: then right as far as possible
    {
        parent = pred;
        pred = pred->right;                // pred = 30, parent = 20
    }
    cout << "Predecessor = " << pred->data << ", parent = " << parent->data << endl;
    // 2. copy the predecessor's value into the root
    root->data = pred->data;               // root now holds 30
    // 3. remove the predecessor node (it has no right child)
    if (parent == root)
        parent->left = pred->left;         // CHANGED
    else
        parent->right = pred->left;        // CHANGED: 20->right = NULL
    delete pred;
 
    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
 
    freeTree(root);
    return 0;
}
 