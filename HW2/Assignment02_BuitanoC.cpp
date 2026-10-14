#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <unordered_map>
#include <algorithm>
using namespace std;

// one node in the tree: a value and pointers to the left and right child
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

const int NONE = INT_MIN;  // marks an empty spot in a level order array

// Builds a tree from a level order array
// Index i has children 2i + 1 and 2i + 2
Node* buildFromArray(const vector<int>& arr, int i = 0) {
    // past the end of the array or an empty spot means no node here
    if (i >= (int)arr.size() || arr[i] == NONE) return nullptr;
    Node* node = new Node(arr[i]);
    node->left = buildFromArray(arr, 2 * i + 1);   // build the left side
    node->right = buildFromArray(arr, 2 * i + 2);  // build the right side
    return node;
}

// returns the values level by level, left to right
vector<int> levelOrder(Node* root) {
    vector<int> out;
    if (root == nullptr) return out;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();   // take the next node out
        out.push_back(node->value);
        if (node->left) q.push(node->left);    // add its children to the line
        if (node->right) q.push(node->right);
    }
    return out;
}

// left side, then the node, then right side
void inorder(Node* node, vector<int>& out) {
    if (node == nullptr) return;
    inorder(node->left, out);
    out.push_back(node->value);
    inorder(node->right, out);
}

// left side, then right side, then the node
void postorder(Node* node, vector<int>& out) {
    if (node == nullptr) return;
    postorder(node->left, out);
    postorder(node->right, out);
    out.push_back(node->value);
}
// Reads a tree from the terminal in level order. N means an empty spot.
Node* readTree() {
    int count;
    cout << "Enter number of level order entries (0 for an empty tree): ";
    cin >> count;
    // keep asking if the count is negative
    while (count < 0) {
        cout << "Count cannot be negative. Enter number of entries: ";
        cin >> count;
    }
    vector<int> arr(count);
    if (count > 0) cout << "Enter " << count << " values in level order (N for an empty spot): ";
    for (int i = 0; i < count; i++) {
        string token;
        cin >> token;
        // N becomes an empty spot, anything else becomes a number
        arr[i] = (token == "N" || token == "n") ? NONE : stoi(token);
    }
    return buildFromArray(arr);
}

// prints the values with spaces, or (empty) if there are none
void printList(const vector<int>& values) {
    if (values.empty()) { cout << "(empty)"; return; }
    for (int v : values) cout << v << " ";
}

// Problem 1
int maxDepth(Node* node) {
    if (node == nullptr) return -1;              // empty tree has depth -1
    int leftDepth = maxDepth(node->left);        // depth of the left side
    int rightDepth = maxDepth(node->right);      // depth of the right side
    return 1 + max(leftDepth, rightDepth);       // one edge down to the deeper side
}
void runProblem1() {
    Node* root = readTree();
    cout << "Maximum depth: " << maxDepth(root) << endl;
}

// Problem 2
// recursive version: this node's value plus both sides
int sumRecursive(Node* node) {
    if (node == nullptr) return 0;               // empty tree adds nothing
    int leftSum = sumRecursive(node->left);
    int rightSum = sumRecursive(node->right);
    return node->value + leftSum + rightSum;
}

// queue version: go level by level and keep a running total
int sumLevel(Node* root) {
    if (root == nullptr) return 0;
    int total = 0;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        total += node->value;                    // add this node to the total
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
    return total;
}
void runProblem2() {
    Node* root = readTree();
    cout << "Sum (recursive): " << sumRecursive(root) << endl;
    cout << "Sum (queue, level order): " << sumLevel(root) << endl;
}

// Problem 3
// INSERT from the lecture: put the new node in the first open spot in level order
Node* insertLevel(Node* root, int value) {
    Node* fresh = new Node(value);
    if (root == nullptr) return fresh;           // empty tree, new node is the root
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        // first empty child spot we find gets the new node
        if (node->left == nullptr) { node->left = fresh; return root; }
        q.push(node->left);
        if (node->right == nullptr) { node->right = fresh; return root; }
        q.push(node->right);
    }
    return root;
}

