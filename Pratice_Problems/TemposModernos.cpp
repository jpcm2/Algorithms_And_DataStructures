#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

//O processador está no ultimo elemento da fila
//O Escalonador está no primeiro elemento da fila.

struct Node{
	pair<int, int> val;
	struct Node *next;
};

class Queue{
public:
	int sz = 0;
	struct Node *head;
	struct Node *tail;
	void init(){
		head = new struct Node();
		head->next = NULL;
		tail = new struct Node();
		tail->next = NULL;
	}
	Node *acessar(int pos){
		int i = 0;
		Node *cur = head;
		while(i < pos && cur->next != NULL){
			cur = cur->next;
			i++;
		}
		return cur;
	}

	Node *find(int x){
		Node *cur = head;
		while(cur->next->val.first != x && cur->next != NULL){
			cur = cur->next;
		}
		return cur;
	}
	void inserir(pair<int, int> x){
		sz++;
		Node *N = new Node();
		N->val = x;
		if(tail->next == NULL){
			tail->next = N;
			head->next = N;
			return;
		}
		Node *p = tail->next;
		p->next = N;
		tail->next = N;
	}

	void remove(){
		if(sz == 0)return;
		Node *p = head->next;
		head->next = p->next;
		if(head->next == NULL){
			tail = head;
		}
		sz--;
		free(p);
	}
};

class Cirucular_List{
public:
	int sz = 0;
	struct Node *head;
	struct Node *tail;
	void init(){
		head = new struct Node();
		head->next = NULL;
		tail = new struct Node();
		tail->next = NULL;
	}
	Node *acessar(int pos){
		int i = 0;
		Node *cur = head;
		while(i < pos && cur->next != NULL){
			cur = cur->next;
			i++;
		}
		return cur;
	}

	Node *find(int x){
		Node *cur = head;
		while(cur->next->val.first != x && cur->next != NULL){
			cur = cur->next;
		}
		return cur;
	}
	Node *inserir(pair<int, int> x, Node *cur){
		Node *N = new Node();
		N->next = cur->next;
		N->val = x;
		cur->next = N;
		if(tail->next == NULL){
			tail->next = N;
		}
		sz++;
		return N;
	}
	Node *remove(Node *cur){
		if(sz == 0)return cur;
		Node *p = cur->next;
		cur->next = p->next;
		free(p);
		sz--;
		if(sz == 0){
			tail = head;
		}
		return cur;
	}
	void girar(){
		if(sz == 1)return;
		Node *p = acessar(sz - 1);
		Node *last = p->next;
		p->next = last->next;
		last->next = head->next;
		head->next = last;
		tail->next = p;
	}
};

class Stack{
public:
	int sz = 0;
	struct Node *head;
	void init(){
		head = new struct Node();
		head->next = NULL;
	}
	Node *acessar(int pos){
		int i = 0;
		Node *cur = head;
		while(i < pos && cur->next != NULL){
			cur = cur->next;
			i++;
		}
		return cur;
	}
	Node *find(int x){
		Node *cur = head;
		while(cur->next->val.first != x && cur->next != NULL){
			cur = cur->next;
		}
		return cur;
	}
	void inserir(pair<int, int> x){
		Node *N = new Node();
		N->val = x;
		N->next = head->next;
		head->next = N;
		sz++;
	}

	void remove(int *ans){
		if(sz == 0)return;
		Node *p = head->next;
		*ans = p->val.first;
		head->next = p->next;
		free(p);
		sz--;
	}
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Stack pilha;
    Queue fila;
    Cirucular_List list;
    list.init();
    fila.init();
    pilha.init();
    int k;
    cin >> k;
    string cmd;
    cin >> cmd;
    while(cmd != "END"){
    	if(cmd == "LOAD"){
    		int x, t;
    		cin >> x >> t;
    		pair<int, int> p = make_pair(x, t);
    		fila.inserir(p);
    	}else if(cmd == "UNLD"){
    		int ans;
    		pilha.remove(&ans);
    		cout << "UNLD " << ans << endl;
    	}else{
    		//1.
    		if(list.sz > 0){
    			Node *cur = list.head;
    			pair<int, int> temp = cur->next->val;
    			if(temp.second == 0){
    				list.remove(list.head);
    				pilha.inserir(temp);
    			}
    		}
    		//2. 
    		if(fila.sz > 0){
    			Node *cur = fila.head;
    			//cout << cur->next->val.first << " " << cur->next->val.second << endl;
    			pair<int, int> temp = cur->next->val;
    			list.inserir(temp, list.head);
    			fila.remove();
    		}
    		//3.
    		if(list.sz > 0){
    			Node *cur = list.tail;
    			cur->next->val.second -= k;
    			if(cur->next->val.second < 0)
    				cur->next->val.second = 0;
    			cout << "PROC " << cur->next->val.first << " " << cur->next->val.second << endl;
    			list.girar();
    		}else{
    			cout << "PROC -1 -1" << endl;
    		}
    	}
    	cin >> cmd;
    }
    return 0;
}
