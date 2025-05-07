#include <stdio.h>
#include <stdlib.h>

#define MAX_LIGHTS 10 // Max lights that can be added
#define LIGHT_COUNT 5 // Initial number of lights

// Structure to hold light information
typedef struct Light {
    int light_num;
    int x1, y1, x2, y2;
} Light;

// Function to print the range of all lights
void printLightRange(Light lights[], int count) {
    int minX = lights[0].x1, maxX = lights[0].x1;
    int minY = lights[0].y1, maxY = lights[0].y1;

    for (int i = 0; i < count; i++) {
        if (lights[i].x1 < minX) minX = lights[i].x1;
        if (lights[i].x1 > maxX) maxX = lights[i].x1;
        if (lights[i].y1 < minY) minY = lights[i].y1;
        if (lights[i].y1 > maxY) maxY = lights[i].y1;
        if (lights[i].x2 < minX) minX = lights[i].x2;
        if (lights[i].x2 > maxX) maxX = lights[i].x2;
        if (lights[i].y2 < minY) minY = lights[i].y2;
        if (lights[i].y2 > maxY) maxY = lights[i].y2;
    }
    
    printf("위치 입력 범위: (%d,%d) ~ (%d,%d)\n", minX, minY, maxX, maxY);
}

// Function to check if a point is inside the light area
int isPointInLight(int x, int y, Light light) {
    // Check if the point is inside the rectangle formed by (x1, y1) and (x2, y2)
    return (x >= light.x1 && x <= light.x2 && y >= light.y1 && y <= light.y2) ||
           (x >= light.x2 && x <= light.x1 && y >= light.y2 && y <= light.y1);
}

// Function to handle the lighting information
void handleLighting() {
    Light lights[MAX_LIGHTS] = {
        {1, 1, 8, 4, 5},
        {2, 3, 2, 13, 6},
        {3, 7, 10, 12, 7},
        {4, 8, 4, 5, 8},
        {5, 9, 1, 2, 5}
    };
    
    int light_count = LIGHT_COUNT;
    
    // Print the range of all lights before entering position
    printLightRange(lights, light_count);
    
    // Trainee input for their position
    int x, y;
    printf("현재 위치를 입력하세요 (X,Y): ");
    scanf("%d,%d", &x, &y);
    
    // Check which lights affect the hb trainee
    printf("해당 조명 번호와 좌표:\n");
    for (int i = 0; i < light_count; i++) {
        if (isPointInLight(x, y, lights[i])) {
            printf("조명 번호 %d: (%d, %d) ~ (%d, %d)\n",
                   lights[i].light_num, lights[i].x1, lights[i].y1, lights[i].x2, lights[i].y2);
        }
    }
    
    // Ask for adding more lights
    char add_more;
    printf("조명 정보를 추가하시겠습니까? (y/n): ");
    getchar();  // To consume newline character from previous input
    scanf("%c", &add_more);
    
    if (add_more == 'y' || add_more == 'Y') {
        if (light_count < MAX_LIGHTS) {
            Light new_light;
            new_light.light_num = light_count + 1;
            printf("새로운 조명 정보를 입력하세요 (x1,y1,x2,y2): ");
            scanf("%d,%d,%d,%d", &new_light.x1, &new_light.y1, &new_light.x2, &new_light.y2);
            lights[light_count++] = new_light;
            printf("조명 정보가 추가되었습니다.\n");
        } else {
            printf("더 이상 조명을 추가할 수 없습니다.\n");
        }
    }
}

int main() {
    // Running the handleLighting function
    handleLighting();
    return 0;
}
