# Parallel-Programming
CISC-372 projects in C++ and C using OpenMP, PThreads, and MPI parallel libraries. Fractal Image creation using CUDA and Nvidia GPUs. Some Projects used the *Darwin HPC CLuster* which is the High Performance Computer (HPC) at the University of Delaware, where you can create compute clusters with specific hardware configurations.


## Assignment 1
### Matrix Transposition in C: Two Dynamic Memory Allocation Methods
This assignment involves writing a serial C program to create and transpose a 2D matrix using two different dynamic memory allocation methods. The program demonstrates memory management, matrix manipulation, and proper deallocation to avoid memory leaks.

- Demonstrates proficiency in dynamic memory allocation using malloc and free.
- Implements two distinct matrix storage methods, showcasing flexibility in C programming.
- Includes memory leak detection using valgrind for robust debugging.

*Technologies Used : C, GCC Compiler, Valgrind*

## Assignment 2
### Parallel Monte Carlo Computation of Pi Using MPI
This assignment involves parallelizing the Monte Carlo algorithm for computing Pi using MPI (Message Passing Interface). The Monte Carlo method approximates Pi by randomly sampling points within a unit square and counting how many fall inside a unit circle. The parallel implementation is achieved using both point-to-point communication and collective communication in MPI.

- Demonstrates parallel programming concepts using MPI.
- Implements two communication strategies: point-to-point and collective communication.
- Includes performance analysis to evaluate scalability and efficiency.

*Technologies Used: C, MPI (Message Passing Interface), Linux, Valgrind*

## Assignment 3
### Shared Memory Parallelization with Pthreads and OpenMP
This assignment focuses on parallel programming for shared memory systems using Pthreads and OpenMP. First, parallelizing the trapezoidal rule for numerical integration using Pthreads. Then, parallelizing a histogram equalization algorithm for grayscale images using OpenMP.

- Demonstrates shared memory parallelism using two popular frameworks: Pthreads and OpenMP.
- Implements parallel algorithms for numerical integration and image processing.
- Includes hands-on experience with high-performance computing (HPC) clusters (DARWIN).

*Technologies Used: C, Pthreads, OpenMP, Darwin HPC Cluster, Linux*

## Assignment 4
### Parallelizing Fractal Movie Generation with CUDA
This assignment involves parallelizing a serial program that generates a sequence of fractal images at increasing zoom levels using CUDA. The goal is to compute these images efficiently on a GPU and combine them into a movie. The program visualizes the Mandelbrot set, and the workload is highly parallelizable, making it ideal for GPU acceleration.

- Demonstrates GPU programming using CUDA for computationally intensive tasks.
- Visualizes the Mandelbrot set, showcasing load imbalance and parallel workload distribution.
- Includes hands-on experience with high-performance computing (HPC) clusters (DARWIN).

*Technologies Used: C, C++, CUDA, Nvidia GPU, nvcc compiler, Darwin HPC Cluster, ImageMagick*
