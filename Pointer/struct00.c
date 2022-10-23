#include <stdio.h>
#include <string.h>

// 구조체의 정의(구조체 자료형 선언)
typedef struct USERDATA {
    int age;
    char name[30];
    char phoneNo[30];
} USERDATA;

int main(){
    USERDATA user; // 구조체의 선언
    user.age = 10;
    strcpy(user.name, "Justin");
    strcpy(user.phoneNo, "01012345678");

    printf("%d_%s_%s\n", user.age, user.name, user.phoneNo);
    return 0;
}