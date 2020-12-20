#include <iostream>
#include <stdio.h>
#include <string.h>
//using namespace std;

const int maxn = 1005;
char s[maxn], p[maxn];
int next[maxn];

void GetNext(char *p, int next[]){
	int lenp = strlen(p);
	int k = -1, j = 0;
	next[0] = -1;
	while (j < lenp - 1) {
		if (k == -1 || p[k] == p[j]) {
			++k;
			++j;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
}

int kmp(char *s, char *p){
	int lens = strlen(s), lenp = strlen(p);
	int i = 0, j = 0;
	while(i < lens && j < lenp) {
		if (j == -1 || s[i] == p[j]) {
			++i;
			++j;
		}
		else {
			j = next[j];
		}
	}
	return j == lenp ? i - j : -1;
}

int main(int argc, char const *argv[])
{
	scanf("%s %s", s, p);
	GetNext(p, next);
	printf("%d\n", kmp(s, p));
	return 0;
}