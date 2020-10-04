//This is code has the level order function
//class for node is defined as

/*class Node{
	public:
		int data;
		Node* left, right;
};
*/

void levelOrder(Node *root){
	if(root == NULL) return;

	queue <Node*> q;
	q.push(root);

	while(q.empty != true){
		Node *node = q.front();
		cout << node -> data << " ";
		q.pop();

		if(node -> left != NULL)
			q.push(node -> left);
		if(node -> right != NULL)
			q.push(node -> right);
	}
}

