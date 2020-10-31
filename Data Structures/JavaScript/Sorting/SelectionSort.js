function selectionSort(a)
{
    for(let i=0 ;i<a.length;i++){
        let indexMin=i
        for(let j=i+1 ;j<a.length;j++)
        {
            if(a[j]<a[indexMin]){
                indexMin=j
            }
        }
         if(indexMin!==i)
        {
            let temp=a[indexMin];
            a[indexMin]=a[i];
            a[i]=temp

       }
        
    }
    return a
}
let a=[7,4,6,2,0,5]
console.log(selectionSort(a))