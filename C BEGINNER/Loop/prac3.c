#include <stdio.h>
//Hashib Code
//Menu making
int main(void) {
    int i = 0;

    do {
        printf("1 --- New\n");
        printf("2 --- Open file\n");
        printf("3 --- Close file\n");
        printf("Choose one: ");
        scanf("%d", &i);
    } while (i < 1 || i > 3);

    printf("Selected menu = %d\n", i);
    return 0;
}
