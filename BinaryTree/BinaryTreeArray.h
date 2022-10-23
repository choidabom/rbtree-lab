#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 현재 각 노드는 character 하나씩을 가지도록 했기 때문에 그 노드가 비었는지 안 비었는지는 이 노드 값에다가 0을 넣는 것으로 표시하도록 하면 됨
// 노드의 데이터 탕비
typedef char DATA;  

// 특정노드는 '그 배열에서 내가 몇 번째 자리에 있다'라고 인덱스 값으로서 int 하나만 가지고 가면 됨
// 노드의 index로써 노드를 가리킴
typedef int Node;   // 배열의 인덱스를 표현할 수 있는 정수값 하나만 있다고 생각

// 이진 트리를 구성하는데 필요한 부분
// makeRoot: 루트 노드에 들어갈 데이터를 주면서 루트 노드 생성하라고 시킴, 함수 안에서 루트 노드를 만들고 만든 루트 노드를 반환 => index 값이 나올 것
Node makeRoot(DATA data); 
Node makeLeftChild(Node cur, DATA data);
Node makeRightChild(Node cur, DATA data);

// 구성된 이진트리 안에서 노드를 또는 노드가 가진 데이터를 가져올 수 있는 Get 함수
// getCurData: 노드를 주면서 그 노드의 데이터부를 받아 봄
DATA getCurData(Node cur);

// getLeftChildData: 특정 노드를 주면서 이 노드의 왼쪽 자식을 알려달라고 함.
Node getLeftChild(Node cur);

// getLeftChildData: 왼쪽 자식을 가져오고 그 노드의 데이터를 가져오는 식
DATA getLeftChildData(Node cur);

// getRightChild: 특정 노드를 주면서 이 노드의 오른쪽 자식을 알려달라고 함.
Node getRightChild(Node cur);

// getRightChildData: 오른쪽 자식을 가져오고 그 노드의 데이터를 가져오는 식
DATA getRightChildData(Node cur);

// 노드를 주면서 이 노드가 지금 비어있으면 1, 비어있지 않다면 0 반환
int isTreeEmpty(Node root);

#endif