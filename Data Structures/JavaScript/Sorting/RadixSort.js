let getDigit=(num,i)=>{
    return Math.floor(Math.abs(num)/Math.pow(10,i))%10
}
let digitCount=(num)=>{
    if(num==0){
        return 1
    }
    return Math.floor(Math.log10(Math.abs(num)))+1
}
let mostDigits=(nums)=>{
    let maxDigits=0
    for(i=0;i<nums.length;i++){
        maxDigits=Math.max(maxDigits,digitCount(nums[i]))
    }
    return maxDigits
}
let radixSort=nums=>{
    let maxDigitsCount=mostDigits(nums)
    
    for(k=0;k<maxDigitsCount;k++){
        let DigitBucket=Array.from({length:10},()=>[])
        for(i=0;i<nums.length;i++){
            DigitBucket[getDigit(nums[i],k)].push(nums[i])
        }
        nums=[].concat(...DigitBucket)
    }
    return nums
}

console.log(radixSort([23,3231,31,3,4,2,4]))



