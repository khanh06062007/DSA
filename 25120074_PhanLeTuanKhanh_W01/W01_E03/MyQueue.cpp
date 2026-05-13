#include<iostream>
#include"MyQueue.h"
void initQueue(MyQueue& q){
    q.head = q.tail = nullptr;
    q.size = 0;
}
bool isEmpty(MyQueue q){
    if(!q.size)
        return true;
    return false;
}
void enqueue(MyQueue &q, int x){
    QueueNode* p = new QueueNode;
    p->data = x;
    p->next = nullptr;
    if(isEmpty(q)){
        q.head = q.tail = p;
        q.size++;
        return;
    }
    q.tail->next = p;
    q.tail = q.tail->next;
    q.size++;
    return;
}
void dequeue(MyQueue &q){
    if(isEmpty(q))
        return;
    QueueNode *p = q.head;
    if(q.size == 1){
        q.size--;
        q.head = q.head->next;
        q.tail = q.tail->next;
        delete p;
        return;
    }
    q.size--;
    q.head = q.head->next;
    delete p;
    return;
}
int front(MyQueue q){
    if (isEmpty(q)) return -1;
    return q.head->data;
}
void clearQueue(MyQueue &q){
    while(q.size)
        dequeue(q);
    return;
}
