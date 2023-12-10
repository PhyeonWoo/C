#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#ifdef __APPLE__ // MAC
#include <unistd.h>
#elif _WIN32 // WIN
#include <windows.h>
#endif

// 구조체
typedef struct {
    double latitude;  // 위도
    double longitude; // 경도
} Location;

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

typedef struct {
    char name[100];    // 병원 이름
    char department[50];  // 의과 종류
    char detail[200];  
    char info[300];  // 상세정보
    char website[200]; // 병원 지도 URL
    Location location; // 병원 위치
} Hospital;

//


// 함수 선언
void inputFamilyInfo(struct FamilyInfo *info);
void inputMedicalInfo(struct MedicInfo *form);
void showFamilyInfo(struct FamilyInfo *info);
void displayMedicInfo(struct MedicInfo *form);
void saveToFile(struct FamilyInfo *info);
void saveMedicFile(struct MedicInfo *form);


// 입력된 위치와 병원 위치 거리 표현 함수
Location getCurrentLocation() {
    Location currentLocation = {37.6486885, 127.0642073};
    return currentLocation;
}

double calculateDistance(Location location1, Location location2) {
    return sqrt(pow(location1.latitude - location2.latitude, 2) +
                pow(location1.longitude - location2.longitude, 2));
}
//


// 구글API 지도 오픈 코드
void openURL(const char *url) {
    char command[256];

#ifdef __APPLE__ // MAC
    snprintf(command, sizeof(command), "open %s", url);
#elif _WIN64 // WIN
    // Use "start" for URLs and "start" with the default web browser for HTML files
    if (strstr(url, ".html") != NULL) {
        snprintf(command, sizeof(command), "start \"%s\"", url);
    } else {
        snprintf(command, sizeof(command), "start %s", url);
    }
#endif

    system(command);
}
//

// 거리 표출 함수
void printHospitalsByDepartment(char *department, Location currentLocation, Hospital hospitals[], int hospitalsCount) {
    printf("- 현재 위치에서 반경 내의 %s 목록:\n\n", department);

    for (int i = 0; i < hospitalsCount; ++i) {
        double distance = calculateDistance(currentLocation, hospitals[i].location);

        if (strcmp(hospitals[i].department, department) == 0) {
            printf("%s\n %s %s - 현위치에서 떨어진 거리: \n %.4f km\n\n", hospitals[i].name, hospitals[i].detail, hospitals[i].info, distance);
        }
    }
}
// 

int hospitalMenu() {
    int choice;

    printf("의과 종류를 선택하세요:\n");
    printf("1. 정형외과\n");
    printf("2. 치과\n");
    printf("3. 내과\n");
    printf("4. 소아과\n");
    printf("5. 이비인후과\n");
    printf("6. 종합병원\n");
    printf("0. 홈으로 돌아가기\n");

    // 개행문자를 소비하기 위한 코드
    while (getchar() != '\n');

    printf("선택: ");
    if (scanf("%d", &choice) != 1) {
        printf("올바른 입력이 아닙니다. 다시 시도하세요.\n");
        // 에러 발생 시 입력 버퍼를 비워줌
        while (getchar() != '\n');
        return -1;
    }

    return choice;
}

