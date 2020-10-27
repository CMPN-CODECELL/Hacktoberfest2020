class Graph{
    constructor(noOfVertices){
        this.noOfVertices=noOfVertices;
        this.adjList=new Map();
    }
    addVertex(x){
        this.adjList.set(x,[])
        
    }
    addEdges(src,dest){
        this.adjList.get(src).push(dest)
        this.adjList.get(dest).push(src)        
        // console.log(this.adjList)
    }
    printGraph(){
        for(let i of this.adjList.keys())
        {
            let con = ''
            for(let j of this.adjList.get(i))
            {
                con+=j +' ';
            }
            console.log(i + ' -> ' + con)
        }
    }
    breafthFirstSearch(startNode){
        var visited=[]
        for(let i=0;i<visited.length;i++){
            visited[i]=false
        }
        var q= new Queue()
        visited[startNode]=true
        q.add(startNode);
        while(!q.isEmpty()){
            var currentElement=q.remove()
            console.log(currentElement)
            let getList=this.adjList.get(currentElement)
            for(let i in getList)
                var taker=getList[i]
            
            if(!visited[taker]){
                visited[taker]=true;
                q.add(taker)
            }
        }
    }

}
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
        isEmpty(){
            if(this.array.length === 0)
                return true;
            else
                return false;
        }
    }
var g=new Graph(3)
var ver=['A','B','C']
for(let i =0 ;i<ver.length;i++){
g.addVertex(ver[i])}
g.addEdges('A','B')
g.addEdges('A','C')
g.addEdges('C','B')
g.printGraph()
g.breafthFirstSearch('A')