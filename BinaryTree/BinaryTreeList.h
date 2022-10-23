#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 노드의 데이터 타입
typedef char DATA;  

// 노드: 자기참조구조체 형성
// 구조체 자체를 노드라고 하면 안 되고, 그 구조체에 대한 포인터 타입을 노드라 해야함. 
typedef struct _Node{
    DATA data;              // 데이터부 
    struct _Node* lchild;   // 링크부: 왼쪽 자식 
    struct _Node* rchild;
} * Node;

Node makeRoot(DATA data); 
Node makeLeftChild(Node cur, DATA data);
Node makeRightChild(Node cur, DATA data);

DATA getCurData(Node cur);
Node getLeftChild(Node cur);
DATA getLeftChildData(Node cur);
Node getRightChild(Node cur);
DATA getRightChildData(Node cur);
int isTreeEmpty(Node root);

#endif