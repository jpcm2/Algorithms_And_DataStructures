#include <bits/stdc++.h>

using namespace std;

class BinaryHeap{
private:
	int *H;
	int sizeH;
	int heapSize;
public:
	BinaryHeap(){
		H = NULL;
		sizeH = 0;
		heapSize = 0;
	}

	int *bubbleUp(int *heap, int pos){
		int i = pos;
		while(i > 0 && heap[i] >= heap[(i - 1)/2]){
			swap(heap[i], heap[(i - 1)/2]);
			i = (i - 1)/2;
		}
		return heap;
	}

	void inserir(int v){
		if(sizeH == heapSize){
			int *temp = NULL;
			temp = new int(sizeH);
			for(int i = 0; i < sizeH; ++i){
				temp[i] = H[i];
			}
			int *buff = NULL;
			int newSize = 2*sizeH + 1;
			buff = new int[newSize];
			delete []H;
			H = buff;
			for(int i = 0; i < sizeH; ++i){
				H[i] = temp[i];
			}
			sizeH = 2*sizeH + 1;
			delete[] temp;
		}
		H[heapSize] = v;
		heapSize++;
		H = bubbleUp(H, heapSize - 1);
	}

	int *bubbleDown(int *heap, int pos){
		int l = 2*pos + 1;
		int r = 2*pos + 2;
		int mx = pos;
		if(l< heapSize && heap[l] > heap[mx]){
			mx = l ;
		}
		if(r < heapSize && heap[r] > heap[mx]){
			mx = r;
		}
		if(mx != pos){
			swap(heap[mx], heap[pos]);
			heap = bubbleDown(heap, mx);
		}
		return heap;
	}
	int extrair(){
		int root = H[0];
		swap(H[0], H[heapSize - 1]);
		heapSize--;
		H = bubbleDown(H, 0);
		return root;
	}
	void buildOffline(int *v, int n){
		H = new int[n];
		H = v;
		heapSize = n;
		for(int i = n/2 - 1; i >= 0; --i){
			H = bubbleDown(H, i);
		}
	}
	void print(){
		for(int i = 0; i < heapSize; ++i){
			cout << H[i] << " ";
		}
	}
	~BinaryHeap(){
		delete[] H;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}
