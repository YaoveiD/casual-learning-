#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1005;
int arr[maxn], len;

void max_heapify(int arr[], int start, int end){
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && arr[son] < arr[son + 1]) {
			++son;//选择更大的子节点
		}
		if (arr[dad] > arr[son]) {
			return;//父节点大与子节点，完成
		}
		else {
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void HeadSort(int arr[], int len){
	for (int i = len / 2 - 1; i >= 0; --i) {
		max_heapify(arr, i, len - 1);
	}//从最后一个父节点开始调整，建立大顶堆
	for (int i = len - 1; i > 0; --i) {
		swap(arr[i], arr[0]);
		max_heapify(arr, 0, i - 1);
	}
}

int main(int argc, char const *argv[])
{
	cin >> len;
	for (int i = 0; i < len; ++i) {
		cin >> arr[i];
	}
	HeadSort(arr, len);
	for (int i = 0; i < len; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}