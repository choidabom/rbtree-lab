# 이진탐색트리 구현 with 연결 리스트

## 1. 이진탐색트리(Binary Search Tree, BST)란?

- 모든 원소는 유일한 키 값을 갖는다. (중복 내용을 갖는 항목은 없다.)
- 왼쪽 서브트리의 모든 원소들은 루트의 키보다 작은 값을 갖는다.
- 오른쪽 서브트리의 모든 원소드른 루트의 키보다 큰 값을 갖는다.
- 왼쪽 서브트리와 오른쪽 서브트리도 이진탐색트리이다. (재귀적으로 정의)

## 2. 이진탐색트리에서 탐색 시 시간 복잡도

이진탐색트리에서 특정한 키값을 찾을 때, 그 값이 비교하려는 노드의 값보다 크면 오른쪽 서브트리를 방문하고 작으면 왼쪽 서브트리를 방문한다. 이 시점에서, 한 서브트리로 진입하는 순간 반대편 서브트리는 전혀 고려할 필요가 없어진다. 때문에 한 번 방문할 때마다 검색 대상이 1/2씩 줄어들어 시간복잡도는 O(log N)이다.

## 3. 이진탐색트리 코드 개요

<code>typedef char data</code>: 트리의 노드에 저장하는 데이터(본 예제에서는 간단한 케이스로 단일 문자를 저장)

<code>typedef struct Node</code>: 노드를 가리키는 구조체

<code>struct Node* left</code>: 해당 노드의 왼쪽 자식 노드를 가리키는 포인터

<code>struct Node* right</code>: 해당 노드의 오른쪽 자식 노드를 가리키는 포인터


## 4. 이진탐색트리에서 3가지 연산: 탐색/삽입/삭제
### 탐색

<code>searchBST(Node* root, char x)</code>:루트 노드를 주고서 우리가 찾고 싶은 x라는 key 값을 찾는다. 

x를 root값부터 시작해 비교하면서 root보다 크면 오른쪽 서브트리를, 작으면 왼쪽 서브트리를 방문한다. 

만약 x가 root값과 같으면 바로 root를 반환한다. 

### 삽입

<code>insertBST(Node* root, char x)</code>:
새로운 노드를 삽입하는 함수.

BST의 특징: 모든 원소는 유일한 키값을 갖는다.(=중복 값을 갖는 노드는 없다.)

따라서 새로운 노드의 key값은 반드시 기존 BST에 존재하지 않아야 하며 탐색을 실패한 위치에 새로운 노드를 삽입.

### 삭제

<code>deleteBST(Node* root, char x)</code>
: 차수(=자식 노드의 개수)가 0/1/2 인 총 세 가지 경우로 나눠서 진행

