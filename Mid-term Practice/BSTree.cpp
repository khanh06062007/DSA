#include<iostream>
#include<queue>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};
Node* SearchOnBST(Node* root, int target){
    Node *p = root;
    while(!p){
        if(p->val == target)
            return p;
        else if(p->val > target)
            p = p->left;
        else
            p = p->right;
    }
    return nullptr;
}
void InsertNodeOnBST(Node*& root, int val){
    if(!root){
        root = new Node(val);
        return;
    }
    if(val < root->val)
        InsertNodeOnBST(root->left, val);
    else if (val > root->val) 
        InsertNodeOnBST(root->right, val); 
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
}
bool check(Node *root, long long minval, long long maxval){
        if(!root) return true;
        if (root->val <= minval || root->val >= maxval) {
            return false; 
        }
        bool l = check(root->left, minval, root->val);
        bool r = check(root->right, root->val, maxval);
        return (l && r);
    }
bool isValidBST(Node* root) {
        return check(root, -2147483649LL, 2147483648LL);
}
void RTL(Node* root, int& k,int &count){
    if(!root || k<=0)
        return;
    RTL(root->right, k, count);
    k--;
    if(k==0){
        count = root->val;
        return;
    }
    RTL(root->left, k, count);
}

int kthLargest(Node* root, int k){
    int count = -1;
    RTL(root, k, count);
    return count;
}
Node* trimBST(Node* root, int low, int high) {
        if(!root)return nullptr;
        if(root->val < low){
            Node* right=trimBST(root->right,low,high);
            return right;
        }
        if(root->val > high){
            Node* left=trimBST(root->left,low,high);
            return left;
        }
        root->left=trimBST(root->left,low,high);
        root->right=trimBST(root->right,low,high);
        return root;
}
Node** splitBST(Node* root, int target){
    Node **res = new Node *[2];
    res[0] = res[1] = nullptr;
    if (!root)
        return nullptr;
    if(root->val <= target){
        Node **right = splitBST(root->right, target);
        root->right = right[0];
        res[0] = root;
        res[1] = right[1];
        delete[] right;
    }else{
        Node **left = splitBST(root->left, target);
        root->left = left[1];
        res[1] = root;
        res[0] = left[0];
        delete[] left;
    }
    return res;
}
void LTRInorder(Node* root,vector<int>&a){
        if(!root)return;
        LTRInorder(root->left,a);
        a.push_back(root->val);
        LTRInorder(root->right,a);
        return;
}
int main(){
    int n, target;
    cin >> n >> target;
    int *a = new int[n];
    Node *root = nullptr;
    for (int i = 0; i < n; i++)
        cin >> a[i], InsertNodeOnBST(root, a[i]);
    cout << findMin(root)->val << '\n';
    cout << findMax(root)->val << '\n';
    cout << kthLargest(root, 3) << '\n';
    vector<int> v;
    LTRInorder(root,v);
    for(auto x:v){
        cout << x << " ";
    }
}