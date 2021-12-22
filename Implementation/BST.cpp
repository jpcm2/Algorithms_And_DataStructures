#include <bits/stdc++.h>

using namespace std;

struct Node{
	struct Node *left;
	struct Node *right;
	int val;
};

class BST{
private:
	int qtd;
	Node *root;
public:
	BST(){
		cout << "Criei a BST papai" << endl;
		root = NULL;
		qtd = 0;
	}
	Node *inserir(Node *raiz, int v){
		if(raiz == NULL){
			Node *N = new Node();
			N->val = v;
			N->left = NULL;
			N->right = NULL;
			qtd++;
			return N;
		}
		if(v < raiz->val){
			raiz->left = inserir(raiz->left, v);
			qtd++;
			return raiz;
		}else{
			raiz->right = inserir(raiz->right, v);
			qtd++;
			return raiz;
		}
	}

	Node *find(Node *raiz, int v){
		if(raiz == NULL){
			return NULL;
		}
		if(v == raiz->val){
			return raiz;
		}
		if(v < raiz->val){
			return find(raiz->left, v);
		}else{
			return find(raiz->right, v);
		}
	}

	pair<Node *, int> Delete_Min(Node *raiz){
		int v;
		if(raiz->left == NULL){
			v = raiz->val;
			Node *r = raiz->right;
			delete raiz;
			return {r, v};
		}
		pair<Node *, int> temp = Delete_Min(raiz->left);
		raiz->left = temp.first;
		v = temp.second;
		return {raiz, v};
	}

	Node *Delete(Node *raiz, int v){
		if(raiz == NULL){
			return NULL;
		}
		if(v < raiz->val){
			raiz->left = Delete(raiz->left, v);
			return raiz;
		}
		if(raiz->val < v){
			raiz->right = Delete(raiz->right, v);
			return raiz;
		}
		if(raiz->left == NULL){
			Node *r = raiz->right;
			delete raiz;
			return r;
		}
		if(raiz ->right == NULL){
			Node *r = raiz->left;
			delete raiz;
			return r;
		}
		pair<Node *, int> temp = Delete_Min(raiz->right);
		raiz->right = temp.first;
		raiz->val = temp.second;
		return raiz;
	}
	int height(Node *cur){
		if(cur == NULL){
			return 0;
		}
		int h_left = height(cur->left);
		int h_right = height(cur->right);
		return 1 + max(h_left, h_right);
	}
	void pre_order(Node *cur){
		if(cur == NULL){
			return;
		}
		cout << cur->val << endl;
		pre_order(cur->left);
		pre_order(cur->right);
	}
	void del(Node *cur){
		if(cur->right != NULL && cur->left != NULL){
			del(cur->right);
			del(cur->left);
			delete cur;
		}else if(cur->right != NULL){
			del(cur->right);
			delete cur;
		}else if(cur->left != NULL){
			del(cur->left);
			delete cur;
		}else{
			delete cur;
		}
		cout << "Deletei a BST papai" << endl;
	}
};

int main(){
	return 0;
}
