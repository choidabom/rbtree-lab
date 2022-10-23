#include "BinaryTreeArray.h"

// 트리
#define NODE_MAXCOUNT 100
DATA tree[NODE_MAXCOUNT] = {0}; // 모든 노드 0으로 초기화 => 100개의 노드가 모두 0값 가짐

// makeRoot, makeLeftChild, makeRightChild => 트리를 생성하는데 필요한 함수
// makeRoot: 루트 노드에 들어갈 데이터를 주면서 루트 노드 생성하라고 시킴, 함수 안에서 루트 노드를 만들고 만든 루트 노드를 반환 => index 값이 나올 것
Node makeRoot(DATA data){
    tree[1] = data; // 준비된 배열의 1번째 원소에 데이터 값 넣기
    // => Node를 반환하게 되어있기 때문에! 방금 생성한 루트 노드 번호를 주면 됨
    return 1;
}

Node makeLeftChild(Node cur, DATA data){
    tree[cur*2] = data;
    return cur*2; // 새로 생긴 왼쪽 자식의 인덱스 번호 반환
}

Node makeRightChild(Node cur, DATA data){
    tree[cur*2+1] = data;
    return cur*2+1; // 새로 생긴 오른쪽 자식의 인덱스 번호 반환
}

// getCurData: 노드를 주면서 그 노드의 데이터를 반환해줘야하는 함수 
DATA getCurData(Node cur){
    return tree[cur];
}

Node getLeftChild(Node cur){
    return cur * 2;
}

DATA getLeftChildData(Node cur){
    return tree[cur*2];
}

Node getRightChild(Node cur){
    return cur * 2 + 1;
}

DATA getRightChildData(Node cur){
    return tree[cur * 2 + 1];
}

int isTreeEmpty(Node root){
    if (tree[root] == 0)
        return 1;
    else
        return 0;

}
