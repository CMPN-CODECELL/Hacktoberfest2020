class Stack
    {
        constructor(){
            this.array=[]
        }
        constructor1(array){
            this.array=array
        }
        add(record){
            this.array.unshift(record);
        }
        remove(){
            return this.array.shift();
        }
        display(){
            console.log(this.array)
        }
        isEmpty(){
            if(this.array.length === 0)
                return true;
            else
                return false;
        }
        getArray()
        {
            return this.array
        }
        stackSearch(stack,element)
        {
            var useArr=stack.getArray();
            var nUseArr=new Stack;
            nUseArr.constructor1(useArr)
            while(!nUseArr.isEmpty()){
                if(nUseArr.remove()==element)
                    {return true;}  
            }
            return false;
        }
    }
function weaver(sourceOne,sourceTwo){
            var concatQueue=new Stack   
            while(!sourceOne.isEmpty() || !sourceTwo.isEmpty())
            {
                if(!sourceOne.isEmpty())
                {
                    concatQueue.add(sourceOne.remove())
                }
                if(!sourceTwo.isEmpty())
                    {
                        concatQueue.add(sourceTwo.remove())
                    }
            }
    console.log(concatQueue)
        }

var s1=new Stack;
var s2=new Stack;
s1.add(1)
s1.add(2)
s1.add(3)
s2.add(4)
s2.add(5)
s1.display()
s2.display()
weaver(s1,s2)