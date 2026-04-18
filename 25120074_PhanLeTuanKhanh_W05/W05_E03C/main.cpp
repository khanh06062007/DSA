#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
};

Node* findNode(Node* root, int targetVal){
    if(!root)
        return nullptr;
    if (root->val==targetVal)
        return root;
    Node *l = findNode(root->left, targetVal);
    if(l)
        return l;
    return findNode(root->right, targetVal);
}
void Kdown(Node *root, int distance, int output[],int &idx){
    if(!root)
        return;
    if (distance == 0){
        output[idx++] = root->val;
        return;
    }
    Kdown(root->left, distance - 1, output,idx);
    Kdown(root->right, distance - 1, output,idx);
}
int findDistance(Node* current,Node* target,int k,int output[],int &idx){
    if(!current)
        return -1;
    if(current==target){
        Kdown(target, k, output, idx);
        return 0;
    }
    int d = findDistance(current->left, target, k, output, idx);
    if(d>=0){
        if (d + 1 == k){
            output[idx++] = current->val;
        }
        else{
            Kdown(current->right, k - d - 2, output, idx);
        }
        return d + 1;
    }
    d = findDistance(current->right, target, k, output, idx);
    if(d>=0){
        if (d + 1 == k){
            output[idx++] = current->val;
        }
        else{
            Kdown(current->left, k - d - 2, output, idx);
        }
        return d + 1;
    }
    return -1;
}
void qsort(int output[], int left, int right){
    if(left>=right)
        return;
    int l = left, r = right;
    int mid = output[l + (r - l) / 2];
    while(l<r){
        while(output[l]<mid)
            l++;
        while(output[r]>mid)
            r--;
        if(l<=r){
            swap(output[l], output[r]);
            l++;
            r--;
        }
    }
    qsort(output, left, r);
    qsort(output, l, right);
}
int distanceK(Node* root, Node* target, int k, int output[]){
    if (!root || !target) return 0;
    int idx = 0;
    findDistance(root, target, k, output, idx);
    if(idx>0)
        qsort(output, 0, idx - 1);
    return idx;
}

Node* buildTreeByIndex(string tokens[], int n, int idx) {
    if (idx >= n || tokens[idx] == "null") {
        return nullptr;
    }

    Node* root = new Node{stoi(tokens[idx]), nullptr, nullptr};
    root->left = buildTreeByIndex(tokens, n, idx * 2 + 1);
    root->right = buildTreeByIndex(tokens, n, idx * 2 + 2);
    return root;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./main.exe <input_path> <output_path>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    if (!infile.is_open() || !outfile.is_open()) {
        return 1;
    }

    int n;
    if (!(infile >> n)) {
        return 0;
    }

    string* tokens = new string[n];
    for (int i = 0; i < n; i++) {
        infile >> tokens[i];
    }

    int targetVal;
    int k;
    infile >> targetVal >> k;

    Node* root = buildTreeByIndex(tokens, n, 0);
    Node* targetNode = findNode(root, targetVal);
    int* result = new int[n];
    int count = distanceK(root, targetNode, k, result);

    for (int i = 0; i < count; i++) {
        if (i > 0) {
            outfile << " ";
        }
        outfile << result[i];
    }
    outfile << "\n";

    delete[] result;
    delete[] tokens;
    infile.close();
    outfile.close();
    return 0;
}
