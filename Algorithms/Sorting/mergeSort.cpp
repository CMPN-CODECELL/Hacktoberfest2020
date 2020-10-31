#include<bits/stdc++.h>
using namespace std;

void merge(vector<long> &a,long low,long mid,long high)
{
    vector<long> f(a.begin()+low,a.begin()+mid+1);
    vector<long> s(a.begin()+mid+1,a.begin()+high+1);

    long i=0, j=0, k=low;
    while(i<(mid-low+1) && j<(high-mid))
    {
        if(f[i]<=s[j])
        {
            a[k]=f[i];
            i++;
        }
        else
        {
            a[k]=s[j];
            j++;
        }
        k++;
    }
    while(i<(mid-low+1))
    {
        a[k]=f[i];
        i++;
        k++;
    }
    while(j<(high-mid))
    {
        a[k]=s[j];
        j++;
        k++;
    }
}

void mergeSort(vector<long> &a,long low,long high)
{
    if(low<high)
    {
        long mid= low + (high-low)/2;
        mergeSort(a,low,mid);
        mergeSort(a,mid+1,high);
        merge(a,low,mid,high);
    }
}

int main()
{
    long n,i; // n= size of the vector
    cin>>n;
    vector<long> a(n);
    for(i=0;i<n;i++)
    {
        cin>>a[i];
    }
    mergeSort(a,0,n-1);
    // display the vector after sorting
    for(i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}