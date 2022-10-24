#include <stdio.h>
#include <stdlib.h>

// 구조체의 정의(구조체 자료형 선언)
typedef struct Data{
    char c;
    int *numPtr; // 포인터
} Data;

int main(){
    int num = 10;
    Data d1;    // 구조체 변수 선언
    Data *d2 = malloc(sizeof(struct Data)); // 구조체 포인터 변수 선언 및 메모리 할당
    
    d1.numPtr = &num; // 구조체 d1의 멤버인 numPtr에 num의 메모리 주소를 전달 
    d2->numPtr = &num; // d2에 있는 Data의 메모리 주소를 역참조하여 멤버인 numPtr에 num에 num의 메모리 주소 전달

    printf("%d\n", *d1.numPtr); // 구조체의 멤버를 역참조
    printf("%d\n", *d2->numPtr); // 구조체 포인터의 멤버를 역참조

    d2->c = 'b';    // 구조체 포인터 역참조하여 멤버 c에 접근해 'b' 값 넣기
    printf("%c\n", (*d2).c);

    printf("%c\n", (*d2).c);
    printf("%d\n", *(*d2).numPtr);

    free(d2); // 동적 메모리 해제
    return 0;
}