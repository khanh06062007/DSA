#include<iostream>
#include<queue>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
};
int calculateDiameter(Node* root, int& val){
        if(root==nullptr)return 0;

        int l = calculateDiameter(root->left,val);
        int r = calculateDiameter(root->right,val);

        int h = l + r;
        if (h > val)
            val = h;
        return max(l, r) + 1;
    }
int diameterOfBinaryTree(Node* root) {
       int val = 0;
       calculateDiameter(root, val);
       return val;
    }
Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        if(root==nullptr || root == p || root == q)return root;
        Node *l=lowestCommonAncestor(root->left, p, q);
        Node *r=lowestCommonAncestor(root->right, p, q);
        if(l!=nullptr && r!=nullptr)return root;
        return (l!=nullptr?l:r);
    }
bool isCompleteTree(Node* root){
    if(!root)return true;
    queue<Node*> q;
    q.push(root);
    bool check = false;
    while(!q.empty()){
        Node *p = q.back();
        q.pop();
        if(!p){
            check = true;
        }
        else{
            if(check)
                return false;
            q.push(p->left);
            q.push(p->right);
        }
    }
    return true;
}
