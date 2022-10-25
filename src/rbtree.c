#include "rbtree.h"

#include <stdlib.h>

// rbtree *new_rbtree(void) {} => return 값이 rbtree 자료형이라는 말이다. 
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));      // 레드 블랙 트리를 생성한다.
  node_t *NIL = (node_t *)calloc(1, sizeof(rbtree));    // NIL 노드를 생성한다. 
  NIL->color = RBTREE_BLACK;                            // NIL 노드의 특성을 고려하여 색을 블랙으로 지정한다. 

  p->root = NIL;                                        // 초기 트리를 NIL 노드로 설정한다.
  p->nil = NIL;                                         // 초기 닐을 NIL 노드로 설정한다. 
  
  return p;
}

// (rbtree * p, node_t * x) => 어느 트리인지, 어떤 노드인지 
void left_rotation(rbtree * p, node_t * x){ // x를 좌회전
  node_t *y; 

  y = x->right;   // 1. x의 오른쪽 자식 노드(right)를 y로 설정
  
  x->right = y->left;   // 2. y의 왼쪽 자식 노드(left)를 x의 오른쪽 자식 노드(right)로 설정
  if (y->left != p->nil)  // 3. y의 왼쪽 자식 노드가 nil이 아니면 
    y->left->parent = x;  // y의 왼쪽 노드의 부모 노드를 x로 설정
  
  y->parent = x->parent;  // 4. y의 부모 노드 값에 x의 부모 노드 값을 대입
  if (x->parent == p->nil)  // 5. x의 부모 노드가 nil이라면, 트리 구조체의 root를 y로 설정
    p->root = y;
  else if (x == x->parent->left) // 6. x가 부모 노드의 왼쪽이면, x의 부모 노드의 왼쪽 노드를 y로 설정
    x->parent->left = y;
  else  // 7. x가 부모 노드의 오른쪽이면, x의 부모 노드의 오른쪽 노드를 y로 설정
    x->parent->right = y; 
  
  y->left = x;  // 8. y의 왼쪽 노드를 x로 설정
  x->parent = y; // 9. x의 부모 노드를 y로 설정
}

// (rbtree * p, node_t * x) => 어느 트리인지, 어떤 노드인지 
void right_rotation(rbtree * p, node_t * x){ // x를 우회전
  node_t *y; 

  y = x->left;   

  x->left = y->right;  
  if (y->right != p->nil)  
    y->right->parent = x;
  y->parent = x->parent; 

  if (x->parent == p->nil) 
    p->root = y;
  else if (x == x->parent->left) 
    x->parent->left = y;
  else    
    x->parent->right = y;
  
  y->right = x;  
  x->parent = y;  
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory

  free(t);
}

void *rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED){
    // z의 parent가 왼쪽 자식 노드이면 
    if (z->parent == z->parent->parent->left){ 
      node_t *uncle = z->parent->parent->right; // 할아버지의 오른쪽 자식 노드 => uncle
      
      if (uncle->color == RBTREE_RED){          // 경우 1: uncle의 색이 red
        z->parent->color = RBTREE_BLACK;        // change color to black 
        uncle->color = RBTREE_BLACK;                   // change color to black 
        z->parent->parent->color = RBTREE_RED;  // change color to red & 여기서는 회전 x
        z = z->parent->parent; // 왜 할아버지를 가르키냐 ?? => 할아버지 밑으로 업뎃 끝났고 그 위에서 다시 while문 돌아야항께
      }
      else {    
        // 경우 2, 3: uncle의 색이 black                                             
        if (z == z->parent->right){             
          z = z->parent;
          left_rotation(t, z); // z를 좌회전 => 그치 parent를 z로 바꿨으니깐 z를 좌회전 ~
        }
        z->parent->color = RBTREE_BLACK;          // change color to black  
        z->parent->parent->color = RBTREE_RED;    // change color to black
        right_rotation(t, z->parent->parent);
      }
    }
    // z의 parent가 오른쪽 자식 노드이면 
    else {
      node_t *uncle = z->parent->parent->left; // 할아버지의 오른쪽 자식 노드 => uncle
      
      if (uncle->color == RBTREE_RED){          // 경우 1: uncle의 색이 red
        z->parent->color = RBTREE_BLACK;        // change color to black 
        uncle->color = RBTREE_BLACK;                   // change color to black 
        z->parent->parent->color = RBTREE_RED;  // change color to red & 여기서는 회전 x
        z = z->parent->parent; // 왜 할아버지를 가르키냐 ?? => 할아버지 밑으로 업뎃 끝났고 그 위에서 다시 while문 돌아야항께
      }
      else {    
        // 경우 2, 3: uncle의 색이 black                                             
        if (z == z->parent->left){             
          z = z->parent;
          right_rotation(t, z); 
        }
        z->parent->color = RBTREE_BLACK;          
        z->parent->parent->color = RBTREE_RED;    
        left_rotation(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *y = t->nil;   // 트리의 nil노드에 해당하는 y노드 생성
  node_t *x = t->root;  // 트리의 root노드에 해당하는 x노드 생성
  node_t *z = (node_t *)calloc(1, sizeof(node_t)); // 새로 들어온 노드 z
  z->key = key;

  // 값이 nil이 아닐 때까지 탐색
  while (x != t->nil){
    y = x;  // x가 nil을 만나기 전 값을 y에 기록
    if (z->key < x->key) // z 노드의 값이 x 노드보다 작을 때
      x = x->left;  
    else                 // z 노드의 값이 x 노드보다 클 때
      x = x->right;
  }
  // 탐색이 끝난 후, x가 nil을 만나기 전 노드인 y를 z의 부모 자리에 대입
  z->parent = y; 

  if (y == t->nil){ 
    t->root = z;
  }
  else if (z->key < y->key){
    y->left = z;
  }
  else{
    y->right = z;
  }

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rbtree_insert_fixup(t, z);
  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find

  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find

  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find

  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array

  return 0;
}
