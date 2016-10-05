class TreeNode{
	char data;
	TreeNode left;
	TreeNode right;
}

class LTree{
	private TreeNode Root;
	
	public TreeNode makeTree(TreeNode t1, char data, TreeNode t2){
		TreeNode Root = new TreeNode();
		Root.data = data;
		Root.left = t1;
		Root.right = t2;
		return Root;
	}

	public void preorder(TreeNode root){
		if(root != null){
			System.out.printf("%c", root.data);
			preorder(root.left);
			preorder(root.right);
		}
	}
 
	public void inorder(TreeNode root){
		if(root != null){
			inorder(root.left);
			System.out.printf("%c", root.data);
			inorder(root.right);  
		}
	}

	public void postorder(TreeNode root){
		if(root != null){
			postorder(root.left);
			postorder(root.right);
			System.out.printf("%c", root.data);
		}
	}

	public int evaluate(TreeNode root){
		if(root==null) return 0;
		if(root.left==null && root.right == null)
			return (int)(root.data);
		else{
			int op1 = (int)(evaluate(root.left));
			int op2 = (int)(evaluate(root.right));
			switch(root.data){
			case '+':
				return (int)(op1+op2);
			case '*':
				return (int)(op1*op2);
			case '-':
				return (int)(op1-op2);
			case '/':
				return (int)(op1/op2);
			}
		}
	return 0;
	}

	void insert_node(TreeNode root, char key){
		TreeNode p, t;
		TreeNode n;

		t=root;
		p=null;	

		while(t!=null){
			if(key == t.data)
				return ;
			p=t;
				if(key<t.data)
				t=t.left;
			else
				t=t.right;
		}
		
		n = new TreeNode();	

		if(n==null) return;
		n.data=key;
		n.left = n.right = null;	

		if(p!=null){
			if(key< p.data)
				p.left = n;
			else
				p.right = n;
		}
		else
			root=n;

	}

}

class Tree1{
	public static void main(String args[]){
		LTree t = new LTree();
		
		TreeNode n7 = t.makeTree(null, '0', null); //단말노드 생성
		TreeNode n6 = t.makeTree(null, '0', null);
		TreeNode n5 = t.makeTree(null, '0', null);
		TreeNode n4 = t.makeTree(null, '0', null); //단말노드 생성 끝
		TreeNode n3 = t.makeTree(n6, '+', n7);
		TreeNode n2 = t.makeTree(n4, '+', n5);
		TreeNode n1 = t.makeTree(n2, '+', n3);

 
		System.out.print("전위 순회 출력  : ");
		t.preorder(n1);
		System.out.println();
  
		System.out.print("중위 순위 출력  : ");
		t.inorder(n1);
		System.out.println();

		System.out.print("후위 순위 출력  : ");
		t.postorder(n1);
		System.out.println();

		System.out.println("계산"+t.evaluate(n1));
	}
}