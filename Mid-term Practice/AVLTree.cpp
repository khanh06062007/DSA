#include<iostream>
#include<queue>
using namespace std;
struct Node {
    int val;
    int height;
    Node* left;
    Node* right;
    Node(int val) : val(val), height(1), left(nullptr), right(nullptr) {}
};
int getHeight(Node* root){
    if(root==nullptr)
        return 0;
    return root->height;
}
Node* rotateRight(Node* A){
    Node *B = A->left;
    Node *T2 = B->right;
    B->right = A;
    A->left = T2;
    A->height = 1 + max(getHeight(A->left), getHeight(A->right));
    B->height = 1 + max(getHeight(B->left), getHeight(B->right));
    return B; 
}
Node* rotateLeft(Node* A){
    Node *B = A->right;
    Node *T2 = B->left;
    B->left = A;
    A->right = T2;
    A->height = 1 + max(getHeight(A->left), getHeight(A->right));
    B->height = 1 + max(getHeight(B->left), getHeight(B->right));
    return B; 
}
int getBalance(Node* root) {
    if (root == nullptr) return 0;
    return getHeight(root->left) - getHeight(root->right);
}
Node* balanceNode(Node* root) {
    if (root == nullptr) return nullptr;
    int bf = getBalance(root);
    // 1. Kịch bản LL
    if (bf > 1 && getBalance(root->left) >= 0)
    return rotateRight(root);

    // 2. Kịch bản RR
    if (bf < -1 && getBalance(root->right) <= 0)
    return rotateLeft(root);
    // 3. Kịch bản LR
    if (bf > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left); // Nắn thẳng
        return rotateRight(root); // Cân bằng
    }
    // 4. Kịch bản RL
    if (bf < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right); // Nắn thẳng
        return rotateLeft(root); // Cân bằng
    }
    return root; // Nếu -1 <= bf <= 1, không cần xoay
}
void InsertNodeOnAVLT(Node*& root, int val){
    if(!root){
        root = new Node(val);
        return;
    }
    if(val < root->val)
        InsertNodeOnAVLT(root->left, val);
    else if (val > root->val) 
        InsertNodeOnAVLT(root->right, val);
    else
        return;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root = balanceNode(root);
}
Node* findMin(Node* root){
    if(!root)
        return nullptr;
    while(root->left){
        //cout << root->val << '\n';
        root = root->left;
    }
    return root;
}
Node* findMax(Node* root){
    if(!root)
        return nullptr;
    while(root->right)
        root = root->right;
    return root;
}
void deleteNode(Node*& root, int key){
    if(!root)
        return;
    if(key<root->val)
        deleteNode(root->left, key);
    else if(key>root->val)
        deleteNode(root->right, key);
    else{
        if(!root->left){
            Node *p = root;
            root = p->right;
            delete p;
        }
        else if(!root->right){
            Node *p = root;
            root = p->left;
            delete p;
        }
        else{
            Node *p = findMax(root->left);
            root->val = p->val;
            deleteNode(root->left, p->val);
           }
    }
    if(!root)
        return;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root = balanceNode(root);
}
