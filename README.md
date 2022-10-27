# Red-Black Tree 구현
### SW Jungle Week05 (2022.10.20~10.27)
Balanced search tree로 많이 쓰이는 Red-black tree (이하 RB tree)를 C 언어로 구현하는 과제입니다.
구현하는 추상 자료형 (ADT: abstract data type)은 ordered set, multiset 입니다.

## TIL (Today I Learned)
### 10.21 금

- [C언어 기초](https://bo5mi.tistory.com/152)

### 10.22 토

- [C 언어 배열](https://bo5mi.tistory.com/154)
- [C 언어 포인터](https://bo5mi.tistory.com/155)
- [C 언어 강의 - BinaryTreeArray 구현](https://github.com/choidabom/rbtree-lab/tree/main/BinaryTree)

### 10.23 일

- [C 언어 구조체](https://bo5mi.tistory.com/156)
- 연결리스트 연습

### 10.24 월
- [C 언어 강의 - BinarySearchTree 구현](https://github.com/choidabom/rbtree-lab/tree/main/BinarySearchTree)
- RBT 원리, 이론 정리

### 10.25 화
- RBT rotation, insert, insert_fixup, find, min, max 구현
- RBT 삭제 공부

### 10.26 수
- RBT rbtree_to_array, transplant, erase, erase_fixup 구현
- test case 통과 
- 코드 리뷰 강의 시청

## Red-Black Tree

- 자가 균형 이진 탐색 트리로서 연관 배열 등을 구현하는데 쓰이는 자료구조
- 높이가 h인 이진 탐색 트리에서 **삽입, 삭제, 검색** 등과 같은 동작이 O(h)의 시간에 수행될 수 있는데, 최악의 경우 (이진 탐색 트리의 높이 클 경우) 실행 속도가 일반적인 연결 리스트와 비슷한 정도에 불가하다.
- 레드 블랙 트리는 트리가 균형을 이루도록 설계된 검색 트리 구조 중 하나이다. 자료의 삽입과 삭제, 검색의 동작이 최악의 경우에도 레드 블랙 트리의 높이인 O(logn) 시간에 수행되도록 보장한다. 

### Red-Black Tree 5계명

Red-Black Tree 는 다음의 성질들을 만족하는 BST 이다.

1.  모든 노드는 `Red` or `Black`
2.  루트는 항상 `Black`
3.  모든 리프(NIL)는 `Black`
4.  어떤 노드가 `Red`이면, 그 자식은 모두 `Black`
5.  각 노드로부터 그 노드의 자손인 리프 노드로 가는 경로들은 모두 같은 수의 `Black`노드를 포함한다. 
  -> 5번 규칙이 존재하기 때문에 RB tree는 근사적으로 균형을 맞추게 된다. 

### Red-Black Tree 의 특징

1.  Binary Search Tree 이므로 BST 의 특징을 모두 갖는다.
2.  Root node 부터 leaf node 까지의 모든 경로 중 최소 경로와 최대 경로의 크기 비율은 2 보다 크지 않다. 이러한 상태를 `balanced` 상태라고 한다.
3.  노드의 child 가 없을 경우 child 를 가리키는 포인터는 NIL 값을 저장한다. 이러한 NIL 들을 leaf node 로 간주한다.

_RBT 는 BST 의 삽입, 삭제 연산 과정에서 발생할 수 있는 문제점을 해결하기 위해 만들어진 자료구조이다. 이를 어떻게 해결한 것인가?_

<details><summary style="color:skyblue">경계 노드(Sentinel Node)</summary>
<p>
### 경계 노드(Sentinel Node)를 갖는 레드-블랙 트리

- 한계 조건을 다루기 편리하도록 트리의 경계 노드를 만들어준다.
- 루트의 부모와 모든 리프 노드는 NIL 노드여야 하고, 모든 리프 노드는 **Black**이어야 한다.
```c
// init
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));      // 레드 블랙 트리를 생성한다.
  node_t *NIL = (node_t *)calloc(1, sizeof(rbtree));    // NIL 노드를 생성한다. 
  NIL->color = RBTREE_BLACK;                            // NIL 노드의 특성을 고려하여 색을 블랙으로 지정한다. 

  p->root = NIL;                                        // 초기 트리를 NIL 노드로 설정한다.
  p->nil = NIL;                                         // 초기 닐을 NIL 노드로 설정한다. 
  
  return p;
}
```
</p>
</details>

<details><summary style="color:skyblue">회전(Rotate)</summary>
<p>
### 회전(Rotate)

- RB tree 삽입(insert), 삭제(delete) 연산 과정에서 트리가 수정되기 때문에 RB tree의 특성을 위반할 수 있다. 이런 특성을 복구해주기 위해서 트리 내의 일부 노드들의 색깔과 포인터를 변경해야 한다.
</p>
</details>

<details><summary style="color:skyblue">삽입(Insert)</summary>
<p>
### 삽입

우선 BST 의 특성을 유지하면서 노드를 삽입을 한다. 그리고 삽입된 노드의 색깔을 **RED 로** 지정한다. Red 로 지정하는 이유는 Black-Height 변경을 최소화하기 위함이다. 삽입 결과 RBT 의 특성 위배(violation)시 노드의 색깔을 조정하고, Black-Height 가 위배되었다면 rotation 을 통해 height 를 조정한다. 이러한 과정을 통해 RBT 의 동일한 height 에 존재하는 internal node 들의 Black-height 가 같아지게 되고 최소 경로와 최대 경로의 크기 비율이 2 미만으로 유지된다.
</p>
</details>

<details><summary style="color:skyblue">삭제(Deletion)</summary>
<p>
### 삭제

삭제도 삽입과 마찬가지로 BST 의 특성을 유지하면서 해당 노드를 삭제한다. 삭제될 노드의 child 의 개수에 따라 rotation 방법이 달라지게 된다. 그리고 만약 지워진 노드의 색깔이 Black 이라면 Black-Height 가 1 감소한 경로에 black node 가 1 개 추가되도록 rotation 하고 노드의 색깔을 조정한다. 지워진 노드의 색깔이 red 라면 Violation 이 발생하지 않으므로 RBT 가 그대로 유지된다.

Java Collection 에서 TreeMap 도 내부적으로 RBT 로 이루어져 있고, HashMap 에서의 `Separate Chaining`에서도 사용된다. 그만큼 효율이 좋고 중요한 자료구조이다.
</p>
</details>

## 구현 범위
다음 기능들을 수행할 수 있도록 RB tree를 구현합니다.

- tree = `new_tree()`: RB tree 구조체 생성
  - 여러 개의 tree를 생성할 수 있어야 하며 각각 다른 내용들을 저장할 수 있어야 합니다.
- `delete_tree(tree)`: RB tree 구조체가 차지했던 메모리 반환
  - 해당 tree가 사용했던 메모리를 전부 반환해야 합니다. (valgrind로 나타나지 않아야 함)

- `tree_insert(tree, key)`: key 추가
  - 구현하는 ADT가 multiset이므로 이미 같은 key의 값이 존재해도 하나 더 추가 합니다.
- ptr = `tree_find(tree, key)`
  - RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
  - 해당하는 node가 없으면 NULL 반환
- `tree_erase(tree, ptr)`: RB tree 내부의 ptr로 지정된 node를 삭제하고 메모리 반환
- ptr = `tree_min(tree)`: RB tree 중 최소 값을 가진 node pointer 반환
- ptr = `tree_max(tree)`: 최대값을 가진 node pointer 반환

- `tree_to_array(tree, array, n)`
  - RB tree의 내용을 *key 순서대로* 주어진 array로 변환
  - array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
  - array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.

## 구현 규칙
- `src/rbtree.c` 이외에는 수정하지 않고 test를 통과해야 합니다.
- `make test`를 수행하여 `Passed All tests!`라는 메시지가 나오면 모든 test를 통과한 것입니다.
- Sentinel node를 사용하여 구현했다면 `test/Makefile`에서 `CFLAGS` 변수에 `-DSENTINEL`이 추가되도록 comment를 제거해 줍니다.

## 과제의 의도 (Motivation)

- 복잡한 자료구조(data structure)를 구현해 봄으로써 자신감 상승
- C 언어, 특히 포인터(pointer)와 malloc, free 등의 system call에 익숙해짐.
- 동적 메모리 할당(dynamic memory allocation)을 직접 사용해 봄으로써 동적 메모리 할당의 필요성 체감 및 data segment에 대한 이해도 상승
- 고급 언어에서 기본으로 제공되는 자료구조가 세부적으로는 어떻게 구현되어 있는지 경험함으로써 고급 언어 사용시에도 효율성 고려

## 참고문헌
- [위키백과: 레드-블랙 트리](https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC)
([영어](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree))
- CLRS book (Introduction to Algorithms) 13장 레드 블랙 트리 - Sentinel node를 사용한 구현
- [Wikipedia:균형 이진 트리의 구현 방법들](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree#Implementations)
