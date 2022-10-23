#include <stdio.h>
#include <string.h>

// 구조체의 정의(구조체 자료형 선언)
typedef struct USERDATA {
    int age;
    char name[30];
    char phoneNo[30];
} USERDATA;

int main(){
    USERDATA * user; // 포인터 구조체의 선언

    user = (USERDATA *)malloc(sizeof(USERDATA)); // 포인터 구조체 초기화

    user->age = 10;
    strcpy(user->name, "dad");
    strcpy(user->phoneNo, "01012345678");

    printf("%d_%s_%s\n", user->age, user->name, user->phoneNo);

    free(user);

    return 0;
}