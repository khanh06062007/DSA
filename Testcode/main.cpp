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
    stack<TreeNode*> node;
    stack<int>val;
    TreeNode *lastVisited = nullptr;;
    TreeNode *cur = root;
    while(!node.empty() || cur!=nullptr){
        if(!cur){
            node.push(cur);
            cur = cur->left;
        }
        else{
            TreeNode *peekNode = node.top();
            if(peekNode->right && lastVisited!=peekNode->right){
                cur = cur->right;
            }
            else{
                if(!peekNode->left && !peekNode->right)
                    val.push(stoi(peekNode->val));
                else{
                    int l = val.top();
                    val.pop();
                    int r = val.top();
                    val.pop();
                    if(peekNode->val=="+")
                        val.push(l + r);
                    else if(peekNode->val=="-")
                        val.push(l - r);
                    else if(peekNode->val=="*")
                        val.push(l * r);
                    else if(r==0){
                        cout << "Error divided by 0!" << '\n';
                        return -1;
                    }
                    else
                        val.push(l / r);
                }
                lastVisited = peekNode;
                node.pop();
            }
        }
    }
    return val.top();
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