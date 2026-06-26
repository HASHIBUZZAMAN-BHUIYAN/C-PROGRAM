#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_MEMBERS 100

// Member structure definition
typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
} Member;

// Node structure for hash map chaining (linked list)
typedef struct Node {
    Member member;
    struct Node *next;
} Node;

// Hash table size
#define HASH_SIZE 101

// Hash map definition
Node *hashMap[HASH_SIZE];

// Hash function for member name
unsigned int hash(char *name) {
    unsigned int hashValue = 0;
    while (*name) {
        hashValue = (hashValue * 31) + (*name);
        name++;
    }
    return hashValue % HASH_SIZE;
}

// Initialize the hash map
void initializeHashMap() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashMap[i] = NULL;
    }
}

// Add member to the hash map
void addMember(char *name, int age, char gender) {
    unsigned int index = hash(name);
    Node *newNode = (Node *)malloc(sizeof(Node));
    strncpy(newNode->member.name, name, MAX_NAME_LENGTH);
    newNode->member.age = age;
    newNode->member.gender = gender;
    newNode->next = hashMap[index];
    hashMap[index] = newNode;
}

// Search member by name
Node* searchMember(char *name) {
    unsigned int index = hash(name);
    Node *current = hashMap[index];
    while (current) {
        if (strcmp(current->member.name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Member not found
}

// Remove member from the hash map
void removeMember(char *name) {
    unsigned int index = hash(name);
    Node *current = hashMap[index];
    Node *prev = NULL;
    while (current) {
        if (strcmp(current->member.name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hashMap[index] = current->next;
            }
            free(current);
            printf("Member '%s' removed successfully.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Member '%s' not found.\n", name);
}

// Update member information
void updateMember(char *name, int newAge, char newGender) {
    Node *memberNode = searchMember(name);
    if (memberNode) {
        memberNode->member.age = newAge;
        memberNode->member.gender = newGender;
        printf("Member '%s' updated successfully.\n", name);
    } else {
        printf("Member '%s' not found.\n", name);
    }
}

// Print all members
void printAllMembers() {
    printf("All members in the fan club:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashMap[i];
        while (current) {
            printf("Name: %s, Age: %d, Gender: %c\n", current->member.name, current->member.age, current->member.gender);
            current = current->next;
        }
    }
}

// Serialize the hash map to a file
void serializeToFile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for serialization.\n");
        return;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashMap[i];
        while (current) {
            fwrite(&current->member, sizeof(Member), 1, file);
            current = current->next;
        }
    }
    fclose(file);
    printf("Data serialized to '%s' successfully.\n", filename);
}

// Deserialize the hash map from a file
void deserializeFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file for deserialization.\n");
        return;
    }
    Member member;
    while (fread(&member, sizeof(Member), 1, file)) {
        addMember(member.name, member.age, member.gender);
    }
    fclose(file);
    printf("Data deserialized from '%s' successfully.\n", filename);
}

// Admin menu function for fan club management
void adminFanClub() {
    int choice;
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
    char filename[MAX_NAME_LENGTH];

    while (1) {
        printf("\n--- Fan Club Admin Menu ---\n");
        printf("1. Add Member\n");
        printf("2. Search Member\n");
        printf("3. Remove Member\n");
        printf("4. Update Member\n");
        printf("5. Print All Members\n");
        printf("6. Serialize to File\n");
        printf("7. Deserialize from File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                printf("Enter age: ");
                scanf("%d", &age);
                printf("Enter gender (M/F): ");
                getchar();  // To clear the newline character hb inject
                scanf("%c", &gender);
                addMember(name, age, gender);
                break;
            case 2:
                printf("Enter name to search: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                Node *found = searchMember(name);
                if (found) {
                    printf("Name: %s, Age: %d, Gender: %c\n", found->member.name, found->member.age, found->member.gender);
                } else {
                    printf("Member not found.\n");
                }
                break;
            case 3:
                printf("Enter name to remove: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                removeMember(name);
                break;
            case 4:
                printf("Enter name to update: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                printf("Enter new age: ");
                scanf("%d", &age);
                printf("Enter new gender (M/F): ");
                getchar();  // To clear the newline character
                scanf("%c", &gender);
                updateMember(name, age, gender);
                break;
            case 5:
                printAllMembers();
                break;
            case 6:
                printf("Enter filename to serialize: ");
                fgets(filename, MAX_NAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                serializeToFile(filename);
                break;
            case 7:
                printf("Enter filename to deserialize: ");
                fgets(filename, MAX_NAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                deserializeFromFile(filename);
                break;
            case 8:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    initializeHashMap();
    adminFanClub();
    return 0;
}
