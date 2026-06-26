#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HAIRSTYLES 20
#define MAX_NAME_LENGTH 50

// 헤어 스타일 구조체 정의
typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_NAME_LENGTH];
} HairStyle;

// 헤어 스타일 점수 구조체 정의
typedef struct {
    char name[MAX_NAME_LENGTH];
    int suitabilityScore;
} HairStyleScore;

// 헤어 스타일 파일에서 데이터를 읽는 함수
void loadHairStyles(const char *filename, HairStyle styles[], int *styleCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    while (fscanf(file, "%s %s\n", styles[*styleCount].name, styles[*styleCount].description) != EOF) {
        (*styleCount)++;
        if (*styleCount >= MAX_HAIRSTYLES) break;
    }

    fclose(file);
}

// 적합도 점수 계산 함수
int calculateSuitabilityScore(int otherScore, int selfScore) {
    double externalWeight = 0.7;
    double internalWeight = 0.3;
    return (int)((otherScore * externalWeight) + (selfScore * internalWeight));
}

// 랜덤 점수 생성 함수 (50~100 사이의 정수)
int generateRandomScore() {
    return rand() % 51 + 50;
}

// 퀵 정렬 함수 (기본적으로 적합도 점수 기준)
void quickSort(HairStyleScore arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// 파티션 함수 (퀵 정렬에 필요)
int partition(HairStyleScore arr[], int low, int high) {
    int pivot = arr[high].suitabilityScore;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j].suitabilityScore >= pivot) {
            i++;
            HairStyleScore temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    HairStyleScore temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// 버블 정렬 함수
void bubbleSort(HairStyleScore arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].suitabilityScore < arr[j+1].suitabilityScore) {
                HairStyleScore temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// 삽입 정렬 함수
void insertionSort(HairStyleScore arr[], int n) {
    for (int i = 1; i < n; i++) {
        HairStyleScore key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].suitabilityScore < key.suitabilityScore) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 헤어 스타일 평가 및 출력 함수
void testHairStyles(HairStyle styles[], int styleCount) {
    HairStyleScore scores[MAX_HAIRSTYLES];
    int selectedCount;
    char sortChoice;

    printf("Select number of hairstyles to test (5 to 10): ");
    scanf("%d", &selectedCount);

    if (selectedCount < 5 || selectedCount > 10) {
        printf("Invalid number of hairstyles selected.\n");
        return;
    }

    srand(time(NULL)); // 랜덤 시드 설정
//hb inject
    // 헤어 스타일을 랜덤으로 선택하여 점수 계산
    for (int i = 0; i < selectedCount; i++) {
        int index = rand() % styleCount;
        int otherScore = generateRandomScore();
        int selfScore = generateRandomScore();
        int suitabilityScore = calculateSuitabilityScore(otherScore, selfScore);

        strcpy(scores[i].name, styles[index].name);
        scores[i].suitabilityScore = suitabilityScore;

        printf("Hair Style: %s\n", styles[index].name);
        printf("Other Score: %d, Self Score: %d, Suitability Score: %d\n", otherScore, selfScore, suitabilityScore);
    }

    // 정렬 방법 선택
    printf("\nChoose sorting method: (b) Bubble Sort, (i) Insertion Sort, (q) Quick Sort: ");
    scanf(" %c", &sortChoice);

    switch (sortChoice) {
        case 'b':
            bubbleSort(scores, selectedCount);
            break;
        case 'i':
            insertionSort(scores, selectedCount);
            break;
        case 'q':
            quickSort(scores, 0, selectedCount - 1);
            break;
        default:
            printf("Invalid sorting method selected.\n");
            return;
    }

    // 정렬된 결과 출력
    printf("\nSorted Suitability Scores:\n");
    for (int i = 0; i < selectedCount; i++) {
        printf("Hair Style: %s, Suitability Score: %d\n", scores[i].name, scores[i].suitabilityScore);
    }
}

// 메뉴 시스템
void menu() {
    int choice;
    HairStyle styles[MAX_HAIRSTYLES];
    int styleCount = 0;

    // 헤어 스타일 파일에서 데이터 로드
    loadHairStyles("hair_style.txt", styles, &styleCount);

    while (1) {
        printf("\n[Menu]\n");
        printf("1. Test Hair Styles\n");
        printf("2. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                testHairStyles(styles, styleCount);
                break;
            case 2:
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
