class Node{
    constructor(value){
    this.value=value;
    this.left=null
    this.right=null
    }
    
}
class BinaryTree{
    constructor(){
        this.root=null;
    }
    insertData(value){
        var newNode=new Node(value)
        if(this.root===null)
            {
                this.root=newNode
            }
        else{
            this.insertNode(this.root,newNode)
        }
    }
    insertNode(parentNode,childNode){
        if(parentNode.value>childNode.value){
            if(parentNode.left===null){
                parentNode.left=childNode
            }
            else{
                this.insertNode(parentNode.left,childNode)
            }
        }
        else{
            if(parentNode.right==null)
                {
                    parentNode.right=childNode
                }
            else{
                this.insertNode(parentNode.right,childNode)
            }
        }
    }
    inorder(node){
        if(node){
            this.inorder(node.left)
            console.log(node.value)
            this.inorder(node.right)
        }
    }
    preorder(node){
        if(node){
            console.log(node.value)
            this.inorder(node.left)
            this.inorder(node.right)
        }
    } postorder(node){
        if(node){
            this.inorder(node.left)
            this.inorder(node.right)
            console.log(node.value)
        }
    }
    
    delete(value){
        this.root=this.deleteNode(this.root,value)
        }
    
    deleteNode(node,value){
        if(!node){
            console.log('tree is empty');
            return null
        }
        else if(node.value>value){
            node.left=this.deleteNode(node.left,value)
            return node
        }
        else if(node.value<value){
            node.right=this.deleteNode(node.right,value)
            return node
        }
        else{
            if(!node.left && !node.right)
                {
                    node=null;
                    return node
                }
            if(!node.left){
                node=node.right;
                return node
            }
            else if(!node.right){
                node=node.left
                return node
            }
            else{
                var temp=this.smallestNode(node.right)
                node.value=temp.value
                node.right=this.deleteNode(node.right,temp.value)
                return node
            }
        }
    }
    inorderTraverser(){
        this.inorder(this.root)

    } preorderTraverser(){
        this.preorder(this.root)

    } postorderTraverser(){
        this.postorder(this.root)

    }
    search(value){
        console.log(this.searcher(this.root,value))
    }
    searcher(node,value){
        if(!node){
            return false
        }
        else if(node.value>value){
            return this.searcher(node.left,value)
        }
        else if(node.value<value){
            return this.searcher(node.right,value)
        }
        else if(node.value===value)
            {
                return true
            }
        else{
            return false
        }
    }
    smallestNode(node){
        if(node.left===null){
            return node
        }
        else
            return this.smallestNode(node.left)
    }
    lowestCommanAncestor(value1,value2){
        function LCA(root,value1,value2){
            if(!root){
                console.log('tree is empty');
                return null;
            }
            else if(Math.max(value1,value2)<root.value)
                {
                    return lowestCommanAncestor(root.left,value1,value2)
                }
            else if(Math.min(value1,value2)>root.value){
                return lowestCommanAncestor(root.right,value1,value2)
            }
            else
                return root.value
            
        }
        console.log(LCA(this.root,value1,value2))
    }
}
var t1=new BinaryTree
t1.insertData(2)
t1.insertData(1)
t1.insertData(3)
t1.postorderTraverser()
t1.lowestCommanAncestor(1,3)