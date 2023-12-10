#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct FamilyInfo {
    char name[50];
    char birthdate[15];
    char gender;
    char blood_type[5];
    char medical_history[100];
    char organ_donation;
};

struct MedicInfo {
    char name[30];
    char sick[50];
    char medic[50];
    char when[50];
    char year[50];
    char warning[50];
};

// 함수 선언
void inputFamilyInfo(struct FamilyInfo *info);
void inputMedicalInfo(struct MedicInfo *form);
void showFamilyInfo(struct FamilyInfo *info);
void displayMedicInfo(struct MedicInfo *form);
void saveToFile(struct FamilyInfo *info);
void saveMedicFile(struct MedicInfo *form);

int main() {
    int choice;
    struct FamilyInfo family;
    struct MedicInfo medic;

    do {
        printf("메뉴를 선택하세요:\n");
        printf("1. 가족 정보 입력\n");
        printf("2. 가족 복용약 입력\n");
        printf("3. 가족 상태 정보 열람\n");
        printf("4. 복용 약 상태 열람\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputFamilyInfo(&family);
                saveToFile(&family);
                break;
            case 2:
                inputMedicalInfo(&medic);
                saveMedicFile(&medic);
                break;
            case 3:
                showFamilyInfo(&family);
                break;
            case 4:
                displayMedicInfo(&medic);    
                break;  // 빠진 break 추가
            case 0:
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("올바른 메뉴를 선택하세요.\n");
        }
    } while (choice != 0);

    return 0;
}



// 정보 입력 함수
void inputFamilyInfo(struct FamilyInfo *info) {
    
    printf("성명: ");
    scanf("%s", info->name);

   
    do {
        printf("생년월일 (YYYYMMDD): ");
        scanf("%s", info->birthdate);

        // 생년월일이 8글자인지 확인
        if (strlen(info->birthdate) != 8) {
            printf("잘못된 입력입니다. 8글자의 숫자로 입력하세요.\n");
        } else {
            // 숫자인지 확인
            int valid = 1;
            for (int i = 0; i < 8; ++i) {
                if (!isdigit(info->birthdate[i])) {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                printf("잘못된 입력입니다. 숫자로 입력하세요.\n");
            }
        }
    } while (strlen(info->birthdate) != 8 || !isdigit(info->birthdate[0]));

    // 성별 입력 (M 또는 F가 아닌 경우 다시 입력)
    do {
        printf("성별 (M/F): ");
        scanf(" %c", &info->gender);

        info->gender = toupper(info->gender); // 대문자로 변환

        if (info->gender != 'M' && info->gender != 'F') {
            printf("잘못된 입력입니다. M 또는 F 중 하나를 입력하세요.\n");
        }
    } while (info->gender != 'M' && info->gender != 'F');


    printf("혈액형: ");
    scanf("%s", info->blood_type);

    // 질병이력 입력
    printf("질병이력: ");
    scanf("%s", info->medical_history);

    
    do {
        printf("장기 기증 여부 (Y/N): ");
        scanf(" %c", &info->organ_donation);

        info->organ_donation = toupper(info->organ_donation); // 대문자로 변환

        if (info->organ_donation != 'Y' && info->organ_donation != 'N') {
            printf("잘못된 입력입니다. Y 또는 N 중 하나를 입력하세요.\n");
        }
    } while (info->organ_donation != 'Y' && info->organ_donation != 'N');
}

void inputMedicalInfo(struct MedicInfo *form) {
    printf("약의 정보를 입력하세요\n");
    printf("누구의 약: ");
    scanf("%s", form->name);

    printf("약 이름: ");
    scanf("%s", form->medic);

    printf("질병: ");
    scanf("%s", form->sick);

    printf("투여 주기: ");
    scanf("%s", form->when);

    do {
        printf("유통기한 (YYYYMMDD): ");
        scanf("%s", form->year);

        // 생년월일이 8글자인지 확인
        if (strlen(form->year) != 8) {
            printf("잘못된 입력입니다. 8글자의 숫자로 입력하세요.\n");
        } else {
            // 숫자인지 확인
            int valid = 1;
            for (int i = 0; i < 8; ++i) {
                if (!isdigit(form->year[i])) {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                printf("잘못된 입력입니다. 숫자로 입력하세요.\n");
            }
        }
    } while (strlen(form->year) != 8 || !isdigit(form->year[0]));

    printf("투여시 주의점: ");
    scanf("%s", form->warning);
}


void saveToFile(struct FamilyInfo *info) {
    FILE *file = fopen("family.txt", "a");  // "a" 모드로 변경

    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    fprintf(file, "성명: %s\n", info->name);
    fprintf(file, "생년월일: %s\n", info->birthdate);
    fprintf(file, "성별: %c\n", info->gender);
    fprintf(file, "혈액형: %s\n", info->blood_type);
    fprintf(file, "질병이력: %s\n", info->medical_history);
    fprintf(file, "장기 기증 여부: %c\n", info->organ_donation);
    fprintf(file,"\n");
    fclose(file);

    printf("가족 정보가 성공적으로 저장되었습니다.\n\n");
}

void saveMedicFile(struct MedicInfo *form) {
    FILE *file = fopen("medic.txt", "a");  // "a" 모드로 변경

    if (file == NULL) {
        printf("파일을 열 수 없습니다\n");
        exit(1);
    }

    fprintf(file, "누구의 약: %s\n", form->name);
    fprintf(file, "약 이름: %s\n", form->medic);
    fprintf(file, "질병: %s\n", form->sick);
    fprintf(file, "투여 주기: %s\n", form->when);
    fprintf(file, "유통기한: %s\n", form->year);
    fprintf(file, "투여시 주의점: %s\n", form->warning);
    fprintf(file, "\n");

    fclose(file);
    printf("약 정보가 성공적으로 저장되었습니다.\n\n");
}

void displayMedicInfo(struct MedicInfo *form) {
    FILE *file = fopen("medic.txt","r");

    printf("\n");

    char c;
    int empty = 1;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
        empty = 0;
    }

    fclose(file);
    if(empty) {
        printf("내용이 존재하지 않습니다.");
    }
}

void showFamilyInfo(struct FamilyInfo *info) {
    FILE *file = fopen("family.txt","r");

    printf("\n");

    char c;
    int empty = 1;
    while((c = fgetc(file)) != EOF) {
        printf("%c",c);
        empty = 0;
    }
    fclose(file);
    if(empty) {
        printf("내용이 존재하지 않습니다.\n\n");
    }
}