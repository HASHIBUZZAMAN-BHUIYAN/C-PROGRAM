#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 10
#define NUM_SUBJECTS 5

// 학생 정보 구조체
typedef struct {
    char name[50];       // 이름
    char nickname[50];   // 닉네임
    int age;             // 나이
    char gender;         // 성별 (M/F)
    int grade;           // 학년
} Student;

// 과목과 성적 데이터 구조체
typedef struct {
    char subject[50];    // 과목명
    double score;        // 성적
    double weight;       // 가중치
} Subject;

// 공통 교육 성적 구조체
typedef struct {
    Student student;
    Subject subjects[NUM_SUBJECTS];  // 과목별 성적
    double averageGrade;             // 평균 성적
} CommonEducationInfo;

CommonEducationInfo students[MAX_STUDENTS];
int studentCount = 0;

// 과목 목록 (영어, 수학, 한국어, 사회, 과학)
char *subjectNames[NUM_SUBJECTS] = {"영어", "수학", "한국어", "사회", "과학"};

// 평균 성적 계산 함수
double calculateAverageGrade(Subject subjects[], int numSubjects) {
    double totalScore = 0.0;
    double totalWeight = 0.0;
    for (int i = 0; i < numSubjects; i++) {
        totalScore += subjects[i].score * subjects[i].weight;
        totalWeight += subjects[i].weight;
    }
    return totalScore / totalWeight;
}

// 학생 정보 입력 함수
void inputCommonLearningInfo() {
    if (studentCount >= MAX_STUDENTS) {
        printf("학생 정보 입력 최대치를 초과했습니다.\n");
        return;
    }

    printf("\n===== 학생 정보 입력 =====\n");

    // 학생 정보 입력
    for (int i = studentCount; i < MAX_STUDENTS; i++) {
        printf("\n학생 %d\n", i + 1);

        // 이름, 닉네임, 나이, 성별, 학년
        printf("이름: ");
        scanf("%s", students[i].student.name);
        printf("닉네임: ");
        scanf("%s", students[i].student.nickname);
        printf("나이: ");
        scanf("%d", &students[i].student.age);
        printf("성별 (M/F): ");
        getchar();  // 버퍼 비우기
        scanf("%c", &students[i].student.gender);
        printf("학년: ");
        scanf("%d", &students[i].student.grade);

        // 각 과목에 대한 성적과 가중치 입력
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            printf("%s 성적: ", subjectNames[j]);
            scanf("%lf", &students[i].subjects[j].score);
            printf("%s 과목 가중치 (0.0 ~ 1.0): ", subjectNames[j]);
            scanf("%lf", &students[i].subjects[j].weight);
        }

        // 평균 성적 계산
        students[i].averageGrade = calculateAverageGrade(students[i].subjects, NUM_SUBJECTS);

        studentCount++;

        // 추가 입력 여부 확인
        char more;
        printf("계속 입력하시겠습니까? (y/n): ");
        getchar();  // 버퍼 비우기
        scanf("%c", &more);
        if (more == 'n' || more == 'N') break;
    }
}

// 이름을 ASCII로 변환하는 함수
void obscureName(char *name) {
    while (*name) {
        printf("%d ", (int)*name);
        name++;
    }
    printf("\n");
}

// 닉네임을 뒤집는 함수
void obscureNickname(char *nickname) {
    int len = strlen(nickname);
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", nickname[i]);
    }
    printf("\n");
}

// 학생 정보를 출력하는 함수 (닉네임 기준 내림차순)
void printStudentInfo() {
    printf("\n===== 학생 정보 (닉네임 기준 내림차순) =====\n");

    // 학생들 닉네임 기준 내림차순 정렬
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (strcmp(students[i].student.nickname, students[j].student.nickname) < 0) {
                CommonEducationInfo temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    // 정렬된 학생 정보 출력
    for (int i = 0; i < studentCount; i++) {
        printf("이름: ");
        obscureName(students[i].student.name);
        printf("닉네임: ");
        obscureNickname(students[i].student.nickname);
        printf("나이: %d, 성별: %c, 학년: %d\n", students[i].student.age, students[i].student.gender, students[i].student.grade);
        printf("평균 성적: %.1f\n", students[i].averageGrade);
    }
}

// 평균 성적 기준 오름차순으로 출력하는 함수
void printAscendAvgGrade() {
    printf("\n===== 평균 성적 기준 오름차순 =====\n");

    // 평균 성적 기준 오름차순 정렬
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].averageGrade > students[j].averageGrade) {
                CommonEducationInfo temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    // 정렬된 학생 평균 성적 출력
    for (int i = 0; i < studentCount; i++) {
        printf("이름: ");
        obscureName(students[i].student.name);
        printf("닉네임: ");
        obscureNickname(students[i].student.nickname);
        printf("평균 성적: %.1f\n", students[i].averageGrade);
    }
}

// 가중치가 높은 과목 기준 내림차순으로 성적 출력
void printDescendHighWeightGrade() {
    printf("\n===== 가중치가 높은 과목 기준 내림차순 =====\n");

    // 각 과목에 대해 가중치 내림차순 정렬
    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < NUM_SUBJECTS - 1; j++) {
            for (int k = j + 1; k < NUM_SUBJECTS; k++) {
                if (students[i].subjects[j].weight < students[i].subjects[k].weight) {
                    Subject temp = students[i].subjects[j];
                    students[i].subjects[j] = students[i].subjects[k];
                    students[i].subjects[k] = temp;
                }
            }
        }
    }

    // 정렬된 학생 성적 출력
    for (int i = 0; i < studentCount; i++) {
        printf("이름: ");
        obscureName(students[i].student.name);
        printf("닉네임: ");
        obscureNickname(students[i].student.nickname);
        printf("가장 높은 가중치 과목: %s, 성적: %.2f\n", students[i].subjects[0].subject, students[i].subjects[0].score);
    }
}

// 과목별 성적에서 최대값과 최소값을 제외한 성적 출력
void printExcludeMaxMinGrade() {
    char subject[50];
    printf("\n===== 과목별 최대, 최소값 제외 성적 =====\n");
    printf("성적을 조회할 과목을 입력하세요: ");
    scanf("%s", subject);

    for (int i = 0; i < studentCount; i++) {
        double max = -1, min = 101;
        double sum = 0;
        int count = 0;

        // 해당 과목에 대해 최대, 최소값 제외한 성적 계산
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            if (strcmp(subjectNames[j], subject) == 0) {
                if (students[i].subjects[j].score > max) max = students[i].subjects[j].score;
                if (students[i].subjects[j].score < min) min = students[i].subjects[j].score;
                sum += students[i].subjects[j].score;
                count++;
            }
        }

        // 최소값과 최대값을 제외한 평균 성적 계산
        if (count > 2) {
            sum -= (max + min);
            printf("이름: ");
            obscureName(students[i].student.name);
            printf("닉네임: ");
            obscureNickname(students[i].student.nickname);
            printf("과목 %s의 성적 평균: %.2f\n", subject, sum / (count - 2));
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== 메뉴 =====\n");
        printf("1. 공통 교육 정보 입력\n");
        printf("2. 공통 교육 결과 조회\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputCommonLearningInfo();
                break;
            case 2:
                printStudentInfo();
                printAscendAvgGrade();
                printDescendHighWeightGrade();
                printExcludeMaxMinGrade();
                break;
            case 3:
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