int countOneChild(Node* node) {
    if (node == nullptr) return 0;
    int leftCount = countOneChild(node->left);
    int rightCount = countOneChild(node->right);
    // true when one child is missing and the other one is there
    if ((node->left == nullptr) != (node->right == nullptr)) {
        return leftCount + rightCount + 1;       // count this node too
    }
    return leftCount + rightCount;
}
void runProblem3() {
    Node* root = readTree();
    string token;
    cout << "Enter the value to INSERT (N to skip the insert): ";
    cin >> token;
    // only insert if the user typed a number
    if (token != "N" && token != "n") root = insertLevel(root, stoi(token));
    cout << "Level order: "; printList(levelOrder(root)); cout << endl;
    cout << "Nodes with exactly one child: " << countOneChild(root) << endl;
}

// Problem 4
bool identical(Node* a, Node* b) {
    if (a == nullptr && b == nullptr) return true;   // both empty, same shape
    if (a == nullptr || b == nullptr) return false;  // only one empty, different shape
    if (a->value != b->value) return false;          // values don't match
    if (!identical(a->left, b->left)) return false;  // left sides don't match, stop early
    return identical(a->right, b->right);            // answer comes from the right sides
}
void runProblem4() {
    cout << "Tree A" << endl;
    Node* a = readTree();
    cout << "Tree B" << endl;
    Node* b = readTree();
    cout << "IDENTICAL(A, B) = " << (identical(a, b) ? "true" : "false") << endl;
}

// Problem 5
int minValue(Node* node) {
    if (node == nullptr) return INT_MAX;  // plays the role of +infinity
    int leftMin = minValue(node->left);
    int rightMin = minValue(node->right);
    return min({node->value, leftMin, rightMin});    // smallest of the three
}

// Twist: in a BST the minimum is the leftmost node
int bstMin(Node* root) {
    Node* node = root;
    while (node->left != nullptr) node = node->left; // keep going left
    return node->value;
}
void runProblem5() {
    Node* root = readTree();
    // the tree needs at least one node to have a minimum
    while (root == nullptr) {
        cout << "The tree must have at least one node." << endl;
        root = readTree();
    }
    cout << "Minimum value: " << minValue(root) << endl;
    cout << "Leftmost node (the minimum only if the tree is a BST): " << bstMin(root) << endl;
}

// Problem 6
Node* invertTree(Node* node) {
    if (node == nullptr) return nullptr;
    // swap the two children
    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
    // then flip both sides the same way
    invertTree(node->left);
    invertTree(node->right);
    return node;
}
void runProblem6() {
    Node* root = readTree();
    vector<int> before;
    inorder(root, before);                       // save inorder before flipping
    root = invertTree(root);
    vector<int> after;
    inorder(root, after);                        // inorder after flipping
    cout << "Level order after inverting: "; printList(levelOrder(root)); cout << endl;
    cout << "Inorder before: "; printList(before); cout << endl;
    cout << "Inorder after:  "; printList(after); cout << endl;
}

// Problem 7
vector<int> levelsAndRightView(Node* root) {
    vector<int> rightView;
    if (root == nullptr) return rightView;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = (int)q.size();                // number of nodes on this level
        for (int i = 1; i <= size; i++) {
            Node* node = q.front(); q.pop();
            cout << node->value << " ";
            if (i == size) rightView.push_back(node->value);  // last node on the level
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        cout << endl;                            // new line after each level
    }
    return rightView;
}
void runProblem7() {
    Node* root = readTree();
    cout << "Levels:" << endl;
    vector<int> view = levelsAndRightView(root);
    cout << "Right side view: "; printList(view); cout << endl;
}

// Problem 8
vector<int> zigzag(Node* root) {
    vector<int> out;
    if (root == nullptr) return out;
    stack<Node*> current, next;                  // current level and the next level
    current.push(root);
    bool leftToRight = true;
    while (!current.empty()) {
        Node* node = current.top(); current.pop();
        out.push_back(node->value);
        // the push order decides which way the next level comes out
        if (leftToRight) {
            if (node->left != nullptr) next.push(node->left);
            if (node->right != nullptr) next.push(node->right);
        } else {
            if (node->right != nullptr) next.push(node->right);
            if (node->left != nullptr) next.push(node->left);
        }
        // level is done, switch stacks and flip the direction
        if (current.empty()) {
            swap(current, next);
            leftToRight = !leftToRight;
        }
    }
    return out;
}
void runProblem8() {
    Node* root = readTree();
    cout << "Zigzag order: "; printList(zigzag(root)); cout << endl;
}

