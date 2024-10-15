# K-Means Clustering in C

## Overview
### Description
This project implements the **K-Means Clustering** algorithm in C to group 2-dimensional data points into a specified number of clusters (`k`). It uses **Euclidean distance** to assign points to clusters and iteratively adjusts the centroids until convergence or a maximum number of iterations.

### Features
- Reads data points from a `.txt` file.
- User-defined number of clusters (`k`).
- Manual or automatic centroid initialization.
- Iterative assignment of points to nearest cluster.
- Output of clustering results to a file.
- Stops upon convergence or after 100 iterations.

## Files
### 1. `main.c`
Contains the main program logic:
- Reads data from a file.
- Runs the K-Means clustering algorithm.
- Writes the results to an output file (`kmeans-output.txt`).

### 2. `kmeans.c`
Implements the core algorithm:
- Memory allocation for data points and clusters.
- Distance calculation and centroid initialization.
- Point assignment and centroid updating.

## How to Compile and Run
### Prerequisites
- A C compiler (e.g., GCC).
- A data file in `.txt` format where each line contains space-separated `x` and `y` coordinates.

### Compilation
```bash
gcc main.c kmeans.c -o kmeans
```

### Running the Program
```bash
./kmeans
```

### Input Process
1. Enter the number of clusters (`k`).
2. Choose centroid initialization:
   - `y`: Manual (specify indices of points).
   - `n`: Automatic (random selection of centroids).

### Example Data File (`kmeans-data.txt`)
```
2.3 4.1
5.0 1.9
3.7 2.8
8.6 7.2
...
```

## Output
### Output File (`kmeans-output.txt`)
The results are saved in a file with the following format:
```
x y cluster
2.3 4.1 0
5.0 1.9 1
3.7 2.8 0
8.6 7.2 1
...
```

### Confirmation Message
After successful completion, the program prints:
```
Results Updated Successfully in 'kmeans-output.txt'!
```

## Error Handling
- Invalid file extension.
- Non-numeric data in input file.
- Invalid number of clusters (`k`).
- Incorrect centroid index selection in manual initialization.

## Memory Management
All dynamically allocated memory for data points and clusters is freed at the end of the program to prevent memory leaks.

## Customization
You can change the **maximum number of iterations** by modifying the `MAX_ITERATIONS` constant in both `main.c` and `kmeans.c`.

## Author
Developed by Patteera Lerdtada.
