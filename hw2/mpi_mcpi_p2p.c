#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../hw2/timer.h"

/*** TODO 1: include the required MPI header file ***/
#include <mpi.h> 

/* struct to store 2D point coordinates 
 */
typedef struct _point {
    double x;
    double y;
} Point;

/* random_point generates coordinates of a random point within the square
 * Output: Point - random point 
 */
Point random_point() {
    Point p;
    p.x = (double)rand()/(double)RAND_MAX;
    p.y = (double)rand()/(double)RAND_MAX;
    return p;
}

/* is_within_circle cheks whether a point falls within the circle 
 * Input: Point - the point to check
 * Output: unsigned short int - 1 if point is within circle, 0 otherwise 
 */
unsigned short int is_within_circle(Point p) {
    double r2 = p.x*p.x + p.y*p.y;
    if (r2 <= 1.0) {
        return 1;
    } else {
        return 0;
    }
}

/* compute_pi calculates the approximate value of pi 
 * using the Monte Carlo method 
 * Input: int - number of points to generate randomly
 * Output: double - the approximate value of pi
 */
double serial_pi(int n) {
    int count=0;
    for (int i=0; i<n; i++) {
        /* generate to random numbers */
        Point p = random_point();
        if (is_within_circle(p)) count++;    
    }

    return  4.0*count/n;
}

double parallel_pi(int n, int comm_sz, int my_rank) {
    int local_n=n, local_count=0, count=0;
    
    /*** TODO 2: add code to determine the number of points that are handled by each process ***/
    long local_n = n/ comm_sz;


    for (int i=0; i<local_n; i++) {
        /* generate to random numbers */
        Point p = random_point();
        if (is_within_circle(p))  local_count++;
    }
    
    /*** TODO 3: add code that correctly determines the overall count ***/
    if (my_rank != 0) {
        // Send the local count to process 0
        MPI_Send(&local_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // Rank 0 receives counts from all other processes
        count = local_count;
        for (int i = 1; i < comm_sz; i++) {
            int received_count;
            MPI_Recv(&received_count, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += received_count;
        }
    }

    // Rank 0 computes pi
    if (my_rank == 0) {
        return 4.0 * count / n;
    } else {
        return 0.0;  // Other ranks don't calculate pi
    }
}

/* main reads the command line argument and outputs the approximate value of pi 
 */
int main(int argc, char *argv[]) {
    long n;
    double pi, error;
    double start, finish, elapsed_serial, elapsed_parallel;

	/*** TODO 4: add code to set up the MPI execution environment ***/
    MPI_Init(&argc, &argv);


    int comm_sz=1, my_rank=0;
    /*** TODO 5: add code to set comm_sz and my_rank to the appropriate values ***/
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    if (my_rank == 0) {
        /* Check command line arguments for correctness and read the parameters from argv */
        if (argc != 2) {
            printf("Usage: pi <npoints>\n");
            exit(-1);
        } else {
            n = atoi(argv[1]);
        }
    }
    /*** TODO 6: Add code that ensures that every process has the input value for n */
    MPI_Bcast(&n, 1, MPI_LONG, 0, MPI_COMM_WORLD);


    /* set a random seed */
    srand(1);

    /* compute approximate value of pi and calculate difference to real value */
    /* Serial execution for comparison */
    if (my_rank == 0) {
        GET_TIME(start);
        pi = serial_pi(n);
        error = pi - 4.0 * atan(1.0);
        GET_TIME(finish);
        elapsed_serial = finish - start;
    }

	/*** TODO 7: add code to synchronize the processes ***/
    MPI_Barrier(MPI_COMM_WORLD);


    GET_TIME(start);
    pi = parallel_pi(n, comm_sz, my_rank);
    error = pi - 4.0*atan(1);
    GET_TIME(finish);
    elapsed_parallel = finish - start;

    if (my_rank == 0) {
        /* Print the results to stout */
        printf("The approximate value of pi is pi=%f (error=%f)\n", pi, error);

        /* Print performance measurements */
        printf("Serial runtime: %f s\n", elapsed_serial);
        printf("Parallel runtime using %d processes: %f s\n", comm_sz, elapsed_parallel);
        printf("Speedup: %.3f\n", elapsed_serial/elapsed_parallel);
    }

	/*** TODO 8: don't forget to terminate the MPI execution environment */
    MPI_Finalize();


    return 0;
}

/* you can compile and run the program on cisc372.cis.udel.edu using the following commands:
 *   mpicc mpi_mcpi.c -lm -o pi
 *   srun -n <numprocs> ./pi
 */