// Problem 9
bool isComplete(Node* root) {
    if (root == nullptr) return true;
    queue<Node*> q;
    q.push(root);
    bool seenNull = false;                       // have we hit an empty spot yet
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        if (node == nullptr) {
            seenNull = true;
        } else {
            if (seenNull) return false;          // real node after a gap, not complete
            q.push(node->left);                  // push children even if they are empty
            q.push(node->right);
        }
    }
    return true;
}
void runProblem9() {
    Node* root = readTree();
    cout << "COMPLETE = " << (isComplete(root) ? "true" : "false") << endl;
}

// Problem 10
Node* lca(Node* node, int a, int b) {
    if (node == nullptr) return nullptr;
    if (node->value == a || node->value == b) return node;  // found one of them
    Node* leftResult = lca(node->left, a, b);
    Node* rightResult = lca(node->right, a, b);
    if (leftResult != nullptr && rightResult != nullptr) return node;  // one on each side
    if (leftResult != nullptr) return leftResult;  // both are on the left
    return rightResult;                            // both are on the right (or neither)
}
void runProblem10() {
    Node* root = readTree();
    int a, b;
    cout << "Enter the two values a and b: ";
    cin >> a >> b;
    Node* answer = lca(root, a, b);
    if (answer == nullptr) cout << "Neither value is in the tree." << endl;
    else cout << "LCA(" << a << ", " << b << ") = " << answer->value << endl;
}

// Problem 11
Node* buildRange(const vector<int>& pre, unordered_map<int, int>& index,
                 int& preIdx, int lo, int hi) {
    if (lo > hi) return nullptr;                 // nothing left in this range
    int rootValue = pre[preIdx];                 // next preorder value is the root
    preIdx++;
    Node* node = new Node(rootValue);
    int m = index[rootValue];                    // where the root is in inorder
    node->left = buildRange(pre, index, preIdx, lo, m - 1);   // everything left of it
    node->right = buildRange(pre, index, preIdx, m + 1, hi);  // everything right of it
    return node;
}

Node* buildTree(const vector<int>& pre, const vector<int>& in) {
    int n = (int)in.size();
    // lookup table: value -> position in the inorder list
    unordered_map<int, int> index;
    for (int i = 0; i < n; i++) index[in[i]] = i;
    int preIdx = 0;
    return buildRange(pre, index, preIdx, 0, n - 1);
}
void runProblem11() {
    int n;
    cout << "Enter number of values: ";
    cin >> n;
    while (n < 0) {
        cout << "Number of values cannot be negative. Enter number of values: ";
        cin >> n;
    }
    vector<int> pre(n), in(n);
    cout << "Enter the preorder list: ";
    for (int i = 0; i < n; i++) cin >> pre[i];
    cout << "Enter the inorder list: ";
    for (int i = 0; i < n; i++) cin >> in[i];
    Node* root = buildTree(pre, in);
    vector<int> post;
    postorder(root, post);                       // used to check the rebuilt tree
    cout << "Level order: "; printList(levelOrder(root)); cout << endl;
    cout << "Postorder:   "; printList(post); cout << endl;
}

// Problem 12
// returns the height and keeps the longest path seen so far in best
int heightAndDiameter(Node* node, int& best) {
    if (node == nullptr) return -1;
    int lh = heightAndDiameter(node->left, best);
    int rh = heightAndDiameter(node->right, best);
    best = max(best, lh + rh + 2);               // longest path that bends at this node
    return 1 + max(lh, rh);                      // height of this node
}

int diameter(Node* root) {
    int best = 0;
    heightAndDiameter(root, best);
    return best;
}
void runProblem12() {
    Node* root = readTree();
    cout << "Diameter: " << diameter(root) << endl;
}

