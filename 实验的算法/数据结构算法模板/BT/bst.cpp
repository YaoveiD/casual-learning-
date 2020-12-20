#include <iostream>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int val):val(val), left(nullptr), right(nullptr){

	}
};

int insert(TreeNode* &root, int val){
	if (!root) {
		root = new TreeNode(val);
		return 1;
	}
	else if (val == root->val) {
		return 0;
	}
	else if (val < root->val) {
		return insert(root->left, val);
	}
	else {
		 return insert(root->right, val);
	}
}

TreeNode* search(TreeNode *root, int val){
	if (!root || val == root->val) {
		return root;
	}
	if (val < root->val) {
		search(root->left, val);
	}
	else {
		search(root->right, val);
	}
}

void traverse(TreeNode *root){
	if (!root) { 
		return;
	}
	traverse(root->left);
	cout << root->val << " ";
	traverse(root->right);
}

void delete_node(TreeNode* &root) {
	TreeNode *p = root;
	if (root->left && root->right) {
		TreeNode *successor = root->right;//lestmost node in the right subtree
		while (successor->left) {
			p = successor;
			successor = successor->left;
		}
		root->val = successor->val;//披着successor外衣的root
		if (p != root) {
			p->left = successor->left;
		}
		else {//successor是p->right,所以得重新接右子树
			p->right = successor->right;
		}
		delete successor;
	}
	else if (root->left) {
		p = root->left;
		root->val = p->val;
		root->left = p->left;
		root->right = p->right;
		delete p;
	}
	else if (root->right) {
		p = root->right;
		root->val = p->val;
		root->left = p->left;
		root->right = p->right;
		delete p;
	}
	else {
		delete root;
		root = nullptr;
	}
}

int deletion(TreeNode* &root, int val){
	if (!root) {
		return 0;
	}
	else {
		if (val == root->val) {
			delete_node(root);
			
			return 1;
		}
		else if (val < root->val) {
			deletion(root->left, val);
		}
		else {
			deletion(root->right, val);
		}
	}
}

int main(int argc, char const *argv[])
{
	TreeNode *root = nullptr;
	int values[] = {5, 3, 1, 6, 2, 4, 0, 7, 9, 8};
	int len = sizeof(values) / sizeof(int*);
	for (int i = 0; i < len; ++i) {
		insert(root, values[i]);
	}
	traverse(root);
	cout << endl;
	return 0;
}