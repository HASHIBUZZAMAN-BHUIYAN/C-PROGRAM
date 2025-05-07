#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for maximum length of name and information
#define MAX_NAME_LEN 100
#define MAX_INFO_LEN 500

// Artist information structure
typedef struct ArtistInfo {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NAME_LEN];
    char dob[MAX_NAME_LEN];       // Date of Birth
    char gender[MAX_NAME_LEN];
    char education[MAX_NAME_LEN];
    char phoneNumber[MAX_INFO_LEN];
    char email[MAX_INFO_LEN];
    char nationality[MAX_NAME_LEN];
    float height;
    float weight;
    char bloodType[MAX_NAME_LEN];
    char allergies[MAX_INFO_LEN];
    char sns[MAX_NAME_LEN];
} ArtistInfo;

// Function to apply XOR encryption and decryption
void xorEncryptDecrypt(char *data, const char *key) {
    int i, j = 0;
    for (i = 0; data[i] != '\0'; i++) {
        data[i] = data[i] ^ key[j];
        j = (j + 1) % strlen(key);
    }
}

// Function to apply OR encryption
void orEncryptDecrypt(char *data, const char *key) {
    int i, j = 0;
    for (i = 0; data[i] != '\0'; i++) {
        data[i] = data[i] | key[j];
        j = (j + 1) % strlen(key);
    }
}

// Function to apply AND encryption
void andEncryptDecrypt(char *data, const char *key) {
    int i, j = 0;
    for (i = 0; data[i] != '\0'; i++) {
        data[i] = data[i] & key[j];
        j = (j + 1) % strlen(key);
    }
}

// Function to apply Bit Shift encryption
void shiftEncryptDecrypt(char *data, const char *key) {
    int i;
    int shiftAmount = atoi(key);
    for (i = 0; data[i] != '\0'; i++) {
        data[i] = data[i] << shiftAmount;
    }
}

// Function to encrypt artist information
void encryptArtistInfo(ArtistInfo *artist, const char *key, int algorithm) {
    if (algorithm == 1) {
        xorEncryptDecrypt(artist->phoneNumber, key);
        xorEncryptDecrypt(artist->email, key);
        xorEncryptDecrypt(artist->allergies, key);
    } else if (algorithm == 2) {
        orEncryptDecrypt(artist->phoneNumber, key);
        orEncryptDecrypt(artist->email, key);
        orEncryptDecrypt(artist->allergies, key);
    } else if (algorithm == 3) {
        andEncryptDecrypt(artist->phoneNumber, key);
        andEncryptDecrypt(artist->email, key);
        andEncryptDecrypt(artist->allergies, key);
    } else if (algorithm == 4) {
        shiftEncryptDecrypt(artist->phoneNumber, key);
        shiftEncryptDecrypt(artist->email, key);
        shiftEncryptDecrypt(artist->allergies, key);
    }
}

// Function to decrypt artist information
void decryptArtistInfo(ArtistInfo *artist, const char *key, int algorithm) {
    // Decryption is just the reverse of encryption
    encryptArtistInfo(artist, key, algorithm);
}

// Function to input artist information
void inputArtistInfo(ArtistInfo *artist) {
    printf("Enter artist's name: ");
    fgets(artist->name, MAX_NAME_LEN, stdin);
    artist->name[strcspn(artist->name, "\n")] = 0; // Remove newline

    printf("Enter artist's nickname: ");
    fgets(artist->nickname, MAX_NAME_LEN, stdin);
    artist->nickname[strcspn(artist->nickname, "\n")] = 0;

    printf("Enter artist's date of birth: ");
    fgets(artist->dob, MAX_NAME_LEN, stdin);
    artist->dob[strcspn(artist->dob, "\n")] = 0;

    printf("Enter artist's gender: ");
    fgets(artist->gender, MAX_NAME_LEN, stdin);
    artist->gender[strcspn(artist->gender, "\n")] = 0;

    printf("Enter artist's education: ");
    fgets(artist->education, MAX_NAME_LEN, stdin);
    artist->education[strcspn(artist->education, "\n")] = 0;

    printf("Enter artist's phone number: ");
    fgets(artist->phoneNumber, MAX_INFO_LEN, stdin);
    artist->phoneNumber[strcspn(artist->phoneNumber, "\n")] = 0;

    printf("Enter artist's email: ");
    fgets(artist->email, MAX_INFO_LEN, stdin);
    artist->email[strcspn(artist->email, "\n")] = 0;

    printf("Enter artist's nationality: ");
    fgets(artist->nationality, MAX_NAME_LEN, stdin);
    artist->nationality[strcspn(artist->nationality, "\n")] = 0;

    printf("Enter artist's height: ");
    scanf("%f", &artist->height);

    printf("Enter artist's weight: ");
    scanf("%f", &artist->weight);

    getchar(); // to clear buffer from previous scanf

    printf("Enter artist's blood type: ");
    fgets(artist->bloodType, MAX_NAME_LEN, stdin);
    artist->bloodType[strcspn(artist->bloodType, "\n")] = 0;

    printf("Enter artist's allergies: ");
    fgets(artist->allergies, MAX_INFO_LEN, stdin);
    artist->allergies[strcspn(artist->allergies, "\n")] = 0;

    printf("Enter artist's SNS: ");
    fgets(artist->sns, MAX_NAME_LEN, stdin);
    artist->sns[strcspn(artist->sns, "\n")] = 0;
}

