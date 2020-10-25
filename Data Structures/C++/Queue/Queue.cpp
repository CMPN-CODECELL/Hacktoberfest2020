#include <iostream>

using namespace std;
struct node{
int data;
node *next;}*head,*tail;


void enqueue(int x){
node *t =new node;
if(t!=NULL){
    t->data=x;
    t->next=NULL;
    if(head==NULL){
        head=t;
        tail=t;
    }
    else{
        tail->next=t;
        tail=t;
    }

}
else{
    cout<<"List is full";
}
}

void display(node *p){
if(p==NULL)
    cout<<"ERROR: List is Empty";
while(p!=NULL){
    cout<<p->data<<" ";
    p=p->next;
}
cout<<endl;
}

int dequeue(){
node *t;
int x;

    t=head;
    x = t->data;
    head=head->next;
    delete t;

return x;
}

int main()
{

  
   int x;
    int n=1;
    while(n!=0){

            cout<<"0. Exit"<<endl
                <<"1. Insert"<<endl
                <<"2. Delete"<<endl
                <<"3. Display"<<endl;
            cout<<"Enter Choice: ";
            cin>>n;
            switch(n){
            case 1: cout<<"Enter Data ";
                    cin>>x;
                    enqueue(x);
                    break;
            case 2: if(head!=NULL)
                    cout<<"The deleted element is: "<<dequeue()<<endl;
                    else cout<<"ERROR: List Empty"<<endl;
                    break;
            case 3: cout<<"The elements in the list are: ";
                    display(head);
                    break;
            case 0: break;
            default : cout<<"ERROR: Invalid Choice";
            }

        }
}




