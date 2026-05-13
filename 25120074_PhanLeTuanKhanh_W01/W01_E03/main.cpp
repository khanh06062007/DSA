#include<iostream>
#include<string>
#include"MyQueue.h"
int timeRequiredToBuy(int tickets[], int n, int k){
    MyQueue q;
    initQueue(q);
    for (int i = 0; i < n; i++)
        enqueue(q, i);
    int res = 0;
    while(tickets[k-1]>0){
        res++;
        int t = front(q);
        //std::cout << tickets[t] << " ";
        dequeue(q);
        if(--tickets[t]>0){
            enqueue(q, t);
        }
    }
    clearQueue(q);
    return res - 1;
}
int catchCow(int n, int k){
    MyQueue q;
    initQueue(q);
    int* numbers = new int [std::max(n,2*k + 1) + 1];
    for(int i = 0; i <= 2*k; i++)
        numbers[i] = k + 10000; // Khởi tạo bằng một số đủ lớn thay vì k
    numbers[n] = 0;
    enqueue(q, n);
    while(!isEmpty(q)){
        int t = front(q);
        dequeue(q);
        if(t-1>=0 && numbers[t]+1<numbers[t-1]){
            numbers[t-1] = numbers[t]+1;
            enqueue(q, t-1);
        }
        if(t+1<=2*k-1 && numbers[t]+1<numbers[t+1]){
            numbers[t+1] = numbers[t]+1;
            enqueue(q, t+1);
        }
        if(t*2<=2*k-1 && numbers[t]+1<numbers[2*t]){
            numbers[2*t] = numbers[t]+1;
            enqueue(q, 2*t);
        }
    }
    int ans = numbers[k];
    delete[] numbers;
    return ans;
}
int main(){
    int tickets[3] = {2, 3, 2};
    int n = 3, k = 2;
    std::cout << timeRequiredToBuy(tickets, n, k)<<'\n';
    n = 5, k = 17;
    std::cout << catchCow(n, k)<<'\n';
}