int main() {
    struct FamilyInfo family;
    struct MedicInfo medic;
    char username[20] = "박현우";
    char password[20] = "박햔우";
    
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

    Location currentLocation = getCurrentLocation();

    Hospital hospitals[] = {
       
       {"A: 이홍섭정형외과", "정형외과", 
        "진료시간 : 09:00 ~ 15:00\n 전화번호 : 010-1234-5678\n", 
        "상세정보 : \n서울 노원구 동일로 1335 대원빌딩\n", "Orthopedics.html\n", {37.6479916, 127.0622426}},
        
        {"B: 김앤조서울 정형외과", "정형외과", 
        "진료시간 : 월~금 09:00 ~ 19:00\n 전화번호 : 02-6933-7080\n"
        "상세정보 : \n서울 노원구 노원로26길 181 청자빌딩 2~5층\n", "", {37.6580408, 127.0713479}},
        
        {"C: 노원 서울스카이 정형외과", "정형외과", 
        "진료시간 : 월~목 09:30 ~ 20:00\n 전화번호 : 02-2039-0911\n",
        "상세정보 : \n서울 노원구 동일로 1405 7층\n","", {37.6538318,127.0602452}},
        
        {"D: 중계넘버원 정형외과","정형외과",
        "진료시간 : 월~금 09:00 ~ 19:00\n 전화번호 : 02-935-5555\n",
        "상세정보 : \n서울 노원구 한글비석로 263 성모빌딩 2층 201\n","",{37.6511746,127.0764616}},
        


        {"A: 허브치과","치과",
        "진료시간 : 월~금 09:30 ~ 18:30\n 전화번호 : 02-933-2854\n",
        "상세정보 : \n서울 노원구 노해로 467 교보빌딩 11층\n","dental.html\n",{37.6544422,127.0599035}},
        
        {"B: 서울 더플랜치과","치과",
        "진료시간 : 월,수,금 10:00 ~ 19:30\n 전화번호 : 02-935-2828\n",
        "상세정보 : \n서울 노원구 노해로 494 고려빌딩 2층\n","", {37.654594,127.0629853}},
        
        {"C: 서울 열린치과의원","치과",
        "진료시간 : 월,수,금,토 10:00 ~ 19:00\n 전화번호 : 02-951-2828\n",
        "상세정보 : \n서울 노원구 동일로 1384\n","", {37.6540253,127.0460437}},
        
        {"D: 노원 아이디치과","치과",
        "진료시간 : 화,수,금 10:00 ~ 19:00\n 전화번호 : 02-3496-5680\n",
        "상세정보 : \n서울 노원구 동일로 1396 중원빌딩 2층\n","", {37.6532038,127.0612971}},
        



        {"A: 삼성편한내과","내과",
        "진료시간 : 월~금 08:30 ~ 18:00\n 전화번호 : 02-934-7500\n",
        "상세정보 : \n서울 노원구 동일로 1380 메디칼빌딩 4층\n","internal.html\n", {37.6516848,127.0616516}},   
        
        {"B :상계 맑은내과의원","내과",
        "진료시간 : 월~금 09:00 ~ 16:30\n 전화번호 : 02-930-7616\n",
        "상세정보 : \n서울 노원구 동일로 1366 삼봉빌딩 5층\n","",{37.6505033,127.06196}},
        
        {"C :천내과","내과",
        "진료시간 : 월,화,수,금 09:00 ~ 18:00\n 전화번호 : 02-3296-3311\n",
        "상세정보 : \n서울 노원구 동일로 1343 동일프라자 301호\n", "",{37.648443,127.061959}},
        
        {"D :연세내과","내과",
        "진료시간 : 월,화,수,금 09:00 ~ 18:00\n 전화번호 : 02-952-6671\n",
        "상세정보 : \n서울 노원구 노해로 492 501,502호\n","", {37.654387,127.062681}},
        
        {"E : 윤내과의원","내과",
        "진료시간 : 월~금 09:00 ~ 18:00\n 전화번호 : 02-934-7575\n",
        "상세정보 : \n서울 노원구 상계로3길 10\n","",{37.6566642,127.0625976}},

        {"F : 건강미소 내과의원","내과",
        "진료시간 : 월~금 08:30 ~ 19:00\n 전화번호 : 02-931-5513\n",
        "상세정보 : \n서울 노원구 노해로 480 5층\n","",{37.6541645,127.0614033}},





        {"A :상계 백병원","종합병원",
        "진료시간 : 월~금 08:30 ~ 17:00\n 전화번호 : 02-950-1144\n",
        "상세정보 : \n서울 노원구 동일로 1342\n", "big.html\n",{37.6485082,127.063142}},
        
        {"B : 원자력 병원","종합병원",
        "진료시간 : 월~금 09:00 ~ 17:00\n 전화번호 : 02-970-2114\n",
        "상세정보 : \n서울 노원구 노원로 75\n","", {37.628784,127.0826588}},
        
        {"C :노원 을지대학병원","종합병원",
        "진료시간 : 월~금 08:30 ~ 17:30\n 전화번호 : 1899-0001\n",
        "상세정보 : \n서울 노원구 한글비석로 68\n", "",{37.6364404,127.070009}},
        
        {"D : 한일병원","종합병원",
        "진료시간 : 월~금 09:00 ~ 18:00\n 전화번호 : 02-903-3231\n",
        "상세정보 : \n서울 강북구 도봉로 301\n","",{37.6352594,127.0228979}},

        {"E : 대한병원","종합병원",
        "진료시간 : 월~금 08:30 ~ 17:30\n 전화번호 : 02-901-3114\n",
        "상세정보 : \n서울 도봉구 우이천로 308\n","",{37.6458568,127.0285789}},





        {"A : 연세프렌즈 소아청소년과의원","소아과",
        "진료시간 : 월~금 09:00 ~ 21:00\n 전화번호 : 02-951-7900\n",
        "상세정보 : \n서울 노원구 동일로 1392 3층\n","kid.html\n",{37.6530156,127.0613085}},

        {"B : 기쁨소아 청소년과의원","소아과",
        "진료시간 : 월~금 09:00 ~ 18:00\n 전화번호 : 02-931-7724\n",
        "상세정보 : \n서울 노원구 동일로216길 70\n","",{37.6520846,127.065477}},

        {"C : 함영백소아과의원","소아과",
        "진료시간 : 월,화,목 09:00 ~ 17:30\n 전화번호 : 02-952-3318\n",
        "상세정보 : \n서울 노원구 동일로 1361 202동\n","",{37.650016,127.0612135}},




        {"A : 하나 이비인후과의원","이비인후과",
        "진료시간 : 월~금 09:00 ~ 19:30\n 전화번호 : 02-952-8883\n",
        "상세정보 : \n서울 노원구 동일로 1405 노원프라자 5층\n","ear_nose.html\n",{37.653842,127.0602611}},

        {"B : 삼성드림 이비인후과의원","이비인후과",
        "진료시간 : 월~금 09:00 ~ 18:30\n 전화번호 : 02-935-1365\n",
        "상세정보 : \n서울 노원구 노해로 482 덕영빌딩 4층\n","",{37.654232,127.0617}},

        {"C : 이병희 이빈이후과의원","이비인후과",
        "진료시간 : 월~금 09:00 ~ 18:30\n 전화번호 : 02-931-4144\n",
        "상세정보 : \n서울 노원구 동일로 1382 올림피아상가 201\n","",{37.6519425,127.0615701}},

        {"D : 선 이비인후과의원","이비인후과",
        "진료시간 : 월~금 09:00 ~ 18:00\n 전화번호 : 02-931-3090\n",
        "상세정보 : \n서울 노원구 동일로 1380 메디칼빌딩 2층\n","",{37.6519425,127.0615701}},

        {"E : 닥터오 이비인후과의원","이비인후과",
        "진료시간 : 월~금 09:00 ~ 19:00\n 전화번호 : 02-6956-0863\n",
        "상세정보 : \n서울 노원구 동일로 1308 정안프라자 2층\n","",{37.6459658,127.0641536}},


    };

    int hospitalsCount = sizeof(hospitals) / sizeof(hospitals[0]);


    int mainChoice;

    while (1) {
        printf("메뉴를 선택하세요:\n");
        printf("1. 가족 확인\n");
        printf("2. 병원 확인\n");
        printf("0. 로그아웃\n");

        printf("선택: ");
        if (scanf("%d", &mainChoice) != 1) {
            printf("올바른 입력이 아닙니다. 다시 시도하세요.\n");
            // 에러 발생 시 입력 버퍼를 비워줌
            while (getchar() != '\n');
            continue;
        }

        if (mainChoice == 0) {
            printf("로그아웃 합니다.\n");
            break;  // 로그아웃 시 메인 루프 종료
        }

        switch (mainChoice) {
            case 1:
                printf("가족 확인 기능을 호출합니다.\n");
                int FamilyChoice;
                do {
                    
                        printf("\n메뉴를 선택하세요:\n");
                        printf("1. 가족 정보 입력\n");
                        printf("2. 가족 복용약 입력\n");
                        printf("3. 가족 상태 정보 열람\n");
                        printf("4. 복용 약 상태 열람\n");
                        printf("0. 종료\n");
                        printf("선택: ");
                        scanf("%d",&FamilyChoice);
                        switch (FamilyChoice){
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
                            break;
                        case 0:
                            printf("프로그램을 종료합니다\n");
                            break;
                        default:
                            printf("올바른 메뉴를 선택하세요\n");
                    }
                } while(FamilyChoice != 0);
                break;

            case 2:

                printf("병원 확인 기능을 호출합니다.\n");
                int hospitalChoice;
                do {
                    hospitalChoice = hospitalMenu();

                    switch (hospitalChoice) {
                        case 1:
                            printHospitalsByDepartment("정형외과", currentLocation, hospitals, hospitalsCount);
                            break;
                        case 2:
                            printHospitalsByDepartment("치과", currentLocation, hospitals, hospitalsCount);
                            break;
                        case 3:
                            printHospitalsByDepartment("내과", currentLocation, hospitals, hospitalsCount);
                            break;
                        case 4:
                            printHospitalsByDepartment("소아과", currentLocation, hospitals, hospitalsCount);
                            break;
                        case 5:
                            printHospitalsByDepartment("이비인후과", currentLocation, hospitals, hospitalsCount);
                            break;
                        case 6:
                            printHospitalsByDepartment("종합병원", currentLocation, hospitals, hospitalsCount);
                            break;
                        case 0:
                            printf("홈으로 돌아갑니다.\n");
                            break;
                        default:
                            printf("잘못된 선택입니다. 다시 선택하세요.\n");
                            break;
                    }
                } while (hospitalChoice != 0);
                break;
            default:
                printf("잘못된 선택입니다.\n");
                return 1;
        }
        printf("\n");
    }

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