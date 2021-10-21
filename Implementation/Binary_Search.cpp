#include <bits/stdc++.h>

using namespace std;

int Binary_Search(int val, int *v, int n){
	int l = 0;
	int r = n - 1;
	while(l <= r){
		int mid = l + (r - l)/2;
		if(v[mid] < val){
			l = mid + 1;
		}else if(v[mid] > val){
			r = mid - 1;
		}else{
			return mid;
		}
	}
	return -1;
}

int main(){
	
	return 0;	
}