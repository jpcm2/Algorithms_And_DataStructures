
#include <bits/stdc++.h>

using namespace std;

struct Node
{
   struct Node *left;
   struct Node *right;
   int val;
   int bf;  
};

class AVL{
private:
   Node *raiz;
public:
   AVL(){
      cout << "Criei a AVL papai" << endl;
      raiz = NULL;   
   }
   Node *Rotate_left(Node *root){
      Node *R;
      Node *RL;
      R = root->right;
      RL = R->left;
      R->left = root;
      root->right = RL;
      if(R->bf <= 0){
         root->bf = root->bf - 1;
      }else{
         root->bf = root->bf - 1 - R->bf;
      }
      if(root->bf >= 0){
         R->bf = R->bf - 1;
      }else{
         R->bf = R->bf - 1 + root->bf;
      }
      return R;
   }

   Node *Rotate_right(Node *root){
      Node *L;
      Node *LR;
      L = root->left;
      LR = L->right;
      L->right = root;
      root->left = LR;
      if(L->bf > 0){
         root->bf = root->bf + 1;
      }else{
         root->bf = root->bf + 1 - L->bf;
      }
      if(root->bf <= 0){
         L->bf = L->bf + 1;
      }else{
         L->bf = L->bf + 1 + root->bf;
      }
      return L;
   }

   pair<Node *, int> inserir(Node *root, int v){      
      if(root == NULL){
         Node *N = new Node();
         N->left = NULL;
         N->right = NULL;
         N->val = v;
         N->bf = 0;
         return {N, 1};
      }
      int hc = 0;
      if(v == root->val){
         return {root, 0};
      }
      if(v < root->val){
         pair<Node *, int> temp = inserir(root->left, v);
         root->left = temp.first;
         hc = temp.second;
         root->bf = root->bf - hc;
      }else{
         pair<Node *, int> temp = inserir(root->right, v);
         root->right = temp.first;
         hc = temp.second;
         root->bf = root->bf + hc;
      }
      if(hc == 0){
         return {root, 0};
      }else if(root->bf == 0){
         return {root, 0};
      }else if(root->bf == 1 || root->bf == -1){
         return {root, 1};
      }else if(root->bf == -2){
         if(root->left->bf == 1){ // Left-right 
            root->left = Rotate_left(root->left);  
         }
         return {Rotate_right(root), 0};
      }else if(root->bf == 2){
         if(root->right->bf == -1){//right->left
            root->right = Rotate_right(root->right);
         } 
         return {Rotate_left(root), 0};
      }
      return {NULL, 0};
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
   void inorder(Node *root){
      if(root == NULL)return;
      inorder(root->left);
      cout << root->val << " ";
      inorder(root->right);
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
      cout << "Deletei a AVL papai" << endl;
   }
};

int main(){
   AVL tree;
   for(int i = 1; i <= 15; ++i){
      tree.raiz = tree.inserir(tree.raiz, 10*i).first;
   }  
   tree.pre_order(tree.raiz);
   return 0;
}
