#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <queue>
#include <map>
#include <vector>
using namespace std;
#define debug(a) #a << " = " << a

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

static int nodes[100] = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, -1};//-1: null, nodes: valid
static int idx = 0;

//creat binary tree
TreeNode* PreorderCreat(){
	int value = nodes[idx++];
	TreeNode* treenode;
	if (-1 == value) {
		treenode = nullptr;
	}
	else{
		treenode = new TreeNode(value);
		treenode->left = PreorderCreat();
		treenode->right = PreorderCreat();
	}
	return treenode;
}

// recursive preorder traverse binary tree
void PrerderTraverse(TreeNode* root){
	if (root == nullptr) {
		return; 
	}
	cout << root->val <<" ";
	PrerderTraverse(root->left);
	PrerderTraverse(root->right);
}

// non-recursive preorder traverse bt
void PrerderTraverse2(TreeNode* root){
	stack<TreeNode*> s;
	TreeNode* p = root;
	while (p || !s.empty()) {
		if (p) {
			cout << p->val << " ";
			s.push(p);
			p = p->left;
		}
		else{
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
}

// non-recursive inorder traverse bt
void InorderTraverse(TreeNode* root){
	stack<TreeNode*> s;
	TreeNode* p = root;
	while (p || !s.empty()) {
		if (p) {
			s.push(p);
			p = p->left;
		}
		else {
			p = s.top();
			s.pop();
			cout << p->val << " ";
			p = p->right;
		}
	}
}

//non-recursive postorder traverse bt
void PostorderTraverse(TreeNode* root){
	stack<TreeNode*> s;
	TreeNode* p = root, *r = nullptr;
	while (p || !s.empty()) {
		if (p) {//push left until null
			s.push(p);
			p = p->left;
		}
		else {
			p = s.top();//get topnode
			if (p->right && p->right != r) { // right subtree and right subtree is not visited, turn right subtree
				p = p->right;
				s.push(p);
				p = p->left;
			}
			else {//right is null or right is visited, visit topnode
				p = s.top();
				s.pop();
				cout << p->val << " ";
				r = p;//p is visited
				p = nullptr;
			}
		}
	}
}

//level traverse

void LevelTraverse(TreeNode* root){
	queue<TreeNode*> q;
	TreeNode* p;
	q.push(root);
	while (!q.empty()) {
		p = q.front();
		q.pop();
		if (p) {
			cout << p->val << " ";
			q.push(p->left);
			q.push(p->right);
		}
	}
}

void test(){
	TreeNode* root = PreorderCreat();
	cout << "PrerderTraverse recursive" << endl;
	PrerderTraverse(root);
	cout << endl;
	cout << "PrerderTraverse non-recursive" << endl;
	PrerderTraverse2(root);
	cout << endl;
	cout << "InorderTraverse non-recursive" << endl;
	InorderTraverse(root);
	cout << endl;
	cout << "PostorderTraverse non-recursive" << endl;
	PostorderTraverse(root);
	cout << endl;
	cout << "LevelTraverse" << endl;
	LevelTraverse(root);
	cout << endl; 
}

int main(int argc, char * argv[])
{
	ios::sync_with_stdio(false);
	cout.tie(0);
	test();
	return 0;
}