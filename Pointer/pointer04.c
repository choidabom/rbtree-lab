struct Test *p1 = (struct Test *)malloc(16); // 설정에 따라 오류 발생
struct Test *p2 = (struct Test *)malloc(sizeof(struct Test)); 

////////////////////////////////////////////////////////////////////

typedef struct node{ // 이 구조체를 연결 리스트에서 노드!!라고 함.
    int number;             // 숫자를 저장할 변수
    struct node *p_next;    // 다음 노드를 가리킬 포인터 
} Node;

// 첫 노드를 가리킬 헤드 포인터를 선언하고 NULL을 초기값으로 대입
NODE *p_head = NULL;

p_head = (NODE *)malloc(sizeof(NODE));
p_head->number = 12;    // 노드의 number에 값 12를 저장
p_head->p_next = NULL;  // 다음 노드가 없음을 명시


p_head = (NODE *)malloc(sizeof(NODE));
p_head->p_next->number = 15;    // 노드의 number에 값 15를 저장
p_head->p_next->p_next = NULL;  // 다음 노드가 없음을 명시

////////////////////////////////////////////////////////////////////

// 반복문은 p_head에 저장된 주소 값에서 시작
NODE *p = p_head;
// p_next가 NULL일 때까지 반복. p_next 값이 NULL이면 마지막 노드라는 뜻
while(NULL != p->p_next){
    p = p->p_next; // p->p_next값을 p에 대입하면 p는 다음 주소로 이동
}

////////////////////////////////////////////////////////////////////

void AddNumber(NODE **pp_head, int data){
    NODE *p;
    if(NULL != **pp_head){
        p = **pp_head;
        while(NULL != p->p_next) p = p->p_next; // p->p_next값을 p에 대입하면 p는 다음 주소로 이동
        p->p_next = (NODE *)malloc(sizeof(NODE));
        p = p->p_next; // 새로 만든 노드의 주소 값을 p에 저장
    } else {
        *pp_head = (NODE *)malloc(sizeof(NODE));
        p = *pp_head; // 새로 만든 노드의 주소 값을 p에 저장
    }
    p->number = data; // 새 노드의 number에 data값을 저장
    p->p_next = NULL; // 다음 노드가 없음을 명시
}

NODE *p_head = NULL;
AddNumber(&p_head, 15);

////////////////////////////////////////////////////////////////////


void AddNumber(NODE **pp_head, NODE **pp_tail, int data)
{
    if(NULL != **pp_head){
        (*pp_tail)->p_next = (NODE *)malloc(sizeof(NODE));
        *pp_tail = (*pp_tail)->p_next; // 새로 만든 노드의 주소 값을 p에 저장
    } else {
        *pp_head = (NODE *)malloc(sizeof(NODE));
        *pp_tail = *pp_head; // 새로 만든 노드의 주소 값을 p에 저장
    }
    *pp_tail->number = data; // 새 노드의 number에 data값을 저장
    *pp_tail->p_next = NULL; // 다음 노드가 없음을 명시
}


/////////////////////////////////////////
NODE *p = p_head, *p_save_next;
while(NULL!=p){
    p_save_next = p -> p_next; // 다음 노드의 주소를 미리 저장
    freep(p);       // p가 가리키는 노드를 삭제
    p = p_save_next; // 다음 노드로 이동
}
p_head = p_tail = NULL; // 연결 리스트의 시작과 끝을 초기화