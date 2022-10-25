/*Left-Rotate(T, x) Pseudo Code
Left-Rotate => x에 대해 좌회전 하겠다는 의미
x => 오른쪽 자식이 T.nil이 아닌 모든 노드

각 노드의 p는 노드의 부모 노드를 가리키는 포인터
각 노드의 right는 오른쪽 자식 노드를 가리키는 포인터
각 노드의 left는 왼쪽 자식 노드를 가리키는 포인터
*/ 

y = x.right;    // x의 오른쪽 자식 노드를 y라는 변수로 설정

x.right = y.left; // y의 왼쪽 자식노드를 x의 오른쪽 자식 노드로 설정, y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 옮긴다.
if (y.left != T.nil)
    y.left.p = x // 이때 y의 왼쪽 자식 노드가 nil이 아니면 y의 왼쪽 노드의 부모 노드를 x로 설정한다.

y.p = x.p;  // x의 부모 노드를 y의 부모 노드로 설정
if (x.p == T.nil)
    T.root = y; // x의 부모 노드가 nil이라면(x가 루트 노드라면) 트리의 root를 y로 설정
else if (x == x.p.left)
    x.p.left = y;   // x가 부모 노드의 '왼쪽'노드라면, x의 부모노드의 왼쪽 노드를 y로 설정
else    
    x.p.right = y; // x가 부모 노드의 '오른쪽' 노드라면, x의 부모 노드의 오른쪽 노드를 y로 설정

y.left = x;  // y의 왼쪽 노드를 x로 설정
x.p = y;  // x의 부모노드를 y로 설정



/*Right-Rotate(T, x) Pseudo Code
Right-Rotate => y에 대해 우회전 하겠다는 의미
x => 왼쪽 자식이 T.nil이 아닌 모든 노드 
p = parent, 노드의 부모 노드를 가리키는 포인터
right = 오른쪽 자식 노드를 가리키는 포인터
left = 왼쪽 자식 노드를 가리키는 포인터 */

y = x.left; // x의 왼쪽 자식 노드를 y라는 변수로 설정

x.left = y.right; // y의 오른쪽 자식 노드를 x의 왼쪽 자식 노드로 설정, y의 오른쪽 서브 트리를 x의 왼쪽 서브 트리로 옮긴다. 
if (y.right != T.nil)
    y.right.p = x // 이때 y의 오른쪽 자식 노드가 nil이 아니면 y의 오른족 노드의 부모 노드를 x로 설정한다.

y.p = x.p;  // y의 부모 노드 값에 x의 부모 노드 값을 대입한다.
if (x.p == T.nil)
    T.root = y; // x의 부모 노드가 nil이면(x가 루트 노드라면) 트리의 root를 y로 설정
else if (x ==  x.p.left)
    x.p.left = y;   // x가 부모 노드의 '왼쪽' 노드라면, x의 부모 노드의 왼쪽 노드를 y로 설정
else    
    x.p.right = y;  // x가 부모 노드의 '오른쪽' 노드라면, x의 부모 노드의 오른쪽 노드를 y로 설정

y.right = x // y의 오른쪽 노드를 x로 설정
x.p = y // x의 부모 노드를 y로 설정

