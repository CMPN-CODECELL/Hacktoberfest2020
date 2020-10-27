function CountSort(arr){
    let max=Math.max.apply(null,arr)
    let min=Math.min.apply(null,arr)
    let i,j=0,len=arr.length,Count=[]
    for(i=min;i<=max;i++){
        Count[i]=0
    }
    for (i = 0; i < len; i++) {
        Count[arr[i]] += 1;
    }
    for(i=min;i<=max;i++){
        while(Count[i]>0){
            arr[j]=i
            j++
            Count[i]--
        }
    }
    console.log(arr)

}

CountSort([23,43,1,2,7,3,3,8,12])