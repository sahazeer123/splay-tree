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
	Splay_node *rotateRight(Splay_node *);
	Splay_node *leftRotate(Splay_node *);
	Splay_node *splay(Splay_node *,int);
	int find(Splay_node *,int);
	void post_orderHelp(Splay_node *,vector<int>&);
	void pre_orderHelp(Splay_node *,vector<int>&);
	void freeTree(Splay_node *);
	Splay_node *removeHelp(Splay_node *,int);
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
Splay_node *splay_tree_implementation::rotateRight(Splay_node *x) 
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
    if (rootSrc == NULL || rootSrc->data == element)  
        return rootSrc;  
    if (rootSrc->data > element)  
    { 
        if (rootSrc->left == NULL) return rootSrc;   
        if (rootSrc->left->data > element)  
        {   
            rootSrc->left->left = splay(rootSrc->left->left, element);
            rootSrc = rotateRight(rootSrc);  
        }  
        else if (rootSrc->left->data< element)   
        {    
            rootSrc->left->right = splay(rootSrc->left->right, element);  
            if (rootSrc->left->right != NULL)  
                rootSrc->left = leftRotate(root->left);  
        }   
        return (rootSrc->left == NULL)? rootSrc: rotateRight(rootSrc);  
    }  
    else 
    {   
        if (rootSrc->right == NULL) return rootSrc;  
        if (rootSrc->right->data > element)  
        {    
            rootSrc->right->left = splay(rootSrc->right->left, element);  
            if (rootSrc->right->left != NULL)  
                rootSrc->right = rotateRight(rootSrc->right);  
        }  
        else if (rootSrc->right->data < element) 
        {   
            rootSrc->right->right = splay(rootSrc->right->right,element);  
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
	return find(rootSrc -> left,element) || find(rootSrc -> right,element);
}
void splay_tree_implementation::insert(int element)
{
	if(root == NULL)
	{
		no_nodes++;
		root = createNode(element);
		return ;
	}
	root = splay(root,element);
	if(root -> data == element)
	{
		return ;
	}
	Splay_node *newNode = createNode(element);
	no_nodes++;
	if(element < root -> data)
	{
		newNode -> right = root;
		newNode -> left = root -> left;
		root -> left = NULL;
	}
	else
	{
		newNode -> left = root;
		newNode -> right = root -> right;
		root -> right = NULL;
	}
	root = newNode;
}
void splay_tree_implementation::remove(int element)
{
	root = removeHelp(root,element);
}
Splay_node *splay_tree_implementation::removeHelp(Splay_node *rootSrc,int element)
{
	Splay_node *temp;
	if(rootSrc == NULL)
		return NULL;
	rootSrc = splay(rootSrc,element);
	if(element != rootSrc -> data)
	{
		return rootSrc;
	}
	if(!rootSrc -> left)
	{
		temp = rootSrc;
		rootSrc = rootSrc -> right;
	}
	else
	{
		temp = rootSrc;
		rootSrc = splay(rootSrc -> left,element);
		root -> right = temp -> right;
	}
	free(temp);
	no_nodes--;
	return rootSrc;
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
void splay_tree_implementation::pre_orderHelp(Splay_node *root,vector<int>&result)
{
	if(root != NULL)
	{
		result.push_back(root -> data);
		pre_orderHelp(root -> left,result);
		pre_orderHelp(root -> right,result);
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