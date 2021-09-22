#include<stdio.h>
#include<stdlib.h>
typedef struct node Node;
struct node {
	int data;
	Node *parent;
	Node *left;
	Node *right;
};

Node *create_node(int item) {
	Node *new_node = (Node *) malloc(sizeof(Node));
	
	if(new_node == NULL) {
		printf("Error! Unable to create a new node.");
		exit(1);
	}
	
	new_node->data = item;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	
	return new_node;
}

void add_left_child(Node *node, Node *child) {
	node->left = child;
	if(child != NULL) {
		child->parent=node;
	}
}

void add_right_child(Node *node, Node *child) {
	node->right = child;
	if(child != NULL) {
		child->parent = node;
	}
}

Node *bst_insert(Node *root, Node *node) {
	if(root == NULL) {
		root = node;
		return root;
	}
	
	Node *current_node, *parent_node;
	current_node = root;
	while(current_node != NULL) {
		parent_node = current_node;
		
		if(node->data < current_node->data) {
			current_node = current_node->left;
		} else {
			current_node = current_node->right;
		}
	}
	
	if(node->data < parent_node->data) {
		add_left_child(parent_node, node);
	} else {
		add_right_child(parent_node, node);
	}
	return root;
}

Node *create_bst() {
	Node *root, *node;
	int ara[] = {5, 17, 3, 6, 12, 19, 1, 4};
	
	root = create_node(10);
	for(int i=0; i<8; i++) {
		node = create_node(ara[i]);
		root = bst_insert(root, node);
	}
	return root;
}

void pre_order(Node *node) {
	printf("%d ", node->data);
	
	if(node->left != NULL)
		pre_order(node->left);
		
	if(node->right != NULL)
		pre_order(node->right);
}

void in_order(Node *node) {
	if(node->left != NULL) 
		in_order(node->left);
	
	printf("%d ", node->data);
	
	if(node->right != NULL)
		in_order(node->right);
}

void post_order(Node *node) {
	if(node->left != NULL)
		post_order(node->left);
		
	if(node->right != NULL)
		post_order(node->right);
		
	printf("%d ", node->data);
}

int main() {
	Node *root = create_bst();
	
	pre_order(root); 
	printf("\n");
	post_order(root);
	printf("\n");
	in_order(root);
	printf("\n");
}
