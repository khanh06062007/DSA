#include <iostream>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
};

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

TreeNode* buildTree(ifstream& infile) {
    string token;
    if (!(infile >> token)) {
        return nullptr;
    }

    TreeNode* node = new TreeNode;
    node->val = token;
    node->left = nullptr;
    node->right = nullptr;

    if (isOperator(token)) {
        node->left = buildTree(infile);
        node->right = buildTree(infile);
    }

    return node;
}

// --- YOUR CODE HERE ---
int evaluateTreeIterative(TreeNode* root) {
    if(root==nullptr)return 0;
    std::stack<TreeNode*>tree;
    std::stack<int>st;
    TreeNode* lastVisited = nullptr;
    TreeNode* cur = root;
    while(!tree.empty() || cur != nullptr){
        if (cur != nullptr) {
            tree.push(cur);
            cur = cur->left;
        }
        else {
            TreeNode* peekNode = tree.top();
            if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                cur = peekNode->right;
            } 
            else {
                if (peekNode->left == nullptr && peekNode->right == nullptr) {
                    st.push(stoi(peekNode->val));
                } else {
                    int rightVal = st.top(); st.pop();
                    int leftVal = st.top(); st.pop();
                    if (peekNode->val == "+") st.push(leftVal + rightVal);
                    else if (peekNode->val == "-") st.push(leftVal - rightVal);
                    else if (peekNode->val == "*") st.push(leftVal * rightVal);
                    else if (peekNode->val == "/") {
                        if (rightVal == 0) {
                            std::cout << "Error: Division by zero!\n";
                            st.push(0);
                        } else st.push(leftVal / rightVal);
                    }
                }
                lastVisited = peekNode;
                tree.pop();
            }
        }
    }
    return st.top();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./main.exe <input_file_path> <output_file_path>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    if (!infile.is_open()) {
        cout << "Error: Cannot open input file " << argv[1] << endl;
        return 1;
    }
    if (!outfile.is_open()) {
        cout << "Error: Cannot open output file " << argv[2] << endl;
        return 1;
    }

    TreeNode* root = buildTree(infile);
    int result = evaluateTreeIterative(root);

    outfile << result << endl;
    
    infile.close();
    outfile.close();

    return 0;
}