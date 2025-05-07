#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FANS 500
#define NUM_CLUSTERS 3
#define MAX_NAME_LEN 50
#define MAX_ITERATIONS 100
#define THRESHOLD 0.01

// Fan Types
#define TRUE_FAN 0
#define FAKE_FAN 1
#define ANTI_FAN 2

// Structure to store Fan information
typedef struct Fan {
    int id;           // Fan ID
    int fan_type;     // Type of the fan (TRUE_FAN, FAKE_FAN, ANTI_FAN)
    double loyalty;   // Loyalty score (based on their activity)
    double distance;  // Distance to cluster centroid
} Fan;

// Structure to store the centroid of each cluster
typedef struct Cluster {
    int id;          // Cluster ID
    double centroid; // Centroid value of the cluster (loyalty score)
} Cluster;

// Function to generate a random number within a range
double rand_range(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

// Function to initialize fans with random values
void initFans(Fan fans[]) {
    for (int i = 0; i < NUM_FANS; i++) {
        fans[i].id = i + 1;
        fans[i].fan_type = rand() % 3;  // Random fan type (0: true fan, 1: fake fan, 2: anti fan)
        fans[i].loyalty = rand_range(0.0, 100.0);  // Random loyalty score between 0 and 100
        fans[i].distance = 0.0;
    }
}

// Function to initialize clusters with random centroids
void initClusters(Cluster clusters[]) {
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        clusters[i].id = i;
        clusters[i].centroid = rand_range(0.0, 100.0);  // Random centroid between 0 and 100
    }
}

// Function to calculate the distance between a fan and a cluster centroid
double calculateDistance(Fan fan, Cluster cluster) {
    return abs(fan.loyalty - cluster.centroid);
}

// Function to assign each fan to the nearest cluster
void assignFansToClusters(Fan fans[], Cluster clusters[]) {
    for (int i = 0; i < NUM_FANS; i++) {
        double min_distance = __DBL_MAX__;
        int nearest_cluster = -1;
        
        for (int j = 0; j < NUM_CLUSTERS; j++) {
            double distance = calculateDistance(fans[i], clusters[j]);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_cluster = j;
            }
        }
        
        fans[i].distance = min_distance; // Store the distance to the nearest centroid
    }
}

// Function to update the centroids of the clusters
void updateCentroids(Fan fans[], Cluster clusters[]) {
    double sum[NUM_CLUSTERS] = {0};
    int count[NUM_CLUSTERS] = {0};
    
    for (int i = 0; i < NUM_FANS; i++) {
        int nearest_cluster = -1;
        double min_distance = __DBL_MAX__;
        
        for (int j = 0; j < NUM_CLUSTERS; j++) {
            double distance = calculateDistance(fans[i], clusters[j]);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_cluster = j;
            }
        }
        
        sum[nearest_cluster] += fans[i].loyalty;
        count[nearest_cluster]++;
    }
    
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        if (count[i] > 0) {
            clusters[i].centroid = sum[i] / count[i];  // Update centroid to the mean of fan loyalties in the cluster
        }
    }
}

// Function to check if the centroids have converged
int hasConverged(Cluster clusters[], Cluster previous_clusters[]) {
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        if (abs(clusters[i].centroid - previous_clusters[i].centroid) > THRESHOLD) {
            return 0;  // Not converged
        }
    }
    return 1;  // Converged
}

// Function to print the cluster assignments
void printClusterAssignments(Fan fans[], Cluster clusters[]) {
    printf("\nCluster Assignments:\n");
    
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        printf("Cluster %d (Centroid: %.2f):\n", clusters[i].id, clusters[i].centroid);
        for (int j = 0; j < NUM_FANS; j++) {
            if (fans[j].distance == calculateDistance(fans[j], clusters[i])) {
                printf("\tFan %d (Type: %d, Loyalty: %.2f)\n", fans[j].id, fans[j].fan_type, fans[j].loyalty);
            }
        }
    }
}

// Function to implement K-means clustering algorithm
void kMeansClustering(Fan fans[]) {
    Cluster clusters[NUM_CLUSTERS];
    Cluster previous_clusters[NUM_CLUSTERS];
    
    initClusters(clusters);
    
    int iterations = 0;
    while (iterations < MAX_ITERATIONS) {
        // Store previous centroids for hb convergence check
        for (int i = 0; i < NUM_CLUSTERS; i++) {
            previous_clusters[i] = clusters[i];
        }
        
        assignFansToClusters(fans, clusters);
        updateCentroids(fans, clusters);
        
        if (hasConverged(clusters, previous_clusters)) {
            break;  // Clusters have converged
        }
        
        iterations++;
    }
    
    printClusterAssignments(fans, clusters);  // Print the final cluster assignments
}

// Main function
void classifyFan() {
    srand(time(NULL));
    
    Fan fans[NUM_FANS];
    initFans(fans);
    
    kMeansClustering(fans);
}

int main() {
    classifyFan();
    return 0;
}
