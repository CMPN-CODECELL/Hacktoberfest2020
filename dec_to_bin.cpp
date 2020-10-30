#include<iostream.h>
#include<conio.h>
void main()
{
	clrscr();
	int i=0,num,digit[1000];
	cout<<"\nenter any no.\n";
	cin>>num;
	while(num>0)
	{
		digit[i]=num%2;
		num=num/2;
		i++;
	}
	do{
		cout<<digit[i--];
	}while(i>=0);
	getch();
}