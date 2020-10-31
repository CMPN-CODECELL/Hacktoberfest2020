function mergeSort(arr){
    if(arr.length===1){
        return arr
    }
    let center=Math.round(arr.length/2)
    let left=arr.slice(0,center);
    let right=arr.slice(center);
    return merge(mergeSort(left),mergeSort(right))
}
function merge(left,right){
    let result=[];
    while(left.length && right.length){
        if(left[0]<right[0])
        {
            result.push(left.shift())
        }
        else
        {
            result.push(right.shift())
        }
        
    }
    console.log([...result,...right,...left])
    return [...result,...right,...left]
}
let arr=[3,2,4,5,1]
console.log(mergeSort(arr))