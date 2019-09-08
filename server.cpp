#include "header.hpp"
#include <iostream>
using namespace std;
#include <vector>
class Splay_node
{
public:
	int data;
	Splay_node *left;
	Splay_node *right;
};

class splay_tree_implementation : public splay_tree
{
private:
	int no_nodes;
	Splay_node *root;
	Splay_node *createNode(int);
	Splay_node *rightRotate(Splay_node *);
	Splay_node *leftRotate(Splay_node *);
	Splay_node *splay(Splay_node *,int);
	int find(Splay_node *,int);
	void post_orderHelp(Splay_node *,vector<int>&);
	void pre_orderHelp(Splay_node *,vector<int>&);
	void freeTree(Splay_node *);
	void removeHelp(Splay_node *&,int);
	Splay_node * bstSearch(Splay_node *,int);
	Splay_node * bstInsert(Splay_node *,int);
	Splay_node * minValNode(Splay_node *);
	void searchKey(Splay_node *&,int,Splay_node *&);
	void delete_dup(Splay_node *,int);
public:
	splay_tree_implementation();
	int get_num_nodes();
	int find(int);
	void insert(int);
	void remove(int);
	vector<int>post_order();
	vector<int>pre_order();
	~splay_tree_implementation();
};
splay_tree_implementation::splay_tree_implementation()
{
	no_nodes = 0;
	root = NULL;
}
int splay_tree_implementation::get_num_nodes()
{
	return no_nodes;
}
Splay_node *splay_tree_implementation::createNode(int data)
{
	Splay_node *node = new Splay_node();
	node -> data = data;
	node -> left = node -> right = NULL;
	return node;
}
Splay_node *splay_tree_implementation::rightRotate(Splay_node *x) 
{  
    Splay_node *y = x->left;  
    x->left = y->right;  
    y->right = x;  
    return y;  
}
Splay_node *splay_tree_implementation::leftRotate(Splay_node *x)  
{  
    Splay_node *y = x->right;  
    x->right = y->left;  
    y->left = x;  
    return y; 
}
Splay_node *splay_tree_implementation::splay(Splay_node *rootSrc,int element)
{  
     if (rootSrc== NULL || rootSrc->data == element)  
        return rootSrc;  
    if (rootSrc->data > element)  
    {   
        if (rootSrc->left == NULL) return rootSrc;    
        if (rootSrc->left->data > element)  
        {  
            rootSrc->left->left = splay(rootSrc->left->left, element);    
            rootSrc = rightRotate(rootSrc);  
        }  
        else if (rootSrc->left->data < element)  
        {  
            rootSrc->left->right = splay(rootSrc->left->right, element);    
            if (rootSrc->left->right != NULL)  
                rootSrc->left = leftRotate(rootSrc->left);  
        }   
        return (rootSrc->left == NULL)? rootSrc: rightRotate(rootSrc);  
    }  
    else
    {   
        if (rootSrc->right == NULL) return rootSrc;    
        if (rootSrc->right->data > element)  
        {   
            rootSrc->right->left = splay(rootSrc->right->left, element);  
            if (rootSrc->right->left != NULL)  
                rootSrc->right = rightRotate(rootSrc->right);  
        }  
        else if (rootSrc->right->data < element) 
        {    
            rootSrc->right->right = splay(rootSrc->right->right, element);  
            rootSrc = leftRotate(rootSrc);  
        }   
        return (rootSrc->right == NULL)? rootSrc: leftRotate(rootSrc);  
    }  
}  
int splay_tree_implementation::find(int element)
{
	root = splay(root,element);
	return find(root,element);
}
int splay_tree_implementation::find(Splay_node * rootSrc,int element)
{
	if(rootSrc == NULL)
		return 0;
	if(rootSrc -> data == element)
		return 1;
	if(element < rootSrc -> data)
		return find(rootSrc -> left,element);
	else
		return find(rootSrc -> right,element);
}
Splay_node * splay_tree_implementation::bstSearch(Splay_node *rootSrc,int element)
{
	if(rootSrc == NULL || rootSrc -> data == element)
		return rootSrc;
	if(element < rootSrc -> data)
		return bstSearch(rootSrc -> left,element);
	else
		return bstSearch(rootSrc -> right,element);
}
Splay_node * splay_tree_implementation::bstInsert(Splay_node *rootSrc,int element)
{
	if(rootSrc == NULL)
	{
		rootSrc = createNode(element);
		return rootSrc;
	}
	if(element < rootSrc -> data)
		rootSrc -> left = bstInsert(rootSrc -> left,element);
	else
		rootSrc -> right = bstInsert(rootSrc -> right,element);
	return rootSrc;
}
void splay_tree_implementation::insert(int element)
{
	Splay_node * temp = bstSearch(root,element);
	if(temp != NULL)
	{
		root = splay(root,element);
		return ;
	}
	else
	{
		no_nodes++;
		root = bstInsert(root,element);
		root = splay(root,element);
	}
}
void splay_tree_implementation::remove(int element)
{
	Splay_node * parent = NULL;
	Splay_node * current = root;
    removeHelp(parent,element);
    if(parent == nullptr)
    	return ;
    else
    	root = splay(root,parent -> data);
}
void splay_tree_implementation::searchKey(Splay_node *&current,int element,Splay_node * &parent)
{
	while(current != nullptr && current -> data != element)
	{
		parent = current;
		if(element < current -> data)
			current = current -> left;
		else
			current = current -> right;
	}
}
void splay_tree_implementation::removeHelp(Splay_node *&parent,int element)
{
	Splay_node * current = root;
	if(root == NULL)
		return ;
	searchKey(current,element,parent);
	if(current == NULL)
		return ;
	no_nodes--;
	if(current -> left == nullptr && current -> right == nullptr)
	{
		if(current != root)
		{
			if(parent -> left == current)
				parent -> left = nullptr;
			else
				parent -> right = nullptr;
		}
		else
			root = nullptr;
		free(current);
	}
	else if(current -> left && current -> right)
	{
		Splay_node * successor = minValNode(current -> right);
		int val = successor -> data;
		current -> data = val;
		delete_dup(current,val);
	}
	else
	{
		Splay_node * child = (current -> left) ? current -> left : current -> right;
		if(current != root)
		{
			if(current == parent -> left)
				parent -> left = child;
			else
		        parent -> right = child;
		}
		else
		   root = child;
		free(current);
	}
}
void splay_tree_implementation::delete_dup(Splay_node *rootSrc,int element)
{
	Splay_node *parent1 = rootSrc;
	Splay_node *current1 = rootSrc -> right;
	if(rootSrc == nullptr)
		return;
	searchKey(current1,element,parent1);
	if(current1 -> left == nullptr && current1 -> right == nullptr)
	{
		if(current1 != root)
		{
			if(parent1 -> left == current1)
				parent1 -> left = nullptr;
			else
				parent1 -> right = nullptr;
		}
		else
			root = nullptr;
		free(current1);
	}
	else
	{
		Splay_node * child = (current1 -> left) ? current1 -> left : current1 -> right;
		if(current1 != root)
		{
			if(current1 == parent1 -> left)
				parent1 -> left = child;
			else
		        parent1 -> right = child;
		}
		else
		   root = child;
		free(current1);
	}
}
Splay_node *splay_tree_implementation::minValNode(Splay_node *rootSrc)
{
	Splay_node *current = rootSrc;
	while(current && current -> left)
	{
		current = current -> left;
	}
	return current;
}
vector<int> splay_tree_implementation::post_order()
{
	vector<int>result;
	post_orderHelp(root,result);
	return result;
}
void splay_tree_implementation::post_orderHelp(Splay_node *root,vector<int>&result)
{
	if(root != NULL)
	{
		post_orderHelp(root -> left,result);
		post_orderHelp(root -> right,result);
		result.push_back(root -> data);
	}
}
vector<int> splay_tree_implementation::pre_order()
{
	vector<int>result;
	pre_orderHelp(root,result);
	return result;
}
void splay_tree_implementation::pre_orderHelp(Splay_node *rootSrc,vector<int>&result)
{
	if(rootSrc != NULL)
	{
		result.push_back(rootSrc -> data);
		pre_orderHelp(rootSrc -> left,result);
		pre_orderHelp(rootSrc -> right,result);
	}
}
splay_tree_implementation::~splay_tree_implementation()
{
	freeTree(root);
}
void splay_tree_implementation::freeTree(Splay_node * rootSrc)
{
	if(rootSrc == NULL)
		return;
	freeTree(rootSrc -> left);
	freeTree(rootSrc -> right);
	delete root;
}
