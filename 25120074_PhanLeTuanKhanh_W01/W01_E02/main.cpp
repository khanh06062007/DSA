#include<string>
#include<iostream>
#include"MyStack.h"
using namespace std;
int n;
string s;
MyStack st;
int main(){
    cin>>s;
    n=s.size();
    initStack(st);
    for(int i=0;i<n;i++){
        int k=s[i]-0;
        if(k==40)k--;
        if(k==39 || k==91 || k==123)
            push(st,k);
        else if(st.size>0 && top(st)==k-2)
            pop(st);
        else{
            push(st,k);
            break;
        }
    }
    if(st.size==0)cout<<"true";
    else cout<<"false";
    clearStack(st);
    return 0;
}