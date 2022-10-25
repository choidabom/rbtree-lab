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

// TREE-INSERT와 RB-INSERT 사이의 차이점 
// 1. TREE-INSERT에 나타는 모든 NIL은 T.nil로 교체된다.
// 2. 올바른 트리 구조를 유지하기 위해 RB-INSERT의 z.left와 z.right가 T.nil로 지정된다.
// 3. z의 색깔을 적색을 칠함
// 4. z를 적색으로 칠함으로써 레드블랙 특성 중 하나가 위반 될 수 있으므로 RB-INSERT-FIXUP(T, z)를 호출해 특성을 복구함

// RB-INSERT(T, z)
y = T.nil;
x = T.root;
while (x != T.nil){
    y = x;
    if (z.key < x.key)
        x = x.left
    else
        x = x.right
}
z.p = y
if (y == T.nil)
    T.root = z
else if (z.key < y.key)
    y.left = z
else
    y.right = z
z.left = T.nil
z.right = T.nil
z.color = RED;
RB-INSERT-FIXUP(T, z)

// RB-INSERT-FIXUP(T, z)
wihle (z.p.color == RED){
    if (z.p == z.p.p.left){
        y = z.p.p.right
        if (y.color == RED)
            z.p.color = BLACK
            y.color = BLACK
            z.p.p.color = RED
            z = z.p.p
        else if z == z.p.right
            z = z.p
            LEFT-ROTATE(T, z)
            
    }
}
