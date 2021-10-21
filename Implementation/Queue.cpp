#include <bits/stdc++.h>

using namespace std;

struct Node{
	int val;
	struct Node *next;
};

class Queue{
private:
	struct Node *head;
	struct Node *tail;
	int sz;
public:
	int getSz(){
		return sz;
	}
	Node* getHead(){
		return head;
	}
	Node* geTail(){
		return tail;
	}
	Queue(){
		cout << "Criou a Queue papai!" << endl;
		head = new struct Node();
		head->next = NULL;
		tail = new struct Node();
		tail->next = NULL;
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
		//if(sz == 0)return;
		Node *p = head->next;
		head->next = p->next;
		if(head->next == NULL){
			tail = head;
		}
		sz--;
	}
	~Queue(){
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