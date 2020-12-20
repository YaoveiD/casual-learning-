#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int a[maxn],n;
int Partition(int a[],int low,int high){
    int piovt = a[low];
    while(low < high){
        while(low < high && a[high] > piovt) --high;
        a[low] = a[high];
        while(low < high && a[low] < piovt) ++low;
        a[high] = a[low];
    }
    a[low] = piovt;
    return high;
}
void quicksort(int a[],int low,int high){
    if(low < high){
        int key = Partition(a,low,high);
        quicksort(a,low,key-1);
        quicksort(a,key+1,high);
    }
    return;
}
int main()
{
    cin>>n;
    for(int i = 0; i < n; ++i) cin>>a[i];
    quicksort(a,0,n-1);
    for(int i = 0; i < n; ++i) cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}

