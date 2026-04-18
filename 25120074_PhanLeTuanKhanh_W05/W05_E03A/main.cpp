#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
};

void findKth(Node *root, int &k, int &count){
    if (!root || k <= 0)
        return;
    findKth(root->right, k, count);
    k--;
    if (k == 0){
        count = root->val;
        return;
    }
    findKth(root->left, k, count);
}

int kthLargest(Node* root, int k){
    int count = -1;
    findKth(root, k, count);
    return count;
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

    int k;
    infile >> k;

    Node* root = buildTreeByIndex(tokens, n, 0);
    outfile << kthLargest(root, k) << "\n";

    delete[] tokens;
    infile.close();
    outfile.close();
    return 0;
}
