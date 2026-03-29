#include<iostream>
#include<string>
struct TreeNode{
    std::string val;
    TreeNode* left;
    TreeNode* right;
};
int evaluateTree(TreeNode* root){
    if(root==nullptr)return 0;
    if(root->left==nullptr && root->right==nullptr)return std::stoi(root->val);
    int l=evaluateTree(root->left);    
    int r=evaluateTree(root->right);
    if(root->val=="+") return l+r;
    if(root->val=="-") return l-r;
    if(root->val=="*") return l*r;
    if(root->val=="/"){
        if(r==0){
            std::cout<<"Error!\n";
            return 0;
        }
        else return l/r;
    }
}
std::string decodeString(const std::string &s,int &index){
    int mul=1;
    std::string res = "";
    while(index<s.size()){
        while((s[index]>='0' && s[index]<='9') || (s[index]>='a' && s[index]<='z')){
            if ((s[index]>='0' && s[index]<='9'))
                mul=s[index]-'0',index++;
            else if(s[index]>='a' && s[index]<='z'){
                for(int i=1;i<=mul;i++)
                    res=res+s[index];
                index++;    
            }
        }
        if(s[index]=='['){
            index++;
            std::string p=decodeString(s,index);
            for(int i=1;i<=mul;i++)
            res=res+p;
            mul=1;
        }
        if(s[index]==']'){
            index++;
            return res;
        }
    }
    return res;
}
int main(){
    std::string s;
    int index=0;
    std::cin>>s;
    std::cout<<decodeString(s,index);
}