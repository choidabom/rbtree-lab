#include "BinaryTreeList.h"

/*
예외처리
1) malloc 반환값 체크
2) 포인터 역참조 전에 NULL 체크
*/

// 트리
// 배열: 트리 => 미리 선언된 배열
// 연결 리스트: 트리 => 빈 트리에서 시작
Node tree = NULL;

// makeRoot, makeLeftChild, makeRightChild => 트리를 생성하는데 필요한 함수
// makeRoot: 루트 노드에 들어갈 데이터를 주면서 루트 노드 생성하라고 시킴, 함수 안에서 루트 노드를 만들고 만든 루트 노드를 반환 => index 값이 나올 것

// Node: 노드 포인터/structure의 size만큼을 malloc을 받아야함.
Node makeRoot(DATA data){ // 루트 노드를 만드는 작업
    tree = (struct _Node*)malloc(sizeof(struct _Node));
    tree->data = data;
    tree->lchild = tree->rchild = NULL; // newnode를 기준으로 새롭게 지정
    return tree; // 지금 새로 생성한 단 하나의 노드를 반환 
}

Node makeLeftChild(Node cur, DATA data){
    struct _Node* newnode = (struct _Node*)malloc(sizeof(struct _Node));
    newnode->data = data;
    newnode->lchild = newnode->rchild = NULL;
    cur->lchild = newnode;
    return newnode; // 새로 할당받은 newnode 반환
}

Node makeRightChild(Node cur, DATA data){
    struct _Node* newnode = (struct _Node*)malloc(sizeof(struct _Node));
    newnode->data = data;
    newnode->lchild = newnode->rchild = NULL;
    cur->rchild = newnode;
    return newnode; // 새로 할당받은 newnode 반환
}

// getCurData: 노드를 주면서 그 노드의 데이터를 반환해줘야하는 함수 
DATA getCurData(Node cur){
    return cur->data;
}

Node getLeftChild(Node cur){
    return cur->lchild;
}

DATA getLeftChildData(Node cur){
    return cur->lchild->data;
}

Node getRightChild(Node cur){
    return cur->rchild;
}

DATA getRightChildData(Node cur){
    return cur->rchild->data;
}

int isTreeEmpty(Node root){ // 루트가 NULL이면 empty이고 NULL이 아니면 empty가 아님
    if(root==NULL)
        return 1;
    else
        return 0;
}
