#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct treeNode {
	int val;
	struct treeNode* left;
	struct treeNode* right;
};

struct treeNode *tree_node_init(int val) {
	struct treeNode *node = malloc(sizeof(struct treeNode));
	if (node == NULL)
		return NULL;
	node->val = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int freeTreeNode(struct treeNode *root) {
	if(root)
		free(root);
	return 0;
}

int insertNode(struct treeNode *root, struct treeNode *node) {
	if (root && node) {
		if (node->val < root->val) {
			root->left = node;
		} else {
			root->right = node;
		}
	}
	return 0;
}

struct treeNode *insertNodeByValue(struct treeNode *root, struct treeNode *node) {
	if (node->val < root->val) {
		if (root->left) {
			insertNodeByValue(root->left, node);
		} else {
			root->left = node;
		}
	} else {
		if (root->right) {
			insertNodeByValue(root->right, node);
		} else {
			root->right = node;
		}
	}
	return NULL;
}

//postorder traversal to free all node
struct treeNode *free_all_node(struct treeNode *root) {
	if (root == NULL)
		return NULL;
	free_all_node(root->left);
	free_all_node(root->right);
	printf("try to free %d %p\n", root->val, root);
	free(root);
}

//preorder traversal to print all node
struct treeNode *RootLR(struct treeNode *root) {
	if(root == NULL) {
		return root;
	}
	if (root) {
		printf("%d ", root->val);
	}
	RootLR(root->left);
	RootLR(root->right);
}

struct treeNode *find_val(struct treeNode *root, int val) {
	struct treeNode *tmp = root;
	while(tmp) {
		if(val < tmp->val) {
			tmp = tmp->left;
		} else if (val > tmp->val) {
			tmp = tmp->right;
		} else {
			return tmp;
		}
	}
}

struct treeNode *find_val_of_parent(struct treeNode *root, int val) {
	if (root == NULL || root->val == val) {
		return NULL;
	}
	struct treeNode *tmp = root;
	struct treeNode *parent;
	while(tmp) {
		if(val < tmp->val) {
			parent = tmp;
			tmp = tmp->left;
		} else if (val > tmp->val) {
			parent = tmp;
			tmp = tmp->right;
		} else {
			return parent;
		}
	}
}

// del the val
int del_tree_node(struct treeNode *root, int val) {
	struct treeNode *node = find_val(root, val);
	if ((node->left == NULL) && (node->right == NULL)) {
		struct treeNode *parent_node = find_val_of_parent(root, val);
		if (parent_node) {
			if (parent_node->left == node) {
				free(parent_node->left);
				parent_node->left = NULL;
			} else {
				free(parent_node->right);
				parent_node->right = NULL;
			}
		}
		return 0;
	}
	
	if (node->left && node->right) {
		struct treeNode *parent_node = find_val_of_parent(root, val);
		struct treeNode *left = node->left;
		struct treeNode *right = node->right;

		if (parent_node->left == node) {
			parent_node->left = NULL;
		} else {
			parent_node->right = NULL;
		}
		insertNodeByValue(root, left);
		insertNodeByValue(root, right);
		free(node);	
		return 0;
	}

	if (node->left || node->right) {
		struct treeNode *parent_node = find_val_of_parent(root, val);
		struct treeNode *tmp = node->left != NULL ? node->left: node->right;

		if (parent_node->left == node) {
			parent_node->left = NULL;
		} else {
			parent_node->right = NULL;
		}
		free(node);	
		insertNodeByValue(root, tmp);
	}
	
	return 0;
}

int main()
{
	struct treeNode *root = tree_node_init(12);
	struct treeNode *node1 = tree_node_init(1);
	struct treeNode *node2 = tree_node_init(18);
	struct treeNode *node3 = tree_node_init(17);
	struct treeNode *node4 = tree_node_init(2);
	insertNodeByValue(root, node1);
	insertNodeByValue(root, node2);
	insertNodeByValue(root, node3);
	insertNodeByValue(root, node4);
	insertNodeByValue(root, tree_node_init(0));
	RootLR(root);
	printf("\n");
//	del_tree_node(root, 17);
	del_tree_node(root, 18);
//	del_tree_node(root, 2);
	RootLR(root);
	printf("\n");
	free_all_node(root);
#if 0
	freeTreeNode(root);
	freeTreeNode(node1);
	freeTreeNode(node2);
	freeTreeNode(node3);
	freeTreeNode(node4);
	return 0;
#endif
}
