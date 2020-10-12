#include<stdlib.h>
#include<stdio.h>

#define MAX 100
int queue[MAX],F=-1,R=-1;

void insert(int x) {
	if((F==0 && R==MAX-1) || (R==F-1)) {
		printf("Queue is full\n");
		return;
	}
	if(F==-1 && R==-1) {
		F=R=0;
	}else if(F!=0 && R==MAX-1){
		R=0;
	}else{
		R=R+1;
	}
	queue[R]=x;
}

void del() {
	if((F==-1 && R==-1) || F>R ) {
		printf("Queue is empty\n");
		return ;
	}
	F++;
}

void display() {
	if((F==-1 && R==-1) || F>R ) {
		printf("Queue is empty\n");
		return ;
	}
	int front=F,rear=R;
	while(front!=rear) {
		if(rear>front) {
			printf("%d ",queue[rear++]);	
		}else {
			printf("%d ",queue[front]);
			if(front==MAX-1) {
				front=0;
			}else {
				front++;
			}				
	}
		
	printf("%d ",queue[rear++]);
	}
}

void peek() {
	if((F==-1 && R==-1) || F>R ) {
		printf("Queue is empty\n");
		return ;
	}
	printf("The first element in queue is %d \n",queue[F]);
}

int main() {
	int x;
	do{
		printf("****MENU****\n");
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Peek\n");
		printf("4.Display");
		printf("5.Exit");
		printf("Enter option\n");
		scanf("%d",&x);
		switch(x) {
			case 1: 
				printf("Enter element to be inserted in queue.\n");
				int a;
				scanf("%d",&a);
				insert(a);
			case 2:
				del();
			case 3:
				peek();
			case 4:
				display();
		}
	}while(x!=-1);
	return 0;
}
