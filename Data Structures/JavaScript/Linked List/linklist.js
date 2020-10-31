class Node{
    constructor(data,next=null)
    {
        this.data=data;
        this.next=next;
    }
}
class Linklist{
    constructor()
    {
        this.head=null
        this.size=-1 
    }
    push(data)
    {
        this.size++;
        if(this.head===null)
            {
                var node=new Node(data)
                this.head=node
            }
        else{
            var temp=this.head;
            var node=new Node(data,temp)
            this.head=node
            
        }
    }
    pop()
    {
        if(this.head===null)
            {
                console.log('list is empty')
            }
        else{
            this.size--;
            var temp=this.head;
            this.head=temp.next;
        }
       
    }
    insert(value,index)
    {
        
        if(this.head===null)
            {
                this.size++;
                var node=new Node(value)
                this.head=node
            }
        else if(this.size<index){
            console.log('index not found')
        }
        else{
            this.size++;
            let i=0
            let temp=this.head
            while(i<index-1)
                {
                    temp=temp.next;
                    i++
                }
                var node=new Node(value,temp.next)
                temp.next=node
        }
    }
    remove(value)
    {
        if(this.head===null)
            {
                console.log('list is empty')
            }
        else if(this.head.data===value)
            {
                this.pop()
            }
        else{
            this.size--;
            var temp=this.head
            let pretemp
            while(temp.data !== value)
                {   
                    pretemp=temp;
                    temp=temp.next;
                }
            pretemp.next=temp.next;
            
        }
    }
    display()
    {
        var currentNode=this.head;
        while(!(currentNode==null)){
            console.log(currentNode);
            currentNode=currentNode.next;
        }
    }
    *[Symbol.iterator](){
        let node=this.head;
        while(node){
        yield node;
        node=node.next;
        }
        
    }
    midpointNode()
    {
        var slow=this.head;
        var fast=this.head;
        while( fast.next && fast.next.next)
            {
                slow=slow.next
                fast=fast.next.next
            }
        console.log(slow)
    }
}

l1=new Linklist();
l1.push(5)
l1.push(4)
l1.push(3)
l1.push(2)
l1.push(1)
/*
l1.remove(1)
l1.display()
for(let node of l1){
    node.data+=10
}
*/
l1.display()
l1.midpointNode()