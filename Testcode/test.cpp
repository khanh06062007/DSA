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
    if(!root)
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
int getBalance(Node* root){
    if(!root)
        return 0;
    return (getHeight(root->left) - getHeight(root->right));
}
Node* nodeBalance(Node* root){
    if(!root)
        return nullptr;
    int bf = getBalance(root);
    if(bf>1 && getBalance(root->left)>=0)
        return rotateRight(root);
    if(bf<-1 && getBalance(root->right)<=0)
        return rotateLeft(root);
    if(bf>1 && getBalance(root->left)<0){
        root->left=rotateLeft(root->left);
        return rotateRight(root);
    }
    if(bf<-1 && getBalance(root->right)>0){
        root->right=rotateRight(root->left);
        return rotateLeft(root);
    }
    return root;
}
void insertNode(Node *root, int val){
    if(!root){
        root = new Node(val);
        return;
    }
    if(root->val > val)
        insertNode(root->left, val);
    else if(root->val < val)
        insertNode(root->right, val);
    else
        return;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root = nodeBalance(root);
    return;
}
Node* getMax(Node* root){
    if(!root)
        return nullptr;
    Node *p = root;
    while(p->right)
        p = p->right;
    return p;
}
void deleteNode(Node *root, int val){
    if(!root)
        return;
    if(val < root->val)
        deleteNode(root->left, val);
    else if(val > root->val)
        deleteNode(root->right, val);
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
            Node *p = getMax(root->left);
            root->val = p->val;
            deleteNode(root->left, p->val);
        }
    }
    if(!root)
        return;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root = nodeBalance(root);
}