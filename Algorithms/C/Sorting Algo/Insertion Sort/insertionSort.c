#include <math.h>
#include <stdio.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    printf("\n Enter the elements : \n");
    for(i=0;i<n;i++)
    {
    scanf("%d",&arr[i]);
    }
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// A utility function to print an array of size n
void printArray(int arr[], int n)
{
    int i;
    printf("\n Elements after sorting : \n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Driver program to test insertion sort */
int main()
{
    int arr[100],n;
    printf("\n How many elements you want to enter : ");
    scanf("%d",&n);

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}

