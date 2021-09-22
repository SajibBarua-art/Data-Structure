#include<stdio.h>
#include<stdlib.h>
typedef struct node Node;
struct node {
	int data;
	Node *parent;
	Node *left;
	Node *right;
};

Node *bst_search(Node *root, int item) {
	Node *node = root;
	while(node != NULL) {
		if(node->data == item)
			return node;
		else if(node->data > item)
			node = node->left;
		else node = node->right;
	}
	return node;
}

int main() {
    // For finding the create_bst() function see the no:1 code
	Node *root = create_bst();
	
	Node *node = bst_search(root, 5);
	if(node == NULL) {
		printf("Node not found!\n");
	} else {
		printf("%d\n", node->data);
	}
	
	node = bst_search(root, 8);
	if(node == NULL) {
		printf("Node not found!\n");
	} else {
		printf("%d\n", node->data);
	}
}