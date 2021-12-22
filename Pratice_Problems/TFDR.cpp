#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Node{
   struct Node *left;
   struct Node *right;
   int val;
};

class BST{
private:
   int qtd;
public:
   Node *root;
   BST(){
      root = NULL;
      qtd = 0;
   }
   Node* buildTree(int *v, int *i, int x, int mn, int mx, int n){
      if(*i >= n){
         return NULL;
      }
      Node *raiz = NULL;
      if(x > mn && x < mx){
         raiz = new Node();
         raiz->val = x;
         *i = *i + 1;
         if(*i < n){
            raiz->left = buildTree(v, i, v[*i], mn, x, n);
         }
         if(*i < n){
            raiz->right = buildTree(v, i, v[*i], x, mx, n);
         }
      }
      return raiz;
   }
   Node *build(int *v, int n){
      int i = 0;
      return buildTree(v, &i, v[0], INT_MIN, INT_MAX, n);
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
   void pos_order(Node *cur){
      if(cur == NULL){
         return;
      }
      pos_order(cur->left);
      pos_order(cur->right);
      if(cur == root){
         cout << cur->val;
      }else{
         cout << cur->val << " ";
      }
   }
   Node *Rotate_left(Node *raiz){
      Node *R;
      Node *RL;
      R = raiz->right;
      RL = R->left;
      R->left = raiz;
      raiz->right = RL;
      return R;
   }
   Node *Rotate_right(Node *raiz){
      Node *L;
      Node *LR;
      L = raiz->left;
      LR = L->right;
      L->right = raiz;
      raiz->left = LR;
      return L;
   }
   Node *step1(Node *raiz, int *ansl){
      if(raiz == NULL){
         return raiz;
      }
      while(raiz->right != NULL){
         raiz = Rotate_left(raiz); 
         *ansl = *ansl + 1;
      }
      raiz->left = step1(raiz->left, ansl);
      return raiz;
   }
   Node *solve(Node *raiz, int isLeft, int isRight, int *ansl, int *ansr, Node *raiz_aux){
      if(raiz == NULL){
         return raiz;
      }
      if(isLeft == 0 && isRight == 0){
         while(raiz->val != raiz_aux->val){
            raiz = Rotate_right(raiz);
            *ansr = *ansr + 1;
         }
         raiz->left = solve(raiz->left, 1, 0, ansl, ansr, raiz_aux->left);
         raiz->right = solve(raiz->right, 0, 1, ansl, ansr, raiz_aux->right);
      }else if(isLeft){
         while(raiz->val != raiz_aux->val){
            raiz = Rotate_right(raiz);
            *ansr = *ansr + 1;
         }
         raiz->left = solve(raiz->left, 1, 0, ansl, ansr, raiz_aux->left);
         raiz->right = solve(raiz->right, 0, 1, ansl, ansr, raiz_aux->right);
      }else if(isRight){
         while(raiz->val != raiz_aux->val){
            raiz = Rotate_left(raiz);
            *ansl = *ansl + 1;
         }
         raiz->right = solve(raiz->right, 0, 1, ansl, ansr, raiz_aux->right);
         raiz->left = solve(raiz->left, 1, 0, ansl, ansr, raiz_aux->left);
      }
      return raiz;
   }
   bool check(Node *raiz){
      if(raiz == NULL){
         return true;
      }
      int r = height(raiz->right);
      int l = height(raiz->left);
      bool eita = false;
      if(abs(r - l) <= 1){
         eita = true;
      }
      if(eita && check(raiz->left) && check(raiz->right)){
         return true;
      }
      return false;
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
   }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n){
        int ansl = 0, ansr = 0;
        BST tree;
        for(int i = 0; i < n; ++i){
            int a;
            cin >> a;
            tree.root = tree.inserir(tree.root, a);
        }
        tree.root = tree.step1(tree.root, &ansl);
        BST aux;
        int v[n + 1];
        for(int i = 0; i < n; ++i){
            cin >> v[i];
        }
        aux.root = aux.build(v, n);
        tree.root = tree.solve(tree.root, 0, 0, &ansl, &ansr, aux.root);
        cout << ansl << " " << ansr << endl;
        aux.pos_order(aux.root);
        cout << endl;
        bool check = aux.check(aux.root);
        if(check){
            cout << "true" << endl;
        }else{
            cout << "false" << endl;
        }
        tree.del(tree.root);
        aux.del(aux.root);
        cout << endl;
    }
    return 0;
}
