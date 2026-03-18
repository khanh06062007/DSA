#include<iostream>
// #include"MyStack.h"
// void initStack(MyStack& st){
//     st.size=0;
//     st.top=nullptr;
// }
// void push(MyStack& st,int x){
//     st.top->data=x;
//     st.top=st.top->next;
//     st.size++;
// }
// void pop(MyStack& st){
//     if(st.size==0)return;
//     node* p=st.top;
//     st.top=st.top->next;
//     delete p;
//     st.size--;
// }
// int top(MyStack st){
//     if(st.size==0)return -1;
//     return st.top->data;
// }
// bool isEmpty(MyStack st){
//     if(st.size==0)return true;
//     return false;
// }
// void clearStack(MyStack& st){
//     while(st.size>0){
//         node* p=st.top;
//         st.top=st.top->next;
//         delete p;
//         st.size--;
//     }
// }