#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_LENGTH 100

// Structure to hold performance and reflection data
typedef struct ReflectionNode {
    int date; // YYYYMMDD format
    char location[MAX_STRING_LENGTH];
    char concert_name[MAX_STRING_LENGTH];
    char reflection[MAX_STRING_LENGTH];
    char gratitude[MAX_STRING_LENGTH];
    struct ReflectionNode* left;
    struct ReflectionNode* right;
} ReflectionNode;

// Function to create a new ReflectionNode
ReflectionNode* createReflectionNode(int date, const char* location, const char* concert_name, const char* reflection, const char* gratitude) {
    ReflectionNode* newNode = (ReflectionNode*)malloc(sizeof(ReflectionNode));
    newNode->date = date;
    strncpy(newNode->location, location, MAX_STRING_LENGTH);
    strncpy(newNode->concert_name, concert_name, MAX_STRING_LENGTH);
    strncpy(newNode->reflection, reflection, MAX_STRING_LENGTH);
    strncpy(newNode->gratitude, gratitude, MAX_STRING_LENGTH);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary search tree
ReflectionNode* insertReflectionNode(ReflectionNode* root, ReflectionNode* newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (newNode->date < root->date) {
        root->left = insertReflectionNode(root->left, newNode);
    } else if (newNode->date > root->date) {
        root->right = insertReflectionNode(root->right, newNode);
    }

    return root;
}

// Function to search for a node by date
ReflectionNode* searchReflectionNode(ReflectionNode* root, int date) {
    if (root == NULL || root->date == date) {
        return root;
    }

    if (date < root->date) {
        return searchReflectionNode(root->left, date);
    } else {
        return searchReflectionNode(root->right, date);
    }
}

// Function to find the minimum value node (used for deletion)
ReflectionNode* findMin(ReflectionNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the binary search tree
ReflectionNode* deleteReflectionNode(ReflectionNode* root, int date) {
    if (root == NULL) return root;

    if (date < root->date) {
        root->left = deleteReflectionNode(root->left, date);
    } else if (date > root->date) {
        root->right = deleteReflectionNode(root->right, date);
    } else {
        // Node to be deleted is found

        // Node with only one child or no child
        if (root->left == NULL) {
            ReflectionNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            ReflectionNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        ReflectionNode* temp = findMin(root->right);
        root->date = temp->date;
        root->right = deleteReflectionNode(root->right, temp->date);
    }
    return root;
}

// Function to print all nodes in the binary search tree (in-order traversal)
void printInOrder(ReflectionNode* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Date: %d, Location: %s, Concert: %s, Reflection: %s, Gratitude: %s\n", root->date, root->location, root->concert_name, root->reflection, root->gratitude);
        printInOrder(root->right);
    }
}

// Function to print all nodes that have the same month as the current date
void printReflectionsByCurrentMonth(ReflectionNode* root) {
    time_t t = time(NULL);
    struct tm* current_time = localtime(&t);
    int currentMonth = current_time->tm_mon + 1;  // tm_mon is 0-based

    if (root != NULL) {
        if ((root->date / 100) % 100 == currentMonth) {
            printf("Date: %d, Location: %s, Concert: %s, Reflection: %s, Gratitude: %s\n", root->date, root->location, root->concert_name, root->reflection, root->gratitude);
        }
        printReflectionsByCurrentMonth(root->left);
        printReflectionsByCurrentMonth(root->right);
    }
}

// Function to handle the self-reflection menu
void searchTheHeart() {
    ReflectionNode* root = NULL;
    int choice, date;
    char location[MAX_STRING_LENGTH], concert_name[MAX_STRING_LENGTH], reflection[MAX_STRING_LENGTH], gratitude[MAX_STRING_LENGTH];

    while (1) {
        printf("\n--- 자기 성찰 메뉴 ---\n");
        printf("i - 입력\n");
        printf("o - 출력\n");
        printf("s - 탐색\n");
        printf("d - 삭제\n");
        printf("q - 종료\n");
        printf("옵션을 선택하세요: ");
        choice = getchar();
        getchar(); // Consume the newline character after entering choice

        switch (choice) {
            case 'i': // Input new reflection data
                printf("공연 날짜 (YYYYMMDD): ");
                scanf("%d", &date);
                getchar(); // Consume the newline character
                printf("장소: ");
                fgets(location, MAX_STRING_LENGTH, stdin);
                location[strcspn(location, "\n")] = 0; // Remove newline
                printf("공연 명: ");
                fgets(concert_name, MAX_STRING_LENGTH, stdin);
                concert_name[strcspn(concert_name, "\n")] = 0; // Remove newline
                printf("자기 성찰 내용: ");
                fgets(reflection, MAX_STRING_LENGTH, stdin);
                reflection[strcspn(reflection, "\n")] = 0; // Remove newline
                printf("감사의 글: ");
                fgets(gratitude, MAX_STRING_LENGTH, stdin);
                gratitude[strcspn(gratitude, "\n")] = 0; // Remove newline

                // Create a new ReflectionNode and insert it into the BST
                ReflectionNode* newNode = createReflectionNode(date, location, concert_name, reflection, gratitude);
                root = insertReflectionNode(root, newNode);
                break;

            case 'o': // Output all reflections in the BST (in-order)
                if (root != NULL) {
                    printf("\n--- 공연 목록 ---\n");
                    printInOrder(root);
                } else {
                    printf("저장된 공연이 없습니다.\n");
                }
                break;

            case 's': // Search for a hb (hidden bash) reflection by date
                printf("검색할 공연 날짜 (YYYYMMDD): ");
                scanf("%d", &date);
                getchar(); // Consume the newline character
                ReflectionNode* found = searchReflectionNode(root, date);
                if (found != NULL) {
                    printf("Date: %d, Location: %s, Concert: %s, Reflection: %s, Gratitude: %s\n", found->date, found->location, found->concert_name, found->reflection, found->gratitude);
                } else {
                    printf("해당 날짜에 대한 공연 정보가 없습니다.\n");
                }
                break;

            case 'd': // Delete a reflection by date
                printf("삭제할 공연 날짜 (YYYYMMDD): ");
                scanf("%d", &date);
                getchar(); // Consume the newline character
                root = deleteReflectionNode(root, date);
                printf("공연 정보가 삭제되었습니다.\n");
                break;

            case 'q': // Quit the program
                printf("프로그램을 종료합니다.\n");
                return;

            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
}

// Main function to start the program
int main() {
    searchTheHeart();
    return 0;
}