// Problem 13
void serialize(Node* node, vector<string>& list) {
    if (node == nullptr) {
        list.push_back("N");                     // N marks an empty child
        return;
    }
    list.push_back(to_string(node->value));      // node first (preorder)
    serialize(node->left, list);
    serialize(node->right, list);
}

Node* deserialize(const vector<string>& list, int& pos) {
    string item = list[pos];                     // read the next item
    pos++;
    if (item == "N") return nullptr;
    Node* node = new Node(stoi(item));
    node->left = deserialize(list, pos);         // rebuild in the same order
    node->right = deserialize(list, pos);
    return node;
}
void runProblem13() {
    Node* root = readTree();
    vector<string> list;
    serialize(root, list);
    cout << "SERIALIZE: ";
    for (const string& item : list) cout << item << " ";
    cout << "(" << list.size() << " items)" << endl;
    int pos = 0;
    Node* rebuilt = deserialize(list, pos);
    cout << "DESERIALIZE level order: "; printList(levelOrder(rebuilt)); cout << endl;
}

// Problem 14
// long long bounds stand in for -infinity and +infinity
bool isBST(Node* node, long long low, long long high) {
    if (node == nullptr) return true;
    if (node->value <= low || node->value >= high) return false;  // outside the allowed range
    if (!isBST(node->left, low, node->value)) return false;       // left side must be smaller
    return isBST(node->right, node->value, high);                 // right side must be bigger
}

// Twist: inorder version, prev starts at -infinity
bool isBSTInorder(Node* node, long long& prev) {
    if (node == nullptr) return true;
    if (!isBSTInorder(node->left, prev)) return false;
    if (node->value <= prev) return false;       // values have to keep going up
    prev = node->value;
    return isBSTInorder(node->right, prev);
}
void runProblem14() {
    Node* root = readTree();
    long long prev = LLONG_MIN;
    cout << "ISBST (range method): " << (isBST(root, LLONG_MIN, LLONG_MAX) ? "true" : "false") << endl;
    cout << "ISBST (inorder method): " << (isBSTInorder(root, prev) ? "true" : "false") << endl;
}

// Problem 15
void verticalOrder(Node* root) {
    if (root == nullptr) return;
    unordered_map<int, vector<int>> cols;        // distance -> values in that column
    queue<pair<Node*, int>> q;                   // each node with its distance
    q.push({root, 0});
    int minD = 0, maxD = 0;
    while (!q.empty()) {
        Node* node = q.front().first;
        int d = q.front().second;
        q.pop();
        cols[d].push_back(node->value);          // put the value in its column
        minD = min(minD, d);                     // remember the leftmost column
        maxD = max(maxD, d);                     // remember the rightmost column
        if (node->left != nullptr) q.push({node->left, d - 1});    // left is one less
        if (node->right != nullptr) q.push({node->right, d + 1});  // right is one more
    }
    // print the columns from left to right
    for (int d = minD; d <= maxD; d++) {
        cout << "distance " << d << ":";
        for (int v : cols[d]) cout << " " << v;
        cout << endl;
    }
}
void runProblem15() {
    Node* root = readTree();
    cout << "Vertical order:" << endl;
    verticalOrder(root);
}

int main() {
    int choice;
    cout << "Binary Tree Interview Questions" << endl;
    cout << "Enter a question number (1-15), or 0 to quit: ";
    // keep running until the user types 0
    while (cin >> choice && choice != 0) {
        switch (choice) {
            case 1: runProblem1(); break;
            case 2: runProblem2(); break;
            case 3: runProblem3(); break;
            case 4: runProblem4(); break;
            case 5: runProblem5(); break;
            case 6: runProblem6(); break;
            case 7: runProblem7(); break;
            case 8: runProblem8(); break;
            case 9: runProblem9(); break;
            case 10: runProblem10(); break;
            case 11: runProblem11(); break;
            case 12: runProblem12(); break;
            case 13: runProblem13(); break;
            case 14: runProblem14(); break;
            case 15: runProblem15(); break;
            default: cout << "Please choose a number from 1 to 15." << endl;
        }
        cout << endl << "Enter a question number (1-15), or 0 to quit: ";
    }
    return 0;
}