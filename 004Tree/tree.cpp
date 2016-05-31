#include <iostream>
#include <fstream>
using namespace std;



template <class elemType>
class linkQueue
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL){data = x;next = N;}
		node():next(NULL){}
		~node(){}
	};
	node *front,*rear;
public:
	linkQueue(){front = rear = NULL;}
	~linkQueue();
	bool isEmpty(){return front == NULL;}
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead(){return front->data;}
};

template <class elemType>
linkQueue <elemType>::~linkQueue()
{
	node *tmp;
	while(front != NULL)
	{
		tmp = front;
		front = front->next;
		delete tmp;
 	}
} 

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if(rear == NULL)front = rear = new node(x);
	else
	{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template <class elemType>
elemType linkQueue <elemType>::deQueue()
{
	node *tmp = front;
	elemType value = front->data;
	front = front->next;
	if(front == NULL)rear = NULL;
	delete tmp;
	return value;
}

template <class elemType>
class linkStack
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL)
		{data=x;next=N;}
		node():next(NULL){}
		~node(){}
	};
	node *elem;
public:
	linkStack(){elem=NULL;}
	~linkStack();
	bool isEmpty() const{return elem==NULL;}
	void push(const elemType &x)
	{
		node *tmp=new node(x,elem);
		elem=tmp;
	}
	elemType pop()
	{
		node *tmp=elem;
		elemType x=tmp->data;
		elem=elem->next;
		delete tmp;
		return x;
	}
	elemType top() const
	{return elem->data;}
};

template <class elemType>
linkStack<elemType>::~linkStack()
{
	node *tmp;
	while(elem!=NULL)
	{
		tmp=elem;
		elem=elem->next;
		delete tmp;
	}
}

template <class Type>
class BinaryTree
{
private:
	struct Node {
		Node *left,*right;
		Type data;
		Node():left(NULL),right(NULL){}
		Node(Type item,Node *L=NULL,Node *R=NULL):
			data(item),left(L),right(R){}
		~Node(){}

	};
	Node *root;
public:
	BinaryTree():root(NULL){}
	BinaryTree(const Type &value){root=new Node(value);}
	~BinaryTree(){clear();}
	void clear(){if(root!=NULL)clear(root);}

	Type getRoot() const {return root->data;}
	Type getLeft() const {return root->left->data;}
	Type getRight() const {return root->right->data;}

	void makeTree(const Type &x,BinaryTree &lt,BinaryTree &rt)
	{
		root=new Node(x,lt.root,rt.root);
		lt.root=NULL;
		rt.root=NULL;
	}
	bool operator==(const BinaryTree &t1)
	{
		linkStack<Node *>s1,s2;
		Node *c1,*c2;
		s1.push(root);
		s2.push(t1.root);
		while(!s1.isEmpty() && !s2.isEmpty())
		{
			c1=s1.pop();
			c2=s2.pop();
			if(c1->data!=c2->data)return false;
			else
			{
				if(c1->right != NULL && c2->right==NULL || 
						c1->right==NULL && c2->right!=NULL)return false;
				else
					if(c1->right != NULL && c2->right != NULL)
					{
						s1.push(c1->right);
						s2.push(c2->right);
					}
				if(c1->left!=NULL && c2->left==NULL || 
						c1->left==NULL && c2->left!=NULL)return false;
				else
					if(c1->left!=NULL && c2->left!=NULL){s1.push(c1->left);s2.push(c2->left);}
			}
		}
		return true;
	}

	bool isEmpty()const {return root==NULL;}
	int size()const{return size(root);}
	int height()const{return height(root);}
	
	void preOrder()const
	{
		if(root!=NULL)
		{
			preOrder(root);
		}
		cout << endl;
	}

	void createTree(Type flag);

private:
	int height(Node *t)const
	{
		if(t==NULL)return 0;
		else
		{
			int lt=height(t->left),rt=height(t->right);
			return 1+((lt>rt)?lt:rt);
		}
	}

	void clear(Node *t)
	{
		if(t->left!=NULL)clear(t->left);
		if(t->right!=NULL)clear(t->right);
		delete t;
	}

	int size(Node *t) const
	{
		if(t==NULL)return 0;
		return 1+size(t->left)+size(t->right);
	}

	void preOrder(Node *t) const
	{
		if(t!=NULL)
		{
			cout << t->data << ' ';
			preOrder(t->left);
			preOrder(t->right);
		}
	}

};

template <class Type>
void BinaryTree<Type>::createTree(Type flag)
{
	int ls[100],rs[100],na[100];
	linkQueue <Node *> que;
	linkQueue <int> que2;
	Node *tmp;
	bool cflag;
	int n,head=0,p,tmp2;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		cin >> ls[i] >> rs[i] >> na[i];
	}
	for(int i=0;i<n;i++)
	{
		cflag=false;
		for(int j=0;j<n;j++)
		{
			if(i==j)continue;
			else
				if(i==ls[j]-1||i==rs[j]-1){cflag=true;break;}
		}
		if(!cflag){head=i;break;}
	}
	root=new Node(na[head]);
	que.enQueue(root);
	que2.enQueue(head);
	while(!que.isEmpty())
	{
		p=0;
		tmp=que.deQueue();
		tmp2=que2.deQueue();
		for(int i=0;i<n;i++)
		{
			if(tmp2==i){p=i;break;}
		}
		if(ls[p]!=flag)
		{
			que.enQueue(tmp->left=new Node(na[ls[p]-1]));
			que2.enQueue(ls[p]-1);
		}
		if(rs[p]!=flag)
		{
			que2.enQueue(rs[p]-1);
			que.enQueue(tmp->right=new Node(na[rs[p]-1]));
		}
 	}
}

int main()
{
	streambuf* backup = cout.rdbuf();
	ifstream in("in.txt");
	ofstream out("out.txt");
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
	BinaryTree<int> t1, t2;
	t1.createTree(0);
	t2.createTree(0);
	t1.preOrder();
	t2.preOrder();
	if(t1 == t2) cout<< "Y" <<endl;
	else cout << "N" << endl;
	cout.rdbuf(backup);
	return 0;
}
