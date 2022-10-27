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

## Red-Black Tree 5계명

Red-Black Tree 는 다음의 성질들을 만족하는 BST 이다.

1.  모든 노드는 `Red` or `Black`
2.  루트는 항상 `Black`
3.  모든 리프(NIL)는 `Black`
4.  어떤 노드가 `Red`이면, 그 자식은 모두 `Black`
5.  각 노드로부터 그 노드의 자손인 리프 노드로 가는 경로들은 모두 같은 수의 `Black`노드를 포함한다. 
  -> 5번 규칙이 존재하기 때문에 RB tree는 근사적으로 균형을 맞추게 된다. 
  
<details><summary style="color:skyblue">경계 노드(Sentinel Node)</summary>

- 한계 조건을 다루기 편리하도록 트리의 경계 노드를 만들어준다.
- 루트의 부모와 모든 리프 노드는 NIL 노드여야 하고, 모든 리프 노드는 **Black**이어야 한다.

</details>

<details><summary style="color:skyblue">회전(Rotate)</summary>

- RB tree 삽입(insert), 삭제(delete) 연산 과정에서 트리가 수정되기 때문에 RB tree의 특성을 위반할 수 있다. 이런 특성을 복구해주기 위해서 트리 내의 일부 노드들의 색깔과 포인터를 변경해야 한다.

</details>

<details><summary style="color:skyblue">삽입(Insert)</summary>

우선 BST 의 특성을 유지하면서 노드를 삽입을 한다. 그리고 삽입된 노드의 색깔을 **RED 로** 지정한다. Red 로 지정하는 이유는 Black-Height 변경을 최소화하기 위함이다. 삽입 결과 RBT 의 특성 위배(violation)시 노드의 색깔을 조정하고, Black-Height 가 위배되었다면 rotation 을 통해 height 를 조정한다. 이러한 과정을 통해 RBT 의 동일한 height 에 존재하는 internal node 들의 Black-height 가 같아지게 되고 최소 경로와 최대 경로의 크기 비율이 2 미만으로 유지된다.

</details>

<details><summary style="color:skyblue">삭제(Deletion)</summary>

<p>
삭제도 삽입과 마찬가지로 BST 의 특성을 유지하면서 해당 노드를 삭제한다. 삭제될 노드의 child 의 개수에 따라 rotation 방법이 달라지게 된다. 그리고 만약 지워진 노드의 색깔이 Black 이라면 Black-Height 가 1 감소한 경로에 black node 가 1 개 추가되도록 rotation 하고 노드의 색깔을 조정한다. 지워진 노드의 색깔이 red 라면 Violation 이 발생하지 않으므로 RBT 가 그대로 유지된다.
</p>

</details>

## _RBT는 왜, 어디서 쓰는가?_

### Why?
- Red-Black Tree는 BST 의 삽입, 삭제 연산 과정에서 발생할 수 있는 문제점을 해결하기 위해 만들어진 자료구조이다.

### Where?
**1. Java Collection API의 Map Interface 구현체인 HashMap의 Seperate Chaining 구현에서 사용한다.**
  - Key 값의 Collision이 발생할 경우 같은 Hash 값을 가지는 원소들을 Collection으로 관리하는데, 이 때 원소의 개수가 많아지면 Red-Black 트리를 이용해서 관리하여 연산 시간을 O(logn)으로 관리한다.

**2. RB-Tree 는 Radix-Tree와 더불어 Linux Kernel에서 가장 많이 사용하는 Tree 자료구조이다.**
  - I/O scheduler(CFQ, deadline 등), ext filesystem, Virtual memory areas 등 Kernel의 여러 Subsystem에서 사용된다. 
  - 기존 Tree자료구조의 단점은 최악의 경우 노드가 Linked-List의 형태로 저장되어 탐색 시간복잡도가 O(N) 이 된다는 점이다. 하지만 RB Tree는 노드의 삽입과 삭제가 이루어 질때, Tree가 자동으로 회전하며 O(logN)의 시간복잡도를 보장한다.
 	- [linux/lib/rbtree_test.c](https://github.com/torvalds/linux/blob/master/lib/rbtree_test.c)

<details><summary style="color:skyblue"><b>Interesting Point</b></summary>

[과제에서 주어진 rbtree.h 내의 node_t 구조체 선언]
```c
typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;
```
[Linux Kernel RB Tree 구조체 선언]
```c
struct rb_node {  
	unsigned long  __rb_parent_color; /* rb parent and color */  
	struct rb_node *rb_right;  
	struct rb_node *rb_left;  
} __attribute__((aligned(sizeof(long))));
```
#### Q. 왜 Linux Kernel RB Tree 구조체 선언에서는 parent와 color가 한 자료형으로 선언되었는가?
#### A. 결론적으론 메모리 공간의 낭비를 줄이기 위해 

- `__rb_parent_color`에는 부모 노드의 주소값이 long으로 형변환되어 저장된다. 
- **주소는 4 혹은 8의 배수로 증가**하기 때문에 하위 2~3비트는 사용되지 않는다.
  -  8(10) ->  1000(2)
  - 16(10) -> 10000(2) 
  - 24(10) -> 11000(2)
  - 8의 배수를 확인해봤을 때, 하위 2~3비트가 사용되지 않는 것을 확인할 수 있다. 컴퓨터는 다 알고 있다..!
- **즉, rb_node에서는 이 사용하지 않는 비트를 색 지정을 사용하여 추가 변수를 사용하지 않아 메모리 공간을 절약할 수 있다.**
- `rb_parent_color` 멤버 변수를 통해 부모 노드 주소와 본인 노드 색 두 가지를 동시에 가질 수 있다. 
- `__rb_parent_color` 변수의 더 정확한 의미는 rb parent and color이다.

- 과거 Linux Kernel 2.4.31의 rb_node 구조체 과거에는 rb_parent와 rb_color가 독립적인 변수로 존재하는것을 알 수 있다. 상대적으로 메모리 공간이 더 낭비 되었을 것임을 확인할 수 있다. (아래 코드 과거 Linux Kernel 2.4.31의 rb_node 구조체)
```c
typedef struct rb_node_s
{
        struct rb_node_s * rb_parent;
        int rb_color;
#define RB_RED          0
#define RB_BLACK        1
        struct rb_node_s * rb_right;
        struct rb_node_s * rb_left;
}
rb_node_t;
```

</details>

**3. Linux의 기본 스케줄러인 CFS 스케줄링 알고리즘에서 사용한다.**
  - 테스크의 소요 시간 기준으로 프로세스를 관리하기 위해 Red-Black 트리를 이용해서 스케줄링을 관리한다. 

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
