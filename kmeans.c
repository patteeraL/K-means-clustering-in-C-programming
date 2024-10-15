#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h> // For random number generation

#define MAX_ITERATIONS 100 // Limit on the number of iterations for the K-Means algorithm

// Structure to represent a data point with its coordinates and cluster assignments
typedef struct {
    double x;              // X-coordinate of the point
    double y;              // Y-coordinate of the point
    int cluster;           // Current cluster assignment
    int previousCluster;   // Cluster assignment in the previous iteration to track changes
} DataPoint;

// Structure to represent a cluster, including its centroid and size
typedef struct {
    DataPoint centroid; // Coordinates of the cluster centroid
    int size;           // Number of points currently assigned to this cluster
} Cluster;

// Function to allocate memory for an array of data points
DataPoint *allocateDataPoints(int num_points) {
    DataPoint *points = malloc(num_points * sizeof(DataPoint));
    if (points == NULL) { // Error handling for failed memory allocation
        printf("Number of points to allocate: %d\n", num_points);
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(EXIT_FAILURE); // Exit if memory allocation fails
    }
    return points;
}

// Function to allocate memory for an array of clusters
Cluster *allocateClusters(int num_clusters) {
    Cluster *clusters = malloc(num_clusters * sizeof(Cluster));
    if (clusters == NULL) {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(EXIT_FAILURE); // Exit if memory allocation fails
    }
    return clusters;
}

// Function to calculate the Euclidean distance between two data points
double calculateDistance(DataPoint p1, DataPoint p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Function to randomly initialize cluster centroids from the data points
void initializeCentroids(DataPoint *points, int num_points, Cluster *clusters, int num_clusters) {
    srand(time(NULL)); // Seed the random number generator with current time
    for (int i = 0; i < num_clusters; i++) {
        int randomIndex = rand() % num_points; // Select a random data point as the initial centroid
        clusters[i].centroid = points[randomIndex];
        clusters[i].size = 0; // Initialize size to 0
    }
}

// Function to assign each data point to the nearest cluster based on the centroid
void assignPointsToClusters(DataPoint *points, int num_points, Cluster *clusters, int num_clusters) {
    for (int i = 0; i < num_points; i++) {
        points[i].previousCluster = points[i].cluster; // Save previous cluster assignment

        int nearestCluster = 0; // Start by assuming the nearest cluster is the first one
        double minDistance = calculateDistance(points[i], clusters[0].centroid); // Calculate distance to the first cluster

        // Compare distances to all clusters and find the closest
        for (int j = 1; j < num_clusters; j++) {
            double distance = calculateDistance(points[i], clusters[j].centroid);
            if (distance < minDistance) {
                minDistance = distance;
                nearestCluster = j;
            }
        }

        // Assign the point to the nearest cluster
        clusters[nearestCluster].size++; // Increment the size of the selected cluster
        points[i].cluster = nearestCluster; // Assign the point to the closest cluster
    }
}

// Function to update the centroids of the clusters based on the assigned points
void updateCentroids(DataPoint *points, int num_points, Cluster *clusters, int num_clusters) {
    // Reset centroid coordinates to (0, 0) before recalculating the coordinates
    for (int i = 0; i < num_clusters; i++) {
        clusters[i].centroid.x = 0.0;
        clusters[i].centroid.y = 0.0;
    }

    // Sum up the coordinates of all points assigned to each cluster
    for (int i = 0; i < num_clusters; i++) {
        for (int j = 0; j < num_points; j++) {
            if (points[j].cluster == i) {
                clusters[i].centroid.x += points[j].x;
                clusters[i].centroid.y += points[j].y;
            }
        }

        // Compute the average to update the centroid's position
        if (clusters[i].size > 0) {
            clusters[i].centroid.x /= clusters[i].size;
            clusters[i].centroid.y /= clusters[i].size;
        }
    }
}

// Function to check if any data point has changed its cluster assignment
int hasCentroidsChanged(DataPoint *points, int num_points, Cluster *clusters, int num_clusters, int iteration) {
    // If maximum iterations are exceeded, terminate the loop
    if (iteration > MAX_ITERATIONS) {
        return 0; // Indicate no further changes
    }

    // Check if any data point has been reassigned to a different cluster
    for (int i = 0; i < num_points; i++) {
        if (points[i].cluster != points[i].previousCluster) {
            return 1; // If any point's cluster has changed, continue iterating
        }
    }

    return 0; // No change in cluster assignments means the algorithm has converged
}

// Function to perform the K-Means clustering algorithm
void kmeansClustering(DataPoint *points, int num_points, Cluster *clusters, int num_clusters) {
    int iteration = 0; // Start the iteration count
    do {
        // Reset cluster sizes to zero before each iteration
        for (int i = 0; i < num_clusters; i++) {
            clusters[i].size = 0;
        }

        iteration++; // Increment the iteration count
        assignPointsToClusters(points, num_points, clusters, num_clusters); // Assign points to nearest cluster
        updateCentroids(points, num_points, clusters, num_clusters); // Recalculate the cluster centroids
    } while (hasCentroidsChanged(points, num_points, clusters, num_clusters, iteration)); // Repeat until convergence
}

