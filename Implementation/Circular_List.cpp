#include <bits/stdc++.h>

using namespace std;

struct Node{
	int val;
	struct Node *next;
};

class Cirucular_List{
private:
	int sz;
	struct Node *head;
public:
	Cirucular_List(){
		head = new struct Node();
		head->next = NULL;
		sz = 0;
	}
	Node *getHead(){
		return head;
	}
	int getSz(){
		return sz;
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
		while(cur->next->val != x && cur->next != NULL){
			cur = cur->next;
		}
		return cur;
	}
	Node *inserir(int x, Node *cur){
		Node *N = new Node();
		N->next = cur->next;
		N->val = x;
		cur->next = N;
		sz++;
		return N;
	}
	Node *remove(Node *cur){
		Node *p = cur->next;
		cur->next = p->next;
		return cur;
	}
	void girar(){
		aNode *p = acessar(sz - 1);
		Node *last = p->next;
		p->next = last->next;
		last->next = head->next;
		head->next = last;  
	}
	~Cirucular_List(){
		Node *cur = head;
		while(cur->next != NULL){
			Node *atual = cur;
			cur = cur->next;
			delete atual;
		}
		delete cur;
	}
};

int main(){
	Cirucular_List list;
	for(int i = 1; i <= 8; ++i){
		list.inserir(i, list.getHead());
	}
	Node *cur = list.getHead();
	while(cur->next != NULL){
		cout << cur->next->val << " ";
		cur = cur->next;
	}
	cout << endl;
	list.girar();
	cur = list.getHead();
	while(cur->next != NULL){
		cout << cur->next->val << " ";
		cur = cur->next;
	}
	return 0;	
}