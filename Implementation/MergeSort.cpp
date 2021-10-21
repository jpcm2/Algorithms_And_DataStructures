#include <bits/stdc++.h>

using namespace std;

void merge(int *v, int l, int mid, int r, int *a){
	int i = l;
	int j = mid + 1;
	for(int k = l; k <= r; ++k){
		if(i > mid){
			a[k] = v[j];
			j++;
		}else if(j > r){
			a[k] = v[i];
			i++;
		}else if(v[i] <= v[j]){
			a[k] = v[i];
			i++;
		}else{
			a[k] = v[j];
			j++;
		}
	}
	for(int k = l; k <= r; ++k){
		v[k] = a[k];
	}
}

void msort(int *v, int l, int r, int *a){
	if(l < r){
		int mid = l + (r - l)/2;
		msort(v, l, mid, a);
		msort(v, mid + 1, r, a);
		merge(v, l, mid, r, a);
	}
}

void MergeSort(int *v, int n){
	int *a = new int[n];
	msort(v, 0, n - 1, a);
}

int main(){
	
}