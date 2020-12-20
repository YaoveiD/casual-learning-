#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int a[maxn],n;
int bubblesort(int a[]){
    int ok = 0,cnt = 1;
    while(!ok){
        ok=1;
        for(int i = 1;i < n-cnt;++i){
            if(a[i]>a[i+1]) swap(a[i],a[i+1]),ok=0;
        }
        ++cnt;
    }
    return ok;
}
int main()
{
    cin>>n;
    for(int i = 0;i < n; ++i) cin>>a[i];
    bubblesort(a);
    for(int i = 0;i < n; ++i) cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
