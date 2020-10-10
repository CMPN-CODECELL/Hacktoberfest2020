#include<stdio.h>
#include<conio.h>
void insert_ele(int i,int ar[],int len){
    int ele, loc;
    printf("\nEnter element to be inserted : ");
    scanf("%d",&ele);
    printf("\nEnter location : ");
    scanf("%d",&loc);
    if(i==19){
        printf("\nOverflow");
    }
    else{
        while(i>=loc){
            ar[i+1]=ar[i];
            i--;
        }
    ar[loc]=ele;
    len++;
    printf("\nNew Array : ");
    for(i=0;i<len;i++){
        printf("\t%d",ar[i]);
    }
    }
}
void delete_ele(int i,int ar[],int len){
    int loc;
    printf("\nEnter location of element to be deleted : ");
    scanf("%d",&loc);
    if(len==0){
        printf("\nUnderflow");
    }
    else{
        for(i=loc;i<len;i++){
            ar[i]=ar[i+1];
        }
        len--;
        printf("\nNew Array : ");
        for(i=0;i<len;i++){
        printf("\t%d",ar[i]);
        }
    }
}
void find_ele(int i,int ar[],int len){
    int ele, count=0;
    printf("\nEnter element to be searched : ");
    scanf("%d",&ele);
    for(i=0;i<len;i++){
        if(ar[i]==ele){
            count++;
        }
    }
    if(count == 0){
        printf("\nElement does not exist");
    }
    else{
        printf("\nElement found %d times",count);
    }
}
void traverse(int i, int ar[], int len){
    printf("\nTotal number of Elements are : %d",len);
    printf("\nElements are : ");
    for(i=0; i<len; i++){
        printf("\t%d",ar[i]);
    }
}
void main(){
    int ar[20], i=0, len=0, ch;
    char choice;
    printf("\nEnter number of elements you want to insert : ");
    scanf("%d",&len);
    for(i=0; i<len; i++){
        printf("Enter element %d : ",i);
        scanf("%d",&ar[i]);
    }
    i--;
    label:
    printf("\nPress 1 to insert, 2 to delete, 3 to find any element");
    printf("\n or 4 to traverse the array : ");
    scanf("%d",&ch);
    switch(ch){
        case 1:insert_ele(i, ar, len);
        break;
        case 2:delete_ele(i, ar, len);
        break;
        case 3:find_ele(i, ar, len);
        break;
        case 4:traverse(i, ar, len);
        break;
        default:printf("\nInvalid Option");
        break;
    }
    printf("\nPress y to continue or any other key to quit : ");
    scanf("%s",&choice);
    if(choice=='y' || choice=='Y'){
        goto label;
    }
    getch();
}
