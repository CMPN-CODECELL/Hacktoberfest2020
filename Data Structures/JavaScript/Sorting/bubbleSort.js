function bubbleSort(a)
{
    for(let i=0 ; i<a.length;i++){
        for(j=0;j<a.length-i-1;j++){
            if(a[j] > a[j+1]){
                temp=a[j]
                a[j]=a[j+1]
                a[j+1]=temp
            }
        }
    }
    return a
}
a=[8,4,5,2,6,1,0,9]
console.log(bubbleSort(a))