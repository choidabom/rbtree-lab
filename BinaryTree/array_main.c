#include "BinaryTreeArray.h"

void preorder(Node root){
    if (isTreeEmpty(root))
        return;
    printf("%c", getCurData(root));
    preorder(getLeftChild(root));
    preorder(getRightChild(root));
}

void inorder(Node root){
    if (isTreeEmpty(root))
        return;
    inorder(getLeftChild(root));
    printf("%c", getCurData(root));
    inorder(getRightChild(root));
}

void postorder(Node root){
    if (isTreeEmpty(root))
        return;
    postorder(getLeftChild(root));
    postorder(getRightChild(root));
    printf("%c", getCurData(root));
}

void main(){
    Node _a = makeRoot('A');
    Node _b = makeLeftChild(_a, 'B');
    Node _c = makeRightChild(_a, 'C');
    Node _d = makeLeftChild(_b, 'D');
    Node _e = makeRightChild(_b, 'E');
    Node _f = makeLeftChild(_c, 'F');
    Node _g = makeRightChild(_c, 'G');

    printf("전위 순회: "); preorder(_a); printf("\n");
    printf("중위 순회: "); inorder(_a); printf("\n");
    printf("후위 순회: "); postorder(_a); printf("\n");

    // 수식 트리
    // Node n1 = makeRoot('-');
    // Node n2 = makeLeftChild(n1, '*');
    // Node n3 = makeRightChild(n1, '/');
    // Node n4 = makeLeftChild(n2, 'A');
    // Node n5 = makeRightChild(n2, 'B');
    // Node n6 = makeLeftChild(n3, 'C');
    // Node n7 = makeRightChild(n3, 'D');
    // printf("test\n");
}