#include<iostream>
#include<string>
struct PatientNode{
    int id;
    std::string name;
    PatientNode* next;
};
PatientNode* createNode(int id,std::string name){
    PatientNode* p = new PatientNode;
    p->id=id;
    p->name=name;
    p->next=nullptr;
    return p;
}
void insertHead(PatientNode*& head, PatientNode* newNode){
    newNode->next=head;
    head=newNode;
}
void insertTail(PatientNode*& head, PatientNode* newNode){
    if(head==nullptr){
        insertHead(head,newNode);
        return;
    }
    PatientNode* p;
    for(p=head;p->next;p=p->next);
    p->next=newNode;
}
void printList(PatientNode* head){
    PatientNode* p;
    for(p=head;p;p=p->next)
        std::cout<<p->id<<" "<<p->name<<'\n';
}
int countPatients(PatientNode* head){
    PatientNode* p;
    int d=0;
    for(p=head;p;p=p->next)d++;
    return d;
}
void removeHead(PatientNode*& head){
    if(head==nullptr)return;
    PatientNode* q=head;
    head=head->next;
    delete q;
}
void removeByID(PatientNode*& head, int id){
    if(head->id==id){
        removeHead(head);
        return;
    }
    PatientNode* p;
    for(p=head;p->next;p=p->next){
        if(p->next->id==id){
            PatientNode* q=p->next;
            p->next=q->next;
            delete q;
            break;
        }
    }
}
void reverseList(PatientNode*& head){
    PatientNode* temp,*prev=nullptr;
    for(PatientNode* p=head;p;){
        temp=p;
        p=p->next;
        temp->next=prev;
        prev=temp;
    }
    head=prev;
}
PatientNode* findMiddle(PatientNode* head){
    if(head==nullptr) return nullptr;
    PatientNode* slow=head,*fast=head;
    while(fast!=nullptr && fast->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}
int main(){
    PatientNode* WaitingList=nullptr;
    insertTail(WaitingList,createNode(101,"Alice"));
    insertTail(WaitingList,createNode(102,"Bob"));
    insertTail(WaitingList,createNode(103,"Charlie"));
    insertHead(WaitingList,createNode(104,"Emergency David"));
    std::cout << "After adding 3 patients and emergency patient arrives:\n";
    printList(WaitingList);
    removeHead(WaitingList);
    std::cout << "After first patient seen:\n";
    printList(WaitingList);
    PatientNode* p=findMiddle(WaitingList);
    if(p!=nullptr)
        std::cout<<"Middle patient: "<<p->id<<" "<<p->name<<'\n';
    removeByID(WaitingList,102);
    std::cout << "After removing patient ID 102:\n";
    printList(WaitingList);
    std::cout<<"Total patients: "<<countPatients(WaitingList)<<'\n';
    reverseList(WaitingList);
    std::cout << "After reversing the list:\n";
    printList(WaitingList);
    while(WaitingList!=nullptr)
        removeHead(WaitingList);
    return 0;
}