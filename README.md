# K-Means Clustering in C

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

# Makefile for K-Means Clustering
### Overview
This Makefile is designed to automate the compilation, cleanup, memory leak checking, and debugging processes for the K-Means Clustering program written in C. It compiles source files, links them into an executable, and provides additional targets for memory checking and debugging.

### Targets
all: The default target to compile the program.
clean: Removes the object files and the executable.
valgrind: Runs the program with Valgrind to check for memory leaks.
debug: Runs the program with GDB for debugging.
test: Placeholder for running tests.
help: Displays help instructions for using the Makefile.

### Variables
CC: Specifies the C compiler (default: gcc).
CFLAGS: Compiler flags including debugging (-g), warnings (-Wall, -Wextra), C standard (-std=c99), and math library linkage (-lm).
SRCS: Lists the source files (main.c and kmeans.c).
OBJS: Generates the corresponding object files (.o) from the source files.
EXEC: Defines the name of the executable (kmeans).

## Usage

### Compile the Program
To compile the program and create the kmeans executable:
``` 
make
```
### Clean Up
To remove the compiled object files and executable:
  ``` 
  make clean
 ```
### Run Valgrind for Memory Leak Detection
To check for memory leaks using Valgrind:
   ```
   make valgrind
 ```
### Debug with GDB
To run the executable in GDB for debugging:
 ``` 
 make debug
 ```
### View Help
To display help information:
 ``` 
 make help
 ```
   
### Notes
You can modify the CFLAGS or SRCS variables if you wish to change compiler options or add more source files.
The test target is a placeholder, and you can customize it with your own test cases if needed.
### Phony Targets
The all, clean, valgrind, debug, test, and help targets are marked as phony, meaning they are not associated with actual files.

## Author
Developed by Patteera Lerdtada, Xuning Zhang, Thee Kullatee
