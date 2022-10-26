#include "rbtree.h"

#include <stdlib.h>

// 구현 규칙 
// .h 수정 없이 .c만 수정해서 구현해야하기에 추가
void left_rotation(rbtree *, node_t *);
void right_rotation(rbtree *, node_t *);
void rbtree_insert_fixup(rbtree *, node_t *);
void rbtree_erase_fixup(rbtree *t, node_t *x);
void rbtree_transplant(rbtree *t, node_t *u, node_t *v);

// init
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

  y = x->right;                   // 1. x의 오른쪽 자식 노드(right)를 y로 설정
  
  x->right = y->left;             // 2. y의 왼쪽 자식 노드(left)를 x의 오른쪽 자식 노드(right)로 설정
  if (y->left != p->nil)          // 3. y의 왼쪽 자식 노드가 nil이 아니면 
    y->left->parent = x;          // y의 왼쪽 노드의 부모 노드를 x로 설정
  
  y->parent = x->parent;          // 4. y의 부모 노드 값에 x의 부모 노드 값을 대입
  if (x->parent == p->nil)        // 5. x의 부모 노드가 nil이라면, 트리 구조체의 root를 y로 설정
    p->root = y;
  else if (x == x->parent->left)  // 6. x가 부모 노드의 왼쪽이면, x의 부모 노드의 왼쪽 노드를 y로 설정
    x->parent->left = y;
  else                            // 7. x가 부모 노드의 오른쪽이면, x의 부모 노드의 오른쪽 노드를 y로 설정
    x->parent->right = y; 
  
  y->left = x;                    // 8. y의 왼쪽 노드를 x로 설정
  x->parent = y;                  // 9. x의 부모 노드를 y로 설정
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

void delete_node(rbtree *t, node_t *n){
  if (n == t->nil){
    return;
  }
  delete_node(t, n->left);
  delete_node(t, n->right);
  free(n);

  return;
}

// RB tree 구조체가 차지했던 메모리 반환
// 해당 tree가 사용했던 메모리를 전부 반환해야 함
void delete_rbtree(rbtree *t) {
  delete_node(t, t->root);
  free(t->nil);
  free(t);
}

void rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED){
    // z의 parent가 왼쪽 자식 노드이면 
    if (z->parent == z->parent->parent->left){ 
      node_t *uncle = z->parent->parent->right; // 할아버지의 오른쪽 자식 노드 => uncle
      
      if (uncle->color == RBTREE_RED){          // 경우 1: uncle의 색이 red
        z->parent->color = RBTREE_BLACK;        // 부모: red -> black
        uncle->color = RBTREE_BLACK;            // 삼촌: red -> black
        z->parent->parent->color = RBTREE_RED;  // 조부모: red
        z = z->parent->parent; // 왜 할아버지를 가르키냐 ?? => 할아버지 밑으로 업뎃 끝났고 그 위에서 다시 while문 돌아야하니까. 조부모 노드랑 부모 노드랑 같은 빨강일 수 있으므로 
      }
      else {    
        // 경우 2, 3: uncle의 색이 black                                             
        if (z == z->parent->right){             
          z = z->parent;
          left_rotation(t, z); // z를 좌회전 => 그치 parent를 z로 바꿨으니깐 z를 좌회전 ~
        }
        z->parent->color = RBTREE_BLACK;          // 부모 red -> black
        z->parent->parent->color = RBTREE_RED;    // change color to black
        right_rotation(t, z->parent->parent);
      }
    }
    // z의 parent가 오른쪽 자식 노드이면 
    else {
      node_t *uncle = z->parent->parent->left; // 할아버지의 오른쪽 자식 노드 => uncle
      
      if (uncle->color == RBTREE_RED){          // 경우 1: uncle의 색이 red
        z->parent->color = RBTREE_BLACK;        // 부모: red -> black
        uncle->color = RBTREE_BLACK;            // 삼촌: red -> black
        z->parent->parent->color = RBTREE_RED;  // 조부모: red
        z = z->parent->parent; // 왜 할아버지를 가르키냐 ?? => 할아버지 밑으로 업뎃 끝났고 그 위에서 다시 while문 돌아야하니까. 조부모 노드랑 부모 노드랑 같은 빨강일 수 있으므로 
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

  // 삽입 위치 찾기 
  while (x != t->nil){  // 값이 nil이 아닐 때까지 탐색
    y = x; // x가 nil을 만나기 전 값을 y에 기록
    if (z->key < x->key) 
      x = x->left;  
    else                 
      x = x->right;
  }
  // 탐색이 끝난 후, x가 nil을 만나기 전 노드인 y를 z의 부모 자리에 대입
  z->parent = y; 

  // 빈 트리인 경우
  if (y == t->nil){ 
    t->root = z;    
  }
  // 키 삽입할 위치 찾기
  else if (z->key < y->key){
    y->left = z;
  }
  else{
    y->right = z;
  }

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;  // 삽입은 always red
  rbtree_insert_fixup(t, z);
  return z;
}

//RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
// 해당하는 node가 없으면 NULL 반환
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *p = t->root;
  while (p != t->nil){
    if (p->key == key){
      return p;
    }
    else if (p->key < key){
      p = p->right;
    }
    else{
      p = p -> left; 
    }
  }
  return NULL;
}

// RB tree 중 최소 값을 가진 node pointer 반환
// 왼쪽 최하단 노드
node_t *rbtree_min(const rbtree *t) {
  node_t *p = t->root;
  while (p->left != t->nil)
    p = p->left;

  return p;
}

// 최대값을 가진 node pointer 반환
// 오른쪽 최하단 노드
node_t *rbtree_max(const rbtree *t) {
  node_t *p = t->root;
  while (p->right != t->nil)
    p = p->right;

  return p;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
  if (u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}

void rbtree_erase_fixup(rbtree *t, node_t *x){

}

// RB tree 내부의 ptr로 지정된 node를 삭제하고 메모리 반환
int rbtree_erase(rbtree *t, node_t *z) {
  node_t *y = z;    // 삭제 후 자리를 대신할 노드 y
  node_t *x;        // z의 자식 노드 x

  color_t y_origin_color = y->color;
  if (z->left == t->nil){
    x = z->right;
    rbtree_transplant(t, z, z->right);
  }
  else if (z->right == t->nil){
    x = z->left;
    rbtree_transplant(t, z, z->left);
  }
  else {
    y = rbtree_min(z->right);
    x = y->right;
    if (y->parent == z){
      x->parent = y;
    }
    else {
      rbtree_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if 
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {


  return 0;
}
