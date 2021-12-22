#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct Node{
    int id;
    int casos;
};

int id_local[500500];

class BinaryHeap{
public:
	Node *H;
	int sizeH;
	int heapSize;
	BinaryHeap(){
		H = NULL;
		sizeH = 0;
		heapSize = 0;
	}

	Node *bubbleUp(Node *heap, int pos){
		int i = pos;
		while(i > 0 && heap[i].casos >= heap[(i - 1)/2].casos){
			if(heap[i].casos > heap[(i - 1)/2].casos){
				swap(id_local[heap[i].id], id_local[heap[(i - 1)/2].id]);
				swap(heap[i], heap[(i - 1)/2]);
			}else if(heap[i].casos == heap[(i - 1)/2].casos){
				if(heap[i].id > heap[(i - 1)/2].id){
					swap(id_local[heap[i].id], id_local[heap[(i - 1)/2].id]);
					swap(heap[i], heap[(i - 1)/2]);
				}
			}
			i = (i - 1)/2;
		}
		return heap;
	}

	void inserir(int val, int j){
		if(sizeH == heapSize){
			Node *temp = NULL;
			temp = new Node[sizeH];
			for(int i = 0; i < sizeH; ++i){
				temp[i] = H[i];
			}
			Node *buff = NULL;
			int newSize = 2*sizeH + 1;
			buff = new Node[newSize];
			delete []H;
			H = buff;
			for(int i = 0; i < sizeH; ++i){
				H[i] = temp[i];
			}
			sizeH = 2*sizeH + 1;
			delete[] temp;
		}
		H[heapSize].casos = val;
		H[heapSize].id = j;
		id_local[j] = heapSize;
		heapSize++;
		H = bubbleUp(H, heapSize - 1);
	}

	Node *bubbleDown(Node *heap, int pos){
		int l = 2*pos + 1;
		int r = 2*pos + 2;
		int mx = pos;
		if(l< heapSize && heap[l].casos > heap[mx].casos){
			mx = l ;
		}else if(l< heapSize && heap[l].casos == heap[mx].casos){
			if(heap[l].id > heap[mx].id){
				mx = l;	
			}
		}
		if(r < heapSize && heap[r].casos > heap[mx].casos){
			mx = r;
		}else if(r< heapSize && heap[r].casos == heap[mx].casos){
			if(heap[r].id > heap[mx].id){
				mx = r;	
			}
		}
		if(mx != pos){
			swap(id_local[heap[mx].id], id_local[heap[pos].id]);
			swap(heap[mx], heap[pos]);
			heap = bubbleDown(heap, mx);
		}
		return heap;
	}
	Node extrair(){
		Node root = H[0];
		swap(id_local[H[0].id], id_local[H[heapSize - 1].id]);
		swap(H[0], H[heapSize - 1]);
		heapSize--;
		H = bubbleDown(H, 0);
		return root;
	}
	Node remove(int id){
		int pos = id_local[id];
		Node root = H[pos];
		swap(id_local[H[pos].id], id_local[H[heapSize - 1].id]);
		swap(H[pos], H[heapSize - 1]);
		heapSize--;
		H = bubbleDown(H, pos);
		H = bubbleUp(H, pos);
		return root;
	}
	int add(int id, int val){
		int pos = id_local[id];
		H[pos].casos += val;
		int ret = H[pos].casos;
		H = bubbleUp(H, pos);
		return ret;
	}
	int out(int id, int val){
		int pos = id_local[id];
		H[pos].casos -= val;
		if(H[pos].casos < 0){
			H[pos].casos = 0;
		}
		int ret = H[pos].casos;
		H = bubbleDown(H, pos);
		return ret;
	}
	void buildOffline(Node *v, int n){
		H = new Node[n];
		H = v;
		heapSize = n;
		for(int i = n/2 - 1; i >= 0; --i){
			H = bubbleDown(H, i);
		}
	}
	int pay(int r){
		int t = 0;
		while(H[0].casos > 0 && r > 0){
			r--;
			t++;
			H[0].casos--;
			bubbleDown(H, 0);
		}
		return t;
	}
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin >> n;
	Node *C = NULL;
	BinaryHeap heap;
	C = new Node[n];
	for(int i = 0; i < n;++i){
		C[i].id = i;
		cin >> C[i].casos;	
		id_local[i] = i;
	} 
	heap.buildOffline(C, n);
	string cmd;
	cin >> cmd;
	while(cmd != "END"){
		if(cmd == "NEW"){
			int h, c;
			cin >> h >> c;
			heap.inserir(c, h);
			if(heap.heapSize == 0){
				cout << -1 << " " << -1 << endl;
			}else{
				cout << heap.H[0].id << " " << heap.H[0].casos << endl;
			}
		}else if(cmd == "DEL"){
			int h;
			cin >> h;
			if(heap.heapSize == 0){
				cout << -1 << " " << -1 << endl;
			}else{
				heap.remove(h);
				if(heap.heapSize == 0){
					cout << -1 << " " << -1 << endl;
				}else{
					cout << heap.H[0].id << " " << heap.H[0].casos << endl;
				}
			}
		}else if(cmd == "IN"){
			int h, c;
			cin >> h >> c;
			int ret = heap.add(h, c);
			cout << ret << endl;
		}else if(cmd == "OUT"){
			int h, c;
			cin >> h >> c;
			int ret = heap.out(h, c);
			cout << ret << endl;
		}else if(cmd == "PAY"){
			int r;
			cin >> r;
			int t = heap.pay(r);
			cout << t << endl;
		}
		cin >> cmd;
	}
	int end = 0;
	for(int i = 0; i < heap.heapSize; ++i){
		end += heap.H[i].casos;
	}
	cout << end << endl;
    return 0;
}
