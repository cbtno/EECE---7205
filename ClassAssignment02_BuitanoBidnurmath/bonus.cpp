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
 
// Inorder (Left, Node, Right) prints a BST in sorted order
void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}
 
// Free every node (postorder: children before parent)
void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
 
// Deletes key from the BST and returns the (possibly new) root.
// Handles: empty tree / not found (B2), leaf (B3), one child (B4),
// two children (B5) and the root (B6). Time: O(h).
Node* deleteNode(Node* root, int key)
{
    // B1: search, remembering the parent
    Node* parent = nullptr;
    Node* cur = root;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
 
    // B2: not found (also covers the empty tree)
    if (cur == nullptr)
    {
        cout << key << " is not in the tree: nothing to delete" << endl;
        return root;
    }
 
    // B5: two children -> copy the inorder successor, then remove it
    if (cur->left != nullptr && cur->right != nullptr)
    {
        Node* succParent = cur;
        Node* succ = cur->right;
        while (succ->left != nullptr)
        {
            succParent = succ;
            succ = succ->left;
        }
        cur->data = succ->data;
        if (succParent == cur) succParent->right = succ->right;
        else                   succParent->left = succ->right;
        delete succ;
        return root;
    }
 
    // B3 / B4: zero or one child -> the child (or NULL) takes cur's place
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent == nullptr)          root = child;            // B6: root changes
    else if (parent->left == cur)   parent->left = child;
    else                            parent->right = child;
    delete cur;
    return root;
}
 
void show(const char* label, Node* root)
{
    cout << label;
    printInorder(root);
    if (root != nullptr) cout << "  (root = " << root->data << ")";
    else                 cout << "  (tree is empty)";
    cout << endl;
}
 
int main()
{
    // build tree T
    Node* root = new Node(40);
    root->left = new Node(20);
    root->right = new Node(60);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(50);
    root->right->right = new Node(70);
 
    show("Before:       ", root);
 
    root = deleteNode(root, 40);
    show("Delete 40:    ", root);
 
    root = deleteNode(root, 10);
    show("Delete 10:    ", root);
 
    root = deleteNode(root, 60);
    show("Delete 60:    ", root);
 
    root = deleteNode(root, 25);
    show("Delete 25:    ", root);
 
    freeTree(root);
    return 0;
}