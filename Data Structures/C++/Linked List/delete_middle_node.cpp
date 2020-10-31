#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};
struct Node *deleteMid(struct Node *head);
void printList(Node* node) 
{ 
	while (node != NULL) { 
		cout << node->data <<" "; 
		node = node->next; 
	}  
	cout<<"\n";
} 
int main() 
{ 
        cout<<"Enter the number of elements to be in the linked list:\n";
		int n;
		cin>>n;
        cout<<"Enter the data of nodes:\n";
		int data;
		cin>>data;
		struct Node *head = new Node(data);
		struct Node *tail = head;
		for (int i = 0; i < n-1; ++i)
		{
			cin>>data;
			tail->next = new Node(data);
			tail = tail->next;
		}
		head = deleteMid(head);
	    cout<<"The linked list without middle node is.:\n";
		printList(head); 
	
	return 0; 
} 
Node* deleteMid(Node* head)
{
    int i=0;
    struct Node* temp;
    temp=head;
    while(temp!=NULL){
        temp=temp->next;
        i++;
    }
    temp=head;int n=1;
    struct Node*previous;
    while(n<=(i/2)){
        previous =temp;
        temp=temp->next;
        n++;
        
    }
    previous->next=temp->next;
    free(temp);
    return head;
}
