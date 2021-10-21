#include <bits/stdc++.h>

using namespace std;

struct Node{
	int val;
	struct Node *next;
};

class Linked_List{
private:
	int sz;
	struct Node *head;
public:
	Linked_List(){
		sz = 0;
		head = new struct Node();
		head->next = NULL;
		cout << "Linked_List criada papai!! sz: " << sz << endl;
	}
	Node* getHead(){
		return head;
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
	~Linked_List(){
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