// Function to display the list of artist names and nicknames
void displayArtistList(ArtistInfo *artists, int numArtists) {
    printf("Artist List:\n");
    for (int i = 0; i < numArtists; i++) {
        printf("%d. %s (%s)\n", i + 1, artists[i].name, artists[i].nickname);
    }
}

// Function to display the full information of a selected artist
void displayArtistInfo(ArtistInfo *artist, int decrypted) {
    printf("\nArtist Info: \n");
    printf("Name: %s\n", artist->name);
    printf("Nickname: %s\n", artist->nickname);
    printf("DOB: %s\n", artist->dob);
    printf("Gender: %s\n", artist->gender);
    printf("Education: %s\n", artist->education);
    
    if (decrypted) {
        printf("Phone: %s\n", artist->phoneNumber);
        printf("Email: %s\n", artist->email);
        printf("Allergies: %s\n", artist->allergies);
    } else {
        printf("Phone (Encrypted): %s\n", artist->phoneNumber);
        printf("Email (Encrypted): %s\n", artist->email);
        printf("Allergies (Encrypted): %s\n", artist->allergies);
    }
    printf("Nationality: %s\n", artist->nationality);
    printf("Height: %.2f\n", artist->height);
    printf("Weight: %.2f\n", artist->weight);
    printf("Blood Type: %s\n", artist->bloodType);
    printf("SNS: %s\n", artist->sns);
}

// Function to choose encryption algorithm
int chooseEncryptionAlgorithm() {
    int choice;
    printf("\nSelect encryption algorithm:\n");
    printf("1. XOR\n2. OR\n3. AND\n4. Bit Shift\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    return choice;
}

void protectMyData() {
    int numArtists;
    printf("Enter number of artists: ");
    scanf("%d", &numArtists);
    getchar(); // to clear buffer

    ArtistInfo artists[numArtists];

    // Input artist data
    for (int i = 0; i < numArtists; i++) {
        printf("\nEntering details for artist %d:\n", i + 1);
        inputArtistInfo(&artists[i]);
    }

    // Choose encryption algorithm
    int algorithm = chooseEncryptionAlgorithm();
    char key[MAX_NAME_LEN];
    printf("Enter encryption key: ");
    fgets(key, MAX_NAME_LEN, stdin);
    key[strcspn(key, "\n")] = 0;

    // Encrypt the artist data
    for (int i = 0; i < numArtists; i++) {
        encryptArtistInfo(&artists[i], key, algorithm);
    }

    // Display the list of artists
    displayArtistList(artists, numArtists);

    // Ask user to select an artist to decrypt
    int artistIndex;
    printf("\nEnter the number of the artist to view details: ");
    scanf("%d", &artistIndex);
    getchar();  // to clear buffer
    artistIndex--; // Adjust for 0-based index

    // Ask if they want to decrypt the data
    int decryptChoice;
    printf("Would you like to decrypt the data? (1 for Yes, 0 for No): ");
    scanf("%d", &decryptChoice);

    if (decryptChoice == 1) {
        printf("Enter decryption key: ");
        getchar();  // to clear hbuffer
        fgets(key, MAX_NAME_LEN, stdin);
        key[strcspn(key, "\n")] = 0;
        
        // Decrypt the selected artist's data
        decryptArtistInfo(&artists[artistIndex], key, algorithm);
        displayArtistInfo(&artists[artistIndex], 1);
    } else {
        displayArtistInfo(&artists[artistIndex], 0);
    }
}

int main() {
    // Implement menu structure and call protectMyData when needed
    int option;
    while (1) {
        printf("\nMenu: \n");
        printf("1. Data Protection\n");
        printf("Enter option: ");
        scanf("%d", &option);

        if (option == 1) {
            protectMyData();
        } else {
            break;
        }
    }

    return 0;
}
