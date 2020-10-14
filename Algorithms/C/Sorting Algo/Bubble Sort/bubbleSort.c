#include<stdio.h>
#include<stdlib.h>
void bubblesort(int [],int);
 int main()
 {
     int arr[100],i,n,j,temp,choice;
     printf("\n How many numbers you want to enter :");
     scanf("%d",&n);
     printf("\n Enter the numbers : ");
     for(i=0;i<n;i++)
     {
     scanf("%d",&arr[i]);
    }printf("\n Numbers before sorting : \n ");
     for(i=0;i<n;i++)
     {
         printf("%d   ",arr[i]);
     }
     bubblesort(arr,n);
 }
void bubblesort(int arr[],int n)
{
  long c, d, t;

  for (c = 0 ; c < n - 1; c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (arr[d] > arr[d+1])
      {
        /* Swapping */

        t= arr[d];
        arr[d]   = arr[d+1];
        arr[d+1] = t;
      }
    }
  }
  printf("\n After bubble sorting : \n");
   for (c = 0; c < n; c++)
   {
    printf("%d   ", arr[c]);
   }
}
