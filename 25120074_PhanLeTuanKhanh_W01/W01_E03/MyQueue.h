#ifndef QUEUE
#define QUEUE
struct QueueNode{
    QueueNode *next;
    int data;
};
struct MyQueue{
    QueueNode *head;
    QueueNode *tail;
    int size;
};

void initQueue(MyQueue &q);
void enqueue(MyQueue &q, int x);
void dequeue(MyQueue &q);
int front(MyQueue q);
bool isEmpty(MyQueue q);
void clearQueue(MyQueue &q);

#endif