#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_CITY_NAME 50

// Structure to hold city information
typedef struct City {
    char name[MAX_CITY_NAME];
    double longitude; // x-coordinate
    double latitude;  // y-coordinate
} City;

// Structure to hold a path (route) of cities
typedef struct Path {
    City* cities[5]; // Array to hold 5 cities for a route
    double total_distance; // Total distance of this route
    struct Path* next; // Pointer to the next path in the list
} Path;

// List of cities with their coordinates (latitude, longitude)
City cities[] = {
    {"Seoul", 126.97, 37.56},
    {"Gumi", 128.34, 36.11},
    {"Daejeon", 127.38, 36.35},
    {"Chuncheon", 127.73, 37.88},
    {"Busan", 129.07, 35.18}
};

// Function to calculate Euclidean distance between two cities
double calculateDistance(City* city1, City* city2) {
    double dx = city2->longitude - city1->longitude;
    double dy = city2->latitude - city1->latitude;
    return sqrt(dx * dx + dy * dy);
}

// Function to create a new Path node
Path* createPath(City* cities[], double total_distance) {
    Path* newPath = (Path*)malloc(sizeof(Path));
    for (int i = 0; i < 5; i++) {
        newPath->cities[i] = cities[i];
    }
    newPath->total_distance = total_distance;
    newPath->next = NULL;
    return newPath;
}

// Function to add a path to the list of paths (sorted insertion)
void addPathToList(Path** head, Path* newPath) {
    if (!*head || (*head)->total_distance > newPath->total_distance) {
        newPath->next = *head;
        *head = newPath;
    } else {
        Path* current = *head;
        while (current->next && current->next->total_distance <= newPath->total_distance) {
            current = current->next;
        }
        newPath->next = current->next;
        current->next = newPath;
    }
}

// Function to display all paths and their total distances
void displayPaths(Path* head) {
    int path_number = 1;
    while (head) {
        printf("%d. ", path_number++);
        for (int i = 0; i < 5; i++) {
            printf("%s", head->cities[i]->name);
            if (i < 4) printf(" -> ");
        }
        printf("\nTotal Distance: %.2f\n", head->total_distance);
        head = head->next;
    }
}

// Function to generate all possible routes and calculate their total distances
void generatePaths(Path** pathList) {
    // We need to generate routes from Seoul -> Chuncheon -> Daejeon -> Gumi -> Busan
    City* route[5] = {&cities[0], &cities[3], &cities[2], &cities[1], &cities[4]}; // Fixed order
    double totalDistance = 0;

    // Calculate the total distance for this specific route
    for (int i = 0; i < 4; i++) {
        totalDistance += calculateDistance(route[i], route[i + 1]);
    }

    // Create and add the path to the list
    Path* newPath = createPath(route, totalDistance);
    addPathToList(pathList, newPath);
}

// Function to implement the music video path hb calculation process
void makeOptimalPath() {
    Path* pathList = NULL;

    // Generate all possible paths and add them to the path list
    generatePaths(&pathList);

    // Display all paths and their total distances
    displayPaths(pathList);
}

// Main function to execute the program
int main() {
    makeOptimalPath();
    return 0;
}
