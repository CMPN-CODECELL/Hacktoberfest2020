class Queue 
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
            return this.array.pop();
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
        queueSearch(queue,element)
        {
            var useArr=queue.getArray();
            var nUseArr=new Queue;
            nUseArr.constructor1(useArr)
            while(!nUseArr.isEmpty()){
                if(nUseArr.remove()==element)
                    {return true;}  
            }
            return false;
        }
    }
function weaver(sourceOne,sourceTwo){
            var concatQueue=new Queue
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

var q1=new Queue;
var q2=new Queue;
q1.add(1)
q1.add(2)
q1.add(3)
q2.add(4)
q1.display()
weaver(q1,q2)
