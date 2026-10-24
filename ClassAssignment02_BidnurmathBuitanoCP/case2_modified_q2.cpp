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
 
    // Case 2 (Q2): delete the leaf 70.
    Node* parent = nullptr;
    Node* cur = root;
    int key = 70;                          // CHANGED
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 70 is 60's right child, so 60->right = NULL
    if (parent->left == cur) parent->left = nullptr;
    else                     parent->right = nullptr;
    delete cur;
 
    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
 
    freeTree(root);
    return 0;
}
 