#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int a[maxn],n;
void insertsort(int a[]){
    int i,j,key;
    for(i = 1; i != n; ++i){
        key = a[i];
        j=i-1;
        while(j >= 0 && a[j] > key ){
            a[j+1]=a[j];//±ßÕÒ±ßÒÆ¶¯ 
            --j;
        }
        a[j+1]=key;
    }
}
int main()
{
    cin>>n;
    for(int i = 0;i < n; ++i) cin>>a[i];
    insertsort(a);
    for(int i = 0;i < n; ++i) cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
