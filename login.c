
#include <stdio.h>
#include <string.h>

int main() {
    
    char username[20] = "ychkim2007";
    char password[20] = "kyc040906@";
    
   
    char inputUsername[20];
    char inputPassword[20];
    
    int loggedIn = 0;

    do {
        printf("로그인\n");
        printf("사용자 이름: ");
        scanf("%s", inputUsername);
        
        printf("비밀번호: ");
        scanf("%s", inputPassword);
        
        
        if (strcmp(username, inputUsername) == 0 && strcmp(password, inputPassword) == 0) {
            printf("로그인 성공!\n");
            loggedIn = 1;
        } else {
            printf("로그인 실패. 잘못된 사용자 이름 또는 비밀번호입니다.\n");
        }
    } while (!loggedIn);

    return 0;
}
