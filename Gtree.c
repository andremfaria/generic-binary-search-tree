#include "Gtree.h"


typedef struct StTree
{
	void * data;
	struct StTree * left;	
	struct StTree * right;
}STree, *Ptree;


struct StBinTree
{
	int length;
	Ptree root;
	int (*compare) (void*,void*);
	char* (*get_value_key) (void*);
	char* (*to_string)(void*);
	size_t size;
};

int init_g_tree(PbinTree * binTree,size_t dataSize, int (*compare) (void*,void*),
	char* (*get_value_key) (void*), char* (*to_string) (void*)) 	
{
	 (*binTree) = (PbinTree) malloc (sizeof (struct StBinTree));
	 if( *binTree == NULL)
	 	return 1;

	(*binTree)->size = dataSize;
	(*binTree)->compare = compare;
	(*binTree)->get_value_key = get_value_key;
	(*binTree)->to_string = to_string;
	(*binTree)->root = NULL;
	(*binTree)->length = 0;

	return 0;
};

Ptree insert_aux(PbinTree ctrl,Ptree tree, void* data, int *res)
{
	
	if(tree == NULL)
	{
		
		Ptree new = (Ptree) malloc (sizeof (struct StTree));
		if(new == NULL)
			*res = 1;
		new->data = malloc(ctrl->size);
		if(new->data == NULL)
			*res = 1;

		memcpy(new->data,data,ctrl->size);
		new->left = NULL;
		new->right = NULL;
		ctrl->length++;
		return new;
	}
	

	if(ctrl->compare(tree->data,data) > 0)
	{	
		printf("New value %s is lower than the actual value in tree %s, inserting at left.\n",ctrl->to_string(data),ctrl->to_string(tree->data));
		tree->left =  insert_aux(ctrl,tree->left, data,res);
	}
	else if(ctrl->compare(tree->data,data) < 0)
	{
		printf("New value %s is greater than the actual value in tree %s, inserting at right.\n",ctrl->to_string(data),ctrl->to_string(tree->data));
		 tree->right = insert_aux(ctrl,tree->right, data,res);	
	}


	return tree;
}

int insert(PbinTree ctrl, void* data){
	int res=0;
	ctrl->root = insert_aux(ctrl,ctrl->root,data, &res);
	return res;
}

void list_pre_order_aux(PbinTree ctrl,Ptree tree)
{
	if(tree == NULL)
		return;

	printf("%s", ctrl->to_string(tree->data));
	list_pre_order_aux(ctrl,tree->left);
	list_pre_order_aux(ctrl,tree->right);
}

void list_pre_order(PbinTree tree)
{
	list_pre_order_aux(tree,tree->root);
}

void list_pos_order_aux(PbinTree ctrl, Ptree tree)
{
	if(!tree) 	
		return;

	list_pos_order_aux(ctrl,tree->left);
	list_pos_order_aux(ctrl,tree->right);
	printf("%s",ctrl->to_string(tree->data));

}

void list_pos_order(PbinTree tree)
{
	list_pos_order_aux(tree,tree->root);
}


void list_in_order_aux(PbinTree ctrl, Ptree tree)
{
	if(!tree) 	
		return;

	list_in_order_aux(ctrl,tree->left);
	printf("%s",ctrl->to_string(tree->data));
	list_in_order_aux(ctrl,tree->right);
}

void list_in_order(PbinTree tree)
{
	list_in_order_aux(tree,tree->root);
}

int get_element(PbinTree ctrl, void* searchElem,void* data)
{
	Ptree iterator = ctrl->root;
	int compare;

	while(iterator)
	{
		compare = ctrl->compare(iterator->data,searchElem);
		if(compare == 0)
		{
			memcpy(data,iterator->data,ctrl->size);
			return 0;
		}

		if(compare < 0)
			iterator = iterator->right;
		else
			iterator = iterator->left;

	}

	return -1;
}

int get_size(PbinTree tree)
{
	return tree->size;
}
Ptree get_suc_min(Ptree ptree)
{
	Ptree iterator = ptree, last=NULL;

	for(;iterator!=NULL;last=iterator,iterator=iterator->left);

	return last;
}

Ptree get_pre_max(Ptree ptree)
{
	Ptree iterator = ptree, last=NULL;

	for(;iterator!=NULL;last=iterator,iterator=iterator->right);

	return last;
}

Ptree delete_element_aux(PbinTree ctrl, Ptree tree, void* remElement, Ptree last, int*	 res)
{
	Ptree tmpTree = tree;
	//Null case
	if(!tree)
		return NULL;

	int compare = ctrl->compare(tree->data,remElement);

	//remElement is bigger that the actual. Going right.
	if(compare < 0)
		tree->right = delete_element_aux(ctrl, tree->right,remElement,tree,res);
	//remElement is bigger that the actual. Going left.
	else if (compare > 0)
		tree->left = delete_element_aux(ctrl, tree->left,remElement,tree,res);
	//Equals case
	else
	{	
		*res = 0;
		if(tree->left==NULL)
		{
			tmpTree = tree->right;
			free(tree);
			tree=NULL;
			return tmpTree;
		}
		else if (tree->right==NULL)
		{
			tmpTree = tree->left;
			free(tree);
			tree=NULL;
			return tmpTree;		
		}
		//Find sucMin of atual value, set the atual value, and delete that min
		Ptree treeMin = get_pre_max(tree->left);
		tree->data = treeMin->data;
		tree->left = delete_element_aux(ctrl,tree->left,treeMin->data,tree,res);

	}

	return tree;
}

int delete_element(PbinTree ctrl, void* remElement)
{	
	int res = 1;
	ctrl->root = delete_element_aux(ctrl, ctrl->root, remElement, ctrl->root, &res);
	return res;	
}
