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
    // CHANGED: tree from inserting 10, 20, 30
    Node* root = nullptr;
    int keys[] = {10, 20, 30};
    for (int k : keys) root = insert(root, k);
 
    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
 
    // Case 3 (Q4): delete the root 10 (one child, 20).
    Node* parent = nullptr;
    Node* cur = root;
    int key = 10;                          // CHANGED
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;   // 20
    if (parent == nullptr)                 // CHANGED (B6): cur is the root
        root = child;                      // CHANGED: root pointer itself moves to 20
    else if (parent->left == cur) parent->left = child;
    else                          parent->right = child;
    delete cur;
 
    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
 
    freeTree(root);
    return 0;
}
 