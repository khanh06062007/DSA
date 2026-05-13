#include<iostream>
#include<queue>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
};

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
