/**
 * Solve this problem with Trie
 */
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include <map>
#include <vector>
using namespace std;
#define debug(a) #a << " = " << a

const int tree_width = 256;
const int word_len_max = 128;
const char* filename = "info.dat";
char web[word_len_max];
char ip[word_len_max];
/**
 * Definition of Trie
 */
struct trie_node
{
	struct trie_node* next[tree_width];
	char* ip_address;
	int isend;
	int pass;
	trie_node(): isend(0), pass(0), ip_address(nullptr){
		memset(next, 0, sizeof(next));
	}
};

void my_free(trie_node* root){
	for (int i = 0; i < tree_width; ++i) {
		if (root->next[i]) {
			my_free(root->next[i]);
			if (root->ip_address) {
				delete []root->ip_address;
			}
			root->next[i] = nullptr;
		}
	}
	delete root;
}

void insert(trie_node* &root, const char* name, const char* ip){
	int len = strlen(name), idx;
	trie_node* curr = root;
	for (int i = 0; i < len; ++i) {
		idx = name[i];
		curr->pass++;
		if (curr->next[idx] == nullptr) {
			curr->next[idx] = new trie_node;
		}
		curr = curr->next[idx];
	}
	curr->isend = 1;
	int ip_len = strlen(ip);
	curr->ip_address = new char[ip_len + 1];
	strcpy(curr->ip_address, ip);
}

void search(trie_node* root, const char* name){
	int len = strlen(name), idx;
	for (int i = 0; i < len; ++i) {
		idx = name[i];
		if (root->next[idx] == nullptr) {
			puts("NOT FOUND!");
			return;
		}
		root = root->next[idx];
	}
	if (root->isend) {
		puts("ip:");
		puts(root->ip_address);
	}
	else {
		puts("NOT FOUND!");
	}
}

int read_from_file(trie_node* &root, const char* filename){
	if (FILE *fp = fopen(filename, "r")) {
		while (!feof(fp)) {
			fread(web, 1, word_len_max, fp);
			fread(ip, 1, word_len_max, fp);
			insert(root, web, ip);
		}
		fclose(fp);
	}
	else {
		puts("Error");
		exit(-1);
	}
}

void write_to_file(const char* web, const char* ip, const char* filename){
	if (FILE* fp = fopen(filename, "a+")) {
		fwrite(web, 1, word_len_max, fp);
		fwrite(ip, 1, word_len_max, fp);
	}
	else {
		puts("Can't Find File");
	}
}
int main(int argc, char * argv[])
{

	int opt;
	trie_node* root = new trie_node;
	read_from_file(root, filename);
	while (1) {
		puts("1: insert website\n");
		puts("2: query website\n");
		puts("others: quit\n");
		cin >> opt;
		if (opt == 1) {
			puts("input website");
			cin >> web;
			puts("input ip");
			cin >> ip;
			write_to_file(web, ip, filename);
			insert(root, web, ip);
		}
		else if (opt == 2) {
			puts("input website");
			cin >> web;
			search(root, web);
		}
		else {
			break;
		}
	}
	my_free(root);
	return 0;
}