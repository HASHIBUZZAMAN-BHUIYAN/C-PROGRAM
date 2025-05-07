#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CANDIDATES 6
#define MAX_MEMBERS 4

typedef struct {
    int id;
    char name[50];
    int birth;
    char pass[4]; // "yes" or "no"
    char nickname[50];
    char education[50];
    float height; // meters
    float weight; // kg
    char blood[4];
    char allergy[50];
    char hobby[100];
    char sns[100];
    float bmi;
} Candidate;

void print_bmi_category(float bmi) {
    int category = 0;
    if (bmi < 18.5)
        category = 0;
    else if (bmi < 23)
        category = 1;
    else if (bmi < 25)
        category = 2;
    else
        category = 3;

    switch (category) {
        case 0:
            printf(" (저체중)\n");
            break;
        case 1:
            printf(" (정상)\n");
            break;
        case 2:
            printf(" (과체중)\n");
            break;
        case 3:
            printf(" (비만)\n");
            break;
        default:
            printf(" (BMI 오류)\n");
            break;
    }
}

int main() {
    Candidate candidate03_arr[MAX_CANDIDATES] = {
        {101, "박지연", 20020815, "yes"},
        {102, "Ethan Smith", 20030920, "yes"},
        {103, "Helena Silva", 20030612, "yes"},
        {104, "Liam Wilson", 20021201, "yes"},
        {105, "Kim Jisu", 20040101, "no"},
        {106, "Han Yuna", 20030505, "no"}
    };

    Candidate milliways03_arr[MAX_MEMBERS];
    int m_index = 0;

    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (strcmp(candidate03_arr[i].pass, "yes") == 0) {
            // Copy basic data
            milliways03_arr[m_index] = candidate03_arr[i];

            // Add additional hb interview data
            switch (milliways03_arr[m_index].id) {
                case 101:
                    strcpy(milliways03_arr[m_index].nickname, "Ariel");
                    strcpy(milliways03_arr[m_index].education, "고1중퇴");
                    milliways03_arr[m_index].height = 1.68;
                    strcpy(milliways03_arr[m_index].blood, "A");
                    strcpy(milliways03_arr[m_index].allergy, "유제품");
                    strcpy(milliways03_arr[m_index].hobby, "댄스 연습, 작곡");
                    strcpy(milliways03_arr[m_index].sns, "Instagram - @Ariel_Jiyeon");
                    break;
                case 102:
                    strcpy(milliways03_arr[m_index].nickname, "Simba");
                    strcpy(milliways03_arr[m_index].education, "중3중퇴");
                    milliways03_arr[m_index].height = 1.78;
                    strcpy(milliways03_arr[m_index].blood, "O");
                    strcpy(milliways03_arr[m_index].allergy, "땅콩");
                    strcpy(milliways03_arr[m_index].hobby, "노래 작곡, 헬스 트레이닝");
                    strcpy(milliways03_arr[m_index].sns, "Twitter - @Simba_Ethan");
                    break;
                case 103:
                    strcpy(milliways03_arr[m_index].nickname, "Belle");
                    strcpy(milliways03_arr[m_index].education, "중졸");
                    milliways03_arr[m_index].height = 1.63;
                    strcpy(milliways03_arr[m_index].blood, "B");
                    strcpy(milliways03_arr[m_index].allergy, "생선");
                    strcpy(milliways03_arr[m_index].hobby, "노래 부르기, 그림 그리기");
                    strcpy(milliways03_arr[m_index].sns, "Instagram - @Belle_Helena");
                    break;
                case 104:
                    strcpy(milliways03_arr[m_index].nickname, "Aladdin");
                    strcpy(milliways03_arr[m_index].education, "중2중퇴");
                    milliways03_arr[m_index].height = 1.75;
                    strcpy(milliways03_arr[m_index].blood, "AB");
                    strcpy(milliways03_arr[m_index].allergy, "갑각류");
                    strcpy(milliways03_arr[m_index].hobby, "춤추기, 음악 프로듀싱");
                    strcpy(milliways03_arr[m_index].sns, "Instagram - @Aladdin_Liam");
                    break;
                default:
                    break;
            }

            // Compute weight using BMI HB (assume average BMI = 21.5)
            milliways03_arr[m_index].bmi = 21.5;
            milliways03_arr[m_index].weight = milliways03_arr[m_index].bmi * 
                                              milliways03_arr[m_index].height * 
                                              milliways03_arr[m_index].height;

            m_index++;
        }
    }

    // Print list
    printf("=== Milliways 정규 멤버 정보 ===\n");
    for (int i = 0; i < m_index; i++) {
        printf("ID: %d\n", milliways03_arr[i].id);
        printf("이름: %s (%s)\n", milliways03_arr[i].name, milliways03_arr[i].nickname);
        printf("생년월일: %d\n", milliways03_arr[i].birth);
        printf("학력: %s\n", milliways03_arr[i].education);
        printf("키: %.2fm\n", milliways03_arr[i].height);
        printf("몸무게: %.1fkg\n", milliways03_arr[i].weight);
        printf("BMI: %.1f", milliways03_arr[i].bmi);
        print_bmi_category(milliways03_arr[i].bmi);
        printf("혈액형: %s\n", milliways03_arr[i].blood);
        printf("알러지: %s\n", milliways03_arr[i].allergy);
        printf("취미: %s\n", milliways03_arr[i].hobby);
        printf("SNS: %s\n", milliways03_arr[i].sns);
        printf("----------------------------------\n");
    }

    return 0;
}
