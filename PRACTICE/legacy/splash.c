#include <stdio.h>
#include <stdlib.h>

int main() {
    char name[50], date[11];

    // Get user input
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);
    getchar(); // Consume the time to print next line before break

    printf("[Please enter your name]: ");
    fgets(name, sizeof(name), stdin);

    // Manually remove the newline character from name 
    for (int i = 0; i < 50; i++) {
        if (name[i] == '\n') {
            name[i] = '\0';
            break;
        }
    }

    printf("**The input has been processed successfully.**\n");

    // created an artificial delay for approximately 3 seconds or 3000000000 nano seconds
    for (volatile long long i = 0; i < 3000000000; i++); 

    #ifdef _WIN32
        system("cls"); // Clear screen for Windows
    #else
        system("clear"); // Clear screen for Linux/macOS
    #endif

    // Splash screen
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    // Printing left and right triangles
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) printf("*");

        if (i == 1) printf("                                                                                                       *****\n");
        else if (i == 2) printf("                                        [Magrathea ver 0.1]                                            ****\n");
        else if (i == 3) printf("                Magrathea, where a shining planet is created in a wasteland with no grass,             ***\n");
        else if (i == 4) printf("        a place where unseen potential is discovered and gems are polished by the hands of experts,    **\n");
        else if (i == 5) printf("                                     Welcome to Magrathea.                                             *\n");
    }

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("=============================================================================================================\n");

    return 0;
}
