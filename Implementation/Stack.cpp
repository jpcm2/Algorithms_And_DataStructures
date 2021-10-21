#include <bits/stdc++.h>

using namespace std;

struct Node{
	int val;
	struct Node *next;
};

class Stack{
private:
	int sz;
	struct Node *head;
public:
	Node* getHead(){
		return head;
	}
	int getSz(){
		return sz;
	}
	Stack(){
		head = new struct Node();
		head->next = NULL;
		sz = 0;
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
	void inserir(int x){
		Node *N = new Node();
		N->val = x;
		N->next = head->next;
		head->next = N;
		sz++;
	}

	void remove(){
		if(sz == 0)return;
		Node *p = head->next;
		head->next = p->next;
		sz--;
	}
	~Stack(){
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

	return 0;	
}