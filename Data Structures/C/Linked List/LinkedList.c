#include<stdio.h>
#include<malloc.h>
#include<conio.h>


typedef struct node
{
    int data;
    struct node *next;
}NODE;

NODE *start=NULL;


void create()
{
    char option;
    int x;
    start=NULL;
    option='y';
    while(option=='Y' || option=='y')
    {
        printf("Enter the value of the node to be inserted\n");
        scanf("%d",&x);
        insert_end(x);
        fflush(stdin);
        printf("\nDo you want to enter more data?[Y/N]\n");
        scanf("%c",&option);

    }
}
int insert_beg(int x)
{
    NODE *ptr;
    ptr=(NODE *)malloc(sizeof(NODE));

    if(ptr==NULL)
    {
        printf("Memory full. ");
        return 0;
    }
    ptr->data=x;
    ptr->next=NULL;

    if(start==NULL)
    {
        start=ptr;
        printf("%d is inserted", x);
        return 1;

    }
    ptr->next=start;
    start=ptr;

    printf("%d is inserted", x);
    return 1;
}

int insert_end(int x)
{
    NODE *ptr,*p;
    ptr=(NODE *)malloc(sizeof(NODE));

    if(ptr==NULL)
    {
        printf("Memory full. ");
        return 0;
    }
    ptr->data=x;
    ptr->next=NULL;

    if(start==NULL)
    {
        start=ptr;
        printf("%d is inserted",x);
        return 1;
    }

    p=start;
    while(p->next!=NULL)
        p=p->next;

    p->next=ptr;

    printf("%d is inserted",x);
    return 1;
}

int insert_after(int key,int x)
{
    NODE *ptr,*p;
    ptr=(NODE *)malloc(sizeof(NODE));

    if(ptr==NULL)
     {
        printf("Memory full. ");
        return 0;
     }
    ptr->data=x;
    ptr->next=NULL;

    p=start;
    while(p!=NULL && p->data!=key)
        p=p->next;

    if(p==NULL)
    {
        printf("%d not found.",key);
        return 0;
    }
    ptr->next=p->next;
    p->next=ptr;

    printf("%d is inserted",x);
    return 1;
}

int insert_before(int key,int x)
{
    NODE *ptr,*p,*prev;
    ptr=(NODE *)malloc(sizeof(NODE));

    if(ptr==NULL)
    {
        printf("Memory full. ");
        return 0;
    }
    ptr->data=x;
    ptr->next=NULL;

    p=start;
    prev=NULL;
    while(p!=NULL && p->data!=key)
    {
        prev=p;
        p=p->next;
    }

    if(p==NULL)
    {
        printf("%d not found. ",key);
        return 0;
    }
    if(p==start)
    {
        ptr->next=p;
        start=ptr;
    }
    else
    {
        ptr->next=prev->next;
        prev->next=ptr;
    }

    printf("%d is inserted. ",x);
    return 1;


}

int insert_position(int pos, int x)
{
    NODE *ptr,*p;
    int i;
    ptr=(NODE *)malloc(sizeof(NODE));

    if(ptr==NULL)
    {
        printf("Memory full. ");
        return 0;
    }


        ptr->data=x;
        ptr->next=NULL;

        if(pos<=1)
        {
            if(start==NULL)
                start=ptr;
            else
            {
                ptr->next=start;
                start=ptr;
            }
        }
        else
        {
            p=start;
            for(i=1;i<=pos-2;i++)
            {
                p=p->next;
                if(p==NULL)
                   break;
            }
            if(p==NULL)
            {
                printf("Invalid position.");
                return 0;
            }

                ptr->next=p->next;
                p->next=ptr;
        }
                printf("%d is inserted. ",x);
                return 1;

}

void tellcount()
{
    NODE *p;
    int count=0;
    p=start;
    while(p!=NULL)
    {
            p=p->next;
            count++;
    }
    printf("The number of elements are %d",count);
}

void empty()
{
   if(start==NULL)
        printf("Linklist is empty");
    else
        printf("Linklist is not empty");

}

void full()
{
    NODE *p;
    p=(NODE *)malloc(sizeof(NODE));
    if(p==NULL)
        printf("Linklist is full");
    else
    {
        free(p);
        printf("Linklist is not full");
    }

}

void traverse()
{
    NODE *p=start;
    printf("The contents of list are\n");
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

void destroy()
{
    NODE *p,*q;
    q=start;
    p=NULL;
    while(q!=NULL)
    {
        p=q;
        q=q->next;
        free(p);
    }
    start=NULL;
    free(start);
}

int delete_beg()
{
    NODE *ptr;
    ptr=start;
    if(ptr==NULL)
    {
        printf("No elements in the list. ");
        return 0;
    }
    start=start->next;
    ptr->next=NULL;
    printf("%d is deleted. ",ptr->data);
    free(ptr);
    return 1;
}

int delete_end()
{
    NODE *ptr,*prev;
    ptr=start;
    prev=NULL;
    if(ptr==NULL)
    {
        printf("No elements in the list. ");
        return 0;
    }
    if(start->next==NULL)
    {
        start=NULL;
        printf("%d is deleted",ptr->data);
        free(ptr);
        return 1;
    }
    while(ptr->next!=NULL)
    {
            prev=ptr;
            ptr=ptr->next;
    }
    prev->next=NULL;
    printf("%d is deleted",ptr->data);
    free(ptr);
    return 1;
}

int delete_node(int key)
{
    NODE *ptr,*prev;
    ptr=start;
    prev=NULL;
    if(ptr==NULL)
    {
        printf("No elements in the list. ");
        return 0;
    }
    if(start->data==key)
    {
        start=start->next;
        ptr->next=NULL;
        printf("%d is deleted",ptr->data);
        free(ptr);
        return 1;
    }
    while(ptr!=NULL && ptr->data!=key)
    {
        prev=ptr;
        ptr=ptr->next;
    }
    if(ptr==NULL)
    {
        printf("Element to be deleted not found. ");
        return 0;
    }
    prev->next=ptr->next;
    ptr->next=NULL;
    printf("%d is deleted",ptr->data);
    free(ptr);
    return 1;
}

int delete_after(int key)
{
    NODE *ptr,*prev;
    ptr=start;
    if(ptr==NULL)
    {
        printf("No elements in the list. ");
        return 0;
    }
    if(start->next==NULL)
    {
        printf("Only one element in the list. ");
        return 0;
    }
    while(prev!=NULL && prev->data!=key)
    {
        prev=ptr;
        ptr=ptr->next;
    }
    if(ptr==NULL)
    {
        printf("Element to be deleted after not found. ");
        return 0;
    }

    prev->next=ptr->next;
    printf("%d is deleted",ptr->data);
    free(ptr);
    return 1;

}

int delete_before(int key)
{
    NODE *p,*q,*prevOfq;

    if(start==NULL)
    {
        printf("Linklist is empty");
        return 0;
    }

    p=start;
    q=NULL;
    prevOfq=NULL;
    while(p->data!=key && p->next!=NULL)
    {
        prevOfq=q;
        q=p;
        p=p->next;

    }
    if(p==start)
    {
        printf("No element before start");
        return 0;
    }
    if(p->data!=key)
    {
        printf("Key not found");
        return 0;
    }
    if(prevOfq==NULL)
    {
        start=start->next;

    }
    else
    {
        prevOfq->next=p;

    }
        q->next=NULL;
        printf("%d is deleted",q->data);
        free(q);
        return 1;

}

int main()
{
    int option,x,pos,op,key;

    do
    {
        printf("\n *Choose an option*");
        printf("\n1. Create a list");
        printf("\n2. Display the list");
        printf("\n3. Add a node at the beginning");
        printf("\n4. Add a node at the end");
        printf("\n5. Add a node before a given node");
        printf("\n6. Add a node after a given node");
        printf("\n7. Add a node at a specific position");
        printf("\n8. Delete a node from the beginning");
        printf("\n9. Delete a node from the end");
        printf("\n10. Delete a given node");
        printf("\n11. Delete a node after a given node");
        printf("\n12. Destroy the entire list");
        printf("\n13. Check whether list is empty");
        printf("\n14. Check whether list if full");
        printf("\n15. Count the number of elements in the list");
        printf("\n16. EXIT");
            printf("0.delete before");

        printf("\n\n Enter your option: ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:create();
                    break;

            case 2:traverse();
                    break;

            case 3: printf("\n Enter the node to be inserted");
                    scanf("%d",&x);
                    op=insert_beg(x);
                    if(op==0)
                        printf("Element not inserted. ");

                    break;

            case 4: printf("\n Enter the node to be inserted");
                    scanf("%d",&x);
                    op=insert_end(x);
                    if(op==0)
                        printf("Element not inserted. ");

                    break;

            case 5: printf("\n Enter the node to be inserted");
                    scanf("%d",&x);
                    printf("\n Enter the node before which data is to be inserted");
                    scanf("%d",&key);

                    op=insert_before(key,x);
                    if(op==0)
                        printf("Element not inserted. ");

                    break;


            case 6: printf("\n Enter the node to be inserted");
                    scanf("%d",&x);
                    printf("\n Enter the node after which data is to be inserted");
                    scanf("%d",&key);

                    op=insert_after(key,x);
                    if(op==0)
                        printf("Element not inserted. ");

                    break;


            case 7: printf("\n Enter the node to be inserted");
                    scanf("%d",&x);
                    printf("\n Enter the position where data is to be inserted");
                    scanf("%d",&pos);

                    op=insert_position(pos,x);
                    if(op==0)
                        printf("Element not inserted. ");

                    break;

            case 8:op=delete_beg();
                    if(op==0)
                        printf("Deletion not possible");

                    break;

            case 9:op=delete_end();
                    if(op==0)
                        printf("Deletion not possible");

                    break;

            case 10: printf("Enter the node to be deleted");
                     scanf("%d",&key);

                     op=delete_node(key);
                     if(op==0)
                        printf("Deletion not possible");

                    break;

            case 11: printf("Enter the node after which data is to be deleted");
                     scanf("%d",&key);

                     op=delete_after(key);
                     if(op==0)
                        printf("Deletion not possible");

                    break;

            case 12: destroy();
                    printf("Linklist is destroyed");
                    break;

            case 13:empty();
                    break;

            case 14:full();
                    break;

            case 15:tellcount();
                    break;

            case 16: break;

            case 0:printf("Enter the node before which data is to be deleted");
                     scanf("%d",&key);

                     op=delete_before(key);
                     if(op==0)
                        printf("Deletion not possible");

                    break;

        default: printf("Invalid option\n");

        }
        getch();
    }
    while(option!=16);

    return 0;
}
