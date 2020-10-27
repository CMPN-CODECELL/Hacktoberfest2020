function quickSort(arr)
{
  
    return quickSorter(arr,0,arr.length-1)
    
}
function quickSorter(arr,start,end){
    if(!(start>=end)){
        let index=partition(arr,start,end)
        quickSorter(arr,start,index-1);
        quickSorter(arr,index+1,end);
    }
    else
    console.log(arr)
    return arr;

}
function partition(arr,start,end){
    let pivotIndex=start
    let pivotNumber=arr[end];
    for(i=start;i<end;i++){
        if(arr[i]<pivotNumber){
            swap(arr,pivotIndex,i);
            pivotIndex++;
        }
    }
swap(arr,pivotIndex,end);
return pivotIndex;
}
function swap(arr,a,b){
    let temp=arr[a];
    arr[a]=arr[b]
    arr[b]=temp
}
let a=[8,4,5,2,6,1,9,0]
console.log(quickSort(a))