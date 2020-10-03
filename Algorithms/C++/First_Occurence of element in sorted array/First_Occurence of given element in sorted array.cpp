#include<iostream>

using namespace std;

//function first_occurence will return the index of given ele

int first_occurence(int* arr, int n, int ele)
{
    int start = 0, last = n-1, index = -1;
    while(start <= last)
    {
        int mid = start + (last-start)/2;

        if(arr[mid] == ele)
        {
            index = mid;
            last = mid-1;
        }

        else if(ele < arr[mid])
            last = mid - 1;

        else
            start = mid + 1;
    }

    return index;
}

int main()
{
    int n;  //size of array
    cin>>n;

    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];

        int element;    //element to search its first occurence
        cin>>element;

    cout<<"Index of first occurence of "<<element<<" is "<<first_occurence(arr,n,element);

    return 0;
}
