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
    // *d1.numPtr == *(d1.numPtr)
    printf("%d\n", *d2->numPtr); // 구조체 포인터의 멤버를 역참조
    // *d2->numPtr == *(d2->numPtr)

    // 출력결과 
    // 10
    // 10
    
    free(d2); // 동적 메모리 해제
    return 0;
}