#include <stdio.h>
#include <stdlib.h>

typedef char data;
typedef struct _Node
{
    char key;
    struct _Node* left;
    struct _Node* right;
} Node;
// 구조체 전체의 이름을 Node라고 부를 수 있음.

Node* searchBST(Node* root, char x){ // 이진 탐색 트리 노드 탐색(검색)
    Node* p = root;
    while (p != NULL){
        if (p->key == x){
            return p;
        }
        else if (p->key < x){
            p = p->right;
        }
        else
            p = p ->left;
    }
    return NULL;
}

// 이진 탐색 트리 노드 삽입
// 노드 삽입으로 구축해보기 => 탐색 실패 시에 실패한 위치에 노드를 삽입한다.
// p가 NULL이 되기 직전 노드
// p가 NULL이 된 순간에는 NULL값을 받기 직전에 가리키던 노드 포인터 => parent가 될 것
// p가 NULL이 된 순간에 그 때의 parent의 child로 새 노드를 붙임
Node* insertBST(Node* root, char x){ 
    Node* p = root;
    Node* parent = NULL; // p의 발자취를 따라가는 변수 => parent가 한 발짝도 못 갈 수 있음 => 그 때는 루트 자체에다가 새 노드 삽입 !
    while (p != NULL){
        parent = p;
        if (p->key == x){
            printf("같은 키가 있습니다.\n");
            return p;
        }
        else if (p->key < x){
            p = p->right;
        }
        else
            p = p ->left;
    }

    // 탐색 실패로 while문 빠져나왔을 때,
    // 1. 새 노드 할당: 아직 기존 트리에 붙이지는 않고 노드만 만들어둔 상황
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = x;
    newNode->left = newNode->right = NULL;

    // 2. parent의 자식으로 새 노드 붙이기: 왼쪽 자식에 붙일거냐, 오른쪽 자식에 붙일거냐? 
    if (parent != NULL){
        if (parent->key < newNode->key){
            parent->right = newNode;
        }
        else
            parent->left = newNode;

    }
    return newNode;
}

// 이진 탐색 트리 노드 삭제
// deleteBST의 반환 타입을 Node *로 해야하는 이유는 deleteBST 안에서 삭제가 되고 밑에 있는 노드가 위로 올라오게 될 수 있음, 새로운 루트 노드의 주소를 돌려줄 수 있게끔 루트노드의 주소를 돌려주도록 만듬
Node* deleteBST(Node* root, char x){ 
    Node* p = root;
    Node* parent = NULL;
    while ((p != NULL) && (p->key != x)){ // key를 만나거나 삭제할 게 없으면 while문 종료!
        parent = p;
        if (p->key == x){
            printf("같은 키가 있습니다.\n");
            return p;
        }
        else if (p->key < x){
            p = p->right;
        }
        else
            p = p ->left;
    }
    if (p==NULL){ // 삭제해야하는데 찾는 노드가 없으면 할 일이 없겠지 ?
        printf("찾는 노드가 없습니다.\n");
        return root;
    }

    // 차수가 0인 경우
    if (p->left == NULL && p->right == NULL){
        if (parent == NULL){  // 1) 현재 노드가 루트 노드이면서 차수가 0인 경우
            root = NULL; // 해당 노드가 루트 노드인 경우! 루트를 삭제
            // 트리 전체 노드가 한 개밖에 없는데 그것이 지워진 상황
        }
        else {  // 2) 현재 노드가 루트가 아닌데 차수가 0인 경우
            if (parent->left == p)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    }
    // 차수가 1인 경우 => 이렇게 쓰면 0인 것도 들어올 수 있는데 차수가 0인 케이스는 위에서 걸러짐
    else if (p->left == NULL || p->right == NULL){
        Node *child = (p->left != NULL) ? p->left : p->right;
        if (parent == NULL){ // 1) 현재 노드가 루트 노드이면서 차수가 1인 경우 => 자식 하나가 새로운 노드가 됨
            root = child;
        }
        else {  // 2) 현재 노드가 루트가 아닌데 차수가 1인 경우
            if (parent->left == p)
                parent->left = child;
            else
                parent->right = child;
        }
    }
    // 차수가 2인 경우 => 후계자를 찾으러 떠나야 하니깐 succ_parent, succ를 만드는 것!
    else {
        Node* succ_parent = p;  // 후계자의 parent 노드를 유지하면서 따라간다.
        Node* succ = p->right;   // 후계자를 오른쪽 서브트리에서 찾으려고 하니 p->right
        while (succ->left != NULL){
            succ_parent = succ; // succ_parent는 현재 succ를 가리키게 하고
            succ = succ->left; // succ는 왼쪽 자식 노드를 가리키게 옮김
        }
        p->key = succ->key;
        if (succ_parent->left == succ){
            succ_parent->left = succ->right;
        }
        else
            succ_parent->right = succ->right;
        p = succ;
    }

    free(p);
    return root; // 위 과정을 통해 값이 바뀌었을 수 있으니 root를 반환
}

void inorder(Node* root){
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%c", root->key);
    inorder(root->right);
}
int main(){
    Node* root = insertBST(NULL, 'D');
    insertBST(root, 'I');
    insertBST(root, 'F');
    insertBST(root, 'A');
    insertBST(root, 'G');
    insertBST(root, 'C');

    root = deleteBST(root, 'C');
    inorder(root); printf("\n");
    // 출력결과
    // ADFGI
    return 0;

}