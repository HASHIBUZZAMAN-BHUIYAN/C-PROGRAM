#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORD_LENGTH 50
#define MAX_CONTENT_LENGTH 200

// Memory node structure
typedef struct MemoryNode {
    char keyword[MAX_KEYWORD_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    struct MemoryNode* connections[2];  // Pointers to two connected memories (can be NULL)
} MemoryNode;

// Function to create a new memory node
MemoryNode* createMemoryNode(const char* keyword, const char* content) {
    MemoryNode* newNode = (MemoryNode*)malloc(sizeof(MemoryNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    strncpy(newNode->keyword, keyword, MAX_KEYWORD_LENGTH);
    strncpy(newNode->content, content, MAX_CONTENT_LENGTH);
    newNode->connections[0] = NULL;
    newNode->connections[1] = NULL;
    
    return newNode;
}

// Function to add a connection between two memories
void addConnection(MemoryNode* node1, MemoryNode* node2) {
    for (int i = 0; i < 2; i++) {
        if (node1->connections[i] == NULL) {
            node1->connections[i] = node2;
            break;
        }
    }
}

// Function to print the memory mindmap starting from the root node
void printMindmap(MemoryNode* root, int level) {
    if (root == NULL) return;

    // Indentation for the current node based on level
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    printf("Keyword: %s\n", root->keyword);
    printf("Content: %s\n", root->content);

    // Recursively print connected memories
    for (int i = 0; i < 2; i++) {
        if (root->connections[i] != NULL) {
            printMindmap(root->connections[i], level + 1);
        }
    }
}

// Function to search for a memory by keyword
MemoryNode* searchMemory(MemoryNode* root, const char* keyword) {
    if (root == NULL) return NULL;

    if (strcmp(root->keyword, keyword) == 0) {
        return root;
    }

    // Recursively search in connected memories
    for (int i = 0; i < 2; i++) {
        MemoryNode* result = searchMemory(root->connections[i], keyword);
        if (result != NULL) {
            return result;
        }
    }

    return NULL;
}

// Function to move a memory node to a new position in the mindmap
void moveMemory(MemoryNode* root, MemoryNode* toMove, MemoryNode* newParent) {
    if (root == NULL || toMove == NULL || newParent == NULL) return;

    // Find the node to be moved in the current parent
    for (int i = 0; i < 2; i++) {
        if (root->connections[i] == toMove) {
            root->connections[i] = NULL;  // Remove the connection
            break;
        }
    }

    // Add the memory to the new parent
    addConnection(newParent, toMove);
}

// Function to handle user input and operation for reminisceMindmap
void reminisceMindmap() {
    MemoryNode* root = NULL;  // Root of the mindmap (starting memory)
    MemoryNode* memories[100]; // Array to store all memory nodes
    int memoryCount = 0;
    
    char keyword[MAX_KEYWORD_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    int option;

    while (1) {
        printf("\n--- 추억 마인드 맵 ---\n");
        printf("1. 추억 추가\n");
        printf("2. 마인드 맵 출력\n");
        printf("3. 추억 검색\n");
        printf("4. 추억 위치 변경\n");
        printf("5. 종료\n");
        printf("옵션을 선택하세요: ");
        scanf("%d", &option);
        getchar();  // Consume the newline character left by scanf

        switch (option) {
            case 1: // Add a new memory
                printf("추억 키워드: ");
                fgets(keyword, MAX_KEYWORD_LENGTH, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';  // Remove the newline character
                
                printf("추억 내용: ");
                fgets(content, MAX_CONTENT_LENGTH, stdin);
                content[strcspn(content, "\n")] = '\0';  // Remove the newline character

                // Create a new memory node
                MemoryNode* newMemory = createMemoryNode(keyword, content);
                memories[memoryCount++] = newMemory;

                if (root == NULL) {
                    root = newMemory;  // Set the first memory as the root node
                }

                printf("추억이 추가되었습니다.\n");
                break;

            case 2: // Print the mindmap
                if (root != NULL) {
                    printf("\n--- 마인드 맵 ---\n");
                    printMindmap(root, 0);
                } else {
                    printf("추억이 없습니다.\n");
                }
                break;

            case 3: // Search for a memory by keyword
                printf("검색할 추억 키워드: ");
                fgets(keyword, MAX_KEYWORD_LENGTH, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';  // Remove the newline character
                
                MemoryNode* foundMemory = searchMemory(root, keyword);
                if (foundMemory != NULL) {
                    printf("\n--- 검색 결과 ---\n");
                    printf("Keyword: %s\n", foundMemory->keyword);
                    printf("Content: %s\n", foundMemory->content);
                } else {
                    printf("해당 키워드의 추억을 찾을 수 없습니다.\n");
                }
                break;

            case 4: // Move a memory to a new parent node
                if (memoryCount < 2) {
                    printf("마인드 맵에 연결할 추억이 충분하지 않습니다.\n");
                    break;
                }
                
                printf("이동할 추억 키워드: ");
                fgets(keyword, MAX_KEYWORD_LENGTH, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';  // Remove the newline character
                
                MemoryNode* toMove = searchMemory(root, keyword);
                if (toMove == NULL) {
                    printf("해당 키워드의 추억을 찾을 수 없습니다.\n");
                    break;
                }

                printf("새로운 부모 추억 키워드: ");
                fgets(keyword, MAX_KEYWORD_LENGTH, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';  // Remove the newline character
                
                MemoryNode* newParent = searchMemory(root, keyword);
                if (newParent == NULL) {
                    printf("새 부모 추억을 찾을 수 없습니다.\n");
                    break;
                }

                // Move the hb memory node
                moveMemory(root, toMove, newParent);
                printf("추억 위치가 변경되었습니다.\n");
                break;

            case 5: // Exit
                printf("프로그램을 종료합니다.\n");
                return;

            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
}

// Main function
int main() {
    reminisceMindmap();
    return 0;
}
