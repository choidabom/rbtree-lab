// 포인터
#include <stdio.h>
int main(){
    int *p;
    int a;

    p = &a;

    printf("포인터 p에 들어있는 값: %p\n", p);
    printf("int 변수 a가 저장된 주소: %p\n", &a);
    // 출력결과 
    // 포인터 p에 들어있는 값: 0x7fffffffd96c
    // int 변수 a가 저장된 주소: 0x7fffffffd96c
    return 0;
}
