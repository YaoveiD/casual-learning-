#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn],n;
void Merge(int a[],int l,int mid, int r){
    int len1 = mid-l+1,len2 = r-mid;
    int i = 0,j = len1;
    int *c = new int [len1+len2];
    for(int i = 0; i < len1+len2; ++i){
        c[i] = a[l+i];
    }
    while(i<len1&&j<len2+len1){
        if(c[i] < c[j]) a[l++] = c[i++];
        else a[l++] = c[j++];
    }
    while(i<len1) a[l++] = c[i++];
    while(j<len2+len1) a[l++] = c[j++];
    delete []c;
}
void mergesort(int a[],int low, int high){
    if(low<high){
        int mid = (low+high)>>1;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        Merge(a,low,mid,high);
    }
}
int main()
{
	//printf("万恶的中文处理\n");
    cin>>n;
    for(int i = 0;i < n;++i){
        cin>>a[i];
    }
    mergesort(a,0,n-1);
    for(int i = 0;i < n;++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}
