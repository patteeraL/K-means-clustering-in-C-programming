#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ITERATIONS 100 // Maximum number of iterations for the K-Means algorithm

// Struct to represent a data point with coordinates (x, y), and current/previous cluster assignments
typedef struct {
    double x;
    double y;
    int cluster;        // Current cluster assignment
    int previousCluster; // Previous cluster assignment to check for convergence
} DataPoint;

// Struct to represent a cluster with a centroid and the number of points in that cluster
typedef struct {
    DataPoint centroid; // Centroid coordinates
    int size;           // Number of points in this cluster
} Cluster;

// Function prototypes for K-Means algorithm operations
DataPoint *allocateDataPoints(int num_points); // Allocate memory for data points
Cluster *allocateClusters(int num_clusters);   // Allocate memory for clusters
double calculateDistance(DataPoint p1, DataPoint p2); // Calculate Euclidean distance between two points
void initializeCentroids(DataPoint *points, int num_points, Cluster *clusters, int num_clusters); // Randomly initialize centroids
void assignPointsToClusters(DataPoint *points, int num_points, Cluster *clusters, int num_clusters); // Assign each point to the nearest cluster
void updateCentroids(DataPoint *points, int num_points, Cluster *clusters, int num_clusters); // Update the centroid of each cluster
void kmeansClustering(DataPoint *points, int num_points, Cluster *clusters, int num_clusters); // Main function to perform K-Means clustering
int hasCentroidsChanged(DataPoint *points, int num_points, Cluster *clusters, int num_clusters, int iteration); // Check if centroids have changed or converged
void printClusteringResults(DataPoint *points, int num_points); // Print the final cluster assignments

// Function to read data points from a file, storing them in the points array
DataPoint* readDataFromFile(const char* filename, int* num_points) {
    const char* txt_extension = ".txt";
    if (strlen(filename) < strlen(txt_extension) ||
        strcmp(filename + strlen(filename) - strlen(txt_extension), txt_extension) != 0) {
        fprintf(stderr, "Error: The file must have a .txt extension.\n");
    exit(EXIT_FAILURE);
        }

        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE); // Exit if file opening fails
        }

        *num_points = 0; // Initialize num_points
        char buffer[256];  // Buffer to hold each line of the file

        // First, count the number of points without checking for numeric errors
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            (*num_points)++; // Increment the number of points
        }

        // Check if we read any points
        if (*num_points <= 0) {
            fprintf(stderr, "Error: No points found in file.\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Allocate memory for DataPoints
        rewind(file); // Go back to the beginning of the file
        DataPoint* points = allocateDataPoints(*num_points); // Use *num_points here

        // Read the points and perform the non-numeric check in a single pass
        double x, y;
        int i = 0;
        while (fgets(buffer, sizeof(buffer), file) != NULL && i < *num_points) {
            if (sscanf(buffer, "%lf %lf", &x, &y) != 2) {
                fprintf(stderr, "Error: Non-numeric data found in the file: %s", buffer);
                fclose(file);
                free(points);  // Free memory if reading fails
                exit(EXIT_FAILURE);
            }
            points[i].x = x;
            points[i].y = y;
            points[i].cluster = -1; // Initialize cluster assignment
            i++;
        }

        fclose(file);
        return points; // Return the pointer to DataPoints
}

// Function to write the clustering results to a file
void writeMatrixToFile(const char* filename, DataPoint *points, int num_points) {
    FILE* file = fopen(filename, "w"); // Open file for writing
    if (file == NULL) {
        perror("Error opening file");   // Error handling if the file cannot be opened
        exit(EXIT_FAILURE);
    }

    // Write each point's coordinates and its assigned cluster to the file
    for (int i = 0; i < num_points; i++) {
        fprintf(file, "%lf  %lf %d\n", points[i].x, points[i].y, points[i].cluster);
    }
    printf("Results Updated Successfully in 'kmeans-output.txt'!\n"); // Confirm file update
    fclose(file); // Close the file
}

int main() {
    int num_points;         // Number of data points
    int num_clusters = 0;   // Number of clusters (k)
    char choice = 'n';      // User choice for manual/automatic centroid initialization

    // Read points from file
    DataPoint *points = readDataFromFile("kmeans-data.txt", &num_points); // Reading points from the file

    printf("Enter the number of clusters (k): ");
    if(scanf("%d", &num_clusters) != 1 || num_clusters < 1 || num_clusters > num_points) { // error handling for invalid k value
        printf("Invalid Input, Please enter a valid number of clusters between 1 and %d", num_points);
        free(points); // Free memory if reading is error
        exit(EXIT_FAILURE);
    }; // Input number of clusters

    // Allocate memory for clusters based on the number of clusters
    Cluster *clusters = allocateClusters(num_clusters);

    // Ask user whether to initialize centroids manually or automatically
    printf("Initialize centroid selection (y/n)?: ");
    scanf(" %c", &choice);

    if (choice == 'y') {
        // Manual centroid selection
        for (int i = 0; i < num_clusters; i++) {
            int selectIndex;
            printf("Select index for centroid %d (0-%d): ", i + 1, num_points - 1); // Ask for index of a data point to be a centroid
            scanf("%d", &selectIndex);
            if (selectIndex < 0 || selectIndex >= num_points) {
                printf("Error: Invalid index selected.\n"); // Error handling for invalid index
                free(points);
                free(clusters);
                exit(EXIT_FAILURE);
            }
            clusters[i].centroid = points[selectIndex]; // Assign user-selected point as the centroid
        }
    } else if (choice == 'n') {
        // Automatic centroid initialization
        initializeCentroids(points, num_points, clusters, num_clusters);
    } else {
        printf("Error: Invalid choice (y/n).\n"); // Error handling for invalid choice
        free(points);
        free(clusters);
        exit(EXIT_FAILURE);
    }

    // Perform K-Means clustering
    kmeansClustering(points, num_points, clusters, num_clusters);

    // Write results to output file
    writeMatrixToFile("kmeans-output.txt", points, num_points);

    // Free dynamically allocated memory
    free(points);
    free(clusters);

    return 0;
}
