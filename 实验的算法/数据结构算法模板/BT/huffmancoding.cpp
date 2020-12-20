//https://www.programiz.com/dsa/huffman-coding
//https://www.techiedelight.com/huffman-coding
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode{
	char ch;
	int freq;
	TreeNode *left, *right;
   	TreeNode(char ch, int freq, TreeNode *left = nullptr, TreeNode *right = nullptr)
   	:ch(ch), freq(freq), left(left), right(right) {}
};

// Comparison object to be used to order the heap
struct cmp{
	bool operator()(TreeNode *l, TreeNode *r){
		return l->freq > r->freq;
	}
};

bool isleaf(TreeNode *root){
	return root->left == nullptr && root->right == nullptr;
}

void encode(TreeNode *root, string code, unordered_map<char, string> &HuffmanCode){
	if (root == nullptr) {
		return;
	}
	if (isleaf(root)) {
		HuffmanCode[root->ch] = code;
	}
	encode(root->left, code + "0", HuffmanCode);
	encode(root->right, code + "1", HuffmanCode);
}

void decode(TreeNode *root, int &index, const string &str){
	if (root == nullptr) {
		return;
	}
	if (isleaf(root)) {
		cout << root->ch;
		return;//decode one character at a time 
	}
	++index;
	if (str[index] == '0') {
		decode(root->left, index, str);
	}
	else {
		decode(root->right, index, str);
	}
}

TreeNode* buildHuffmanTree(const string &text){
	if (text == "") {
		return nullptr;
	}
	unordered_map<char, int> freq;
	for (char ch: text) {
		++freq[ch];
	}
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> pq;
	TreeNode *treenode;
	for (auto pair: freq) {
		treenode = new TreeNode(pair.first, pair.second);
		pq.push(treenode);
	}
	while (pq.size() != 1) {
		TreeNode *left = pq.top(); pq.pop();
		TreeNode *right = pq.top(); pq.pop();
		int sum = left->freq + right->freq;
		treenode = new TreeNode('\0', sum, left, right);
		pq.push(treenode);
	}
	treenode = pq.top();
	return treenode;
}

void getHuffmanCode(TreeNode *root, unordered_map<char, string> &huffmancode) {
	encode(root, "", huffmancode);
	cout << "Huffman Codes are:\n" << '\n';
	for (auto pair: huffmancode) {
		cout << pair.first << " " << pair.second << '\n';
	}
}

void getOriginalStr(TreeNode *root, const string &codes){
	if (isleaf(root)) {
		for (int i = 0; i < root->freq; ++i) {
			cout << root->ch;
		}
	}
	else {
		int index = -1;
		int len = codes.size();//因为codes.size()返回类型时size_t()，-1 与之比较会得到我们不想要的结果
								//所以转换一下
		while (index < len - 1) {
			decode(root, index, codes);
		}
	}
}

/**
 * [test description]
 * a test for the program 
 */

void test(){
	unordered_map<char, string> huffmancode;
	string text = "Huffman coding is a data compression algorithm.";
	TreeNode *root = buildHuffmanTree(text);
	getHuffmanCode(root, huffmancode);
	string codes;
	for (char ch: text) {
		codes += huffmancode[ch];
	}
	cout << "\nEncoded string is:\n" << codes << '\n';
	cout << "\nDecoded string is:\n";
	getOriginalStr(root, codes);
}

int main(int argc, char const *argv[])
{
	test();
	return 0;
}