#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
};
bool findTarget(Node* root, int target){
    stack<Node*> L, R;
    Node *l = root, *r = root;
    while(true){
        while(l){
            L.push(l);
            l = l->left;
        }   
        while(r){
            R.push(r);
            r = r->right;
        }
        if (L.empty() || R.empty() || L.top() == R.top())
            return false;
        if (L.top()->val + R.top()->val == target)
            return true;
        if (L.top()->val + R.top()->val < target){
            l = L.top()->right;
            L.pop();
        }
        else{
            r = R.top()->left;
            R.pop();
        }
    }
    return false;
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

    int target;
    infile >> target;

    Node* root = buildTreeByIndex(tokens, n, 0);
    outfile << (findTarget(root, target) ? "true" : "false") << "\n";

    delete[] tokens;
    infile.close();
    outfile.close();
    return 0;
}
