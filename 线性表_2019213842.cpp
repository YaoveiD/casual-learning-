#include <bits/stdc++.h>
using namespace std;
#define SIZE 100
#define INCRE 10
inline void nextline(){
	cout << "-----------------------------------------------" << endl;
}
typedef struct {
	int *elem;
	int size, len;
}Sqlist;
void Init(Sqlist &L)
{
	L.elem = new int [SIZE];
	L.len = 0;
	L.size = SIZE;
}
int Destory(Sqlist &L)
{
	L.len = 0;
	L.size = 0;
	delete []L.elem;
}
int Clear(Sqlist &L)
{
	L.len = 0;
	return 1;
}
int Empty(Sqlist L)
{
	return L.len == 0;
}
int Length(Sqlist L)
{
	return L.len;
}
int GetElem(Sqlist L, int i, int &e)
{
	e = L.elem[i-1];
	return 1;
}
int Locate(Sqlist L, int e)
{
	int i;
	for (int i = 0; i < L.len; ++i){
		if (L.elem[i] == e){
			return i+1;
		}
	}
	return 0;
}
int Insert(Sqlist &L, int i , int e)
{
	if (i < 1 || i > L.len+1){
		return 0;
	}
	if (L.len > L.size){
		int *newbase = (int *)realloc(L.elem, (L.size + INCRE)*sizeof(int));
		if (newbase == NULL){
			return 0;
		}
		L.elem = newbase;
		L.size = L.size + INCRE;
	}
	for (int j = L.len; j >= i; --j){
		L.elem[j] = L.elem[j-1];
	}
	L.elem[i-1] = e;
	++L.len;
	return 1;
}
int Delete(Sqlist &L, int i, int &e)
{
	if (i < 1 || i > L.len){
		return 0;
	}
	e = L.elem[i-1];
	for (int j = i; j < L.len; ++j){
		L.elem[j-1] = L.elem[j];
	}
	--L.len;
	return 1;
}
int Pre(Sqlist L, int x, int &e)
{
	int i = Locate(L, x);
	if (i <= 1){
		return 0;
	}
	e = L.elem[i-2];
	return 1;
}
int Nex(Sqlist L, int x, int &e)
{
	int i = Locate(L, x);
	if(i >= L.len){
		return 0;
	}
	e = L.elem[i];
	return 1;
}
void print(Sqlist L)
{
    for (int i = 0; i < L.len; ++i) {
        printf("%d\t",L.elem[i]);
    }
    printf("\n");
}
int main()
{
    Sqlist L;
    int e;
    Init(L);
    for (int i = 0; i < 10; ++i) {
        L.elem[i] = i + 1;
        ++L.len;
    }
    printf("List:\n");
    print(L);
    nextline();
    printf("after Delete, index = 3:\n");
    Delete(L,3,e);
    print(L);
    nextline();
    printf("after Insert 11, index = 4\n");
    Insert(L,4,11);
    print(L);
    nextline();
    printf("Getelem, index = 6\n");
    GetElem(L,6,e);
    printf("e = %d\n",e);
    nextline();
    printf("index of 7:\n");
    printf("L.elem[%d] = 7\n",Locate(L,7) - 1);
    nextline();
    Pre(L,5,e);
    printf("Preelem of 5 is %d\n", e);
    nextline();
    Nex(L,5,e);
    printf("Nextelem of 5 is %d\n", e);
    nextline();
    printf("Destory\n");
    Destory(L);
	return 0;
}
