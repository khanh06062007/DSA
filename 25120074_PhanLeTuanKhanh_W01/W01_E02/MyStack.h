#ifndef STACK
#define STACK
struct node{
    node* next;
    int data;
};
struct MyStack{
    node* top;
    int size;
};
void initStack(MyStack& st);
void push(MyStack& st,int x);
void pop(MyStack& st);
int top(MyStack st);
bool isEmpty(MyStack st);
void clearStack(MyStack& st);
#endif