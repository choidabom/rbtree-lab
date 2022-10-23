// & 연산자
#include <stdio.h>
int main(){
    int a;
    a = 2;
    // 주소 연산자(&)를 붙여, 변수 a의 주소를 구함
    printf("%p \n", &a);
    // 출력 결과: 0x7fffffffd984
    return 0;
}