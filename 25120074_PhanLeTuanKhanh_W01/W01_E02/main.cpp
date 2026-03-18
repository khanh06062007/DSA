#include<string>
#include<iostream>
#include"MyStack.h"
using namespace std;
int n;
string s;
MyStack st;
void module2_2(){
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
    cout<<'\n';
}
void module2_3(){
    cin>>s;
    n=s.size();
    int res=0;
    MyStack pos;
    initStack(st);
    initStack(pos);
    push(pos,-1);
    for(int i=0;i<n;i++){
        int k=s[i]-0;
        if(k==40){
            push(st,k);
            push(pos,i);
        }
        else if(!isEmpty(st) && top(st)==k-1){
            pop(st);
            pop(pos);
            res=max(res,i-top(pos));
        }
        else{
            push(st,k);
            push(pos,i);
        }
    }
    cout<<res;
    clearStack(st);
    clearStack(pos);
}
int main(){
    module2_2();
    module2_3();
    return 0;
}