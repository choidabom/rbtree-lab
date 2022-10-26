// 1행에서 NIL 대신 경계 노드 T.nil을 참고
// 6행에서 조건 없이 v.p에 값이 할당된다.
// 즉, v가 경계 노드를 가리키고 있어도 v.p에 값을 설정할 수 있다.
// v = T.nil일 때도 v.p에 값을 할당할 수 있다.

// RB_TRANSPLANT(T, u, v)
if u.p == T.nil
    T.root = v
else if u == u.p.left
    u.p.left = v
else
    u.p.right = v
v.p = u.p


