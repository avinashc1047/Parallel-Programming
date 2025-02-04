#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

int n;              // Number of trapezoids
double a, b;        // Left and right endpoints
double h;           // Height of trapezoids
int num_threads;    // Number of threads
double total_sum = 0.0;
pthread_mutex_t mutex;
double start,finish;
// Function to compute f(x)
double f(double x) {
    return x * x; 
}

// Thread function to compute partial sum over a given thread
void* compute_trap(void* arg) {
    long my_rank = (long) arg;
    double local_sum = 0.0;

    int local_n = n / num_threads; // num of trapezoids per thread
    double local_a = a + my_rank * local_n * h; // Local start
    double local_b = local_a + local_n * h; // Local end

    local_sum = (f(local_a) + f(local_b)) / 2.0;
    double x = local_a + h;
    for (int k = 1; k < local_n; k++) {
        local_sum += f(x);
        x += h;
    }
    local_sum *= h;

    // update global sum
    pthread_mutex_lock(&mutex);
    total_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;

    // get args
    printf("Enter a, b, n, and thread count\n");
    scanf("%lf %lf %d %d", &a, &b, &n, &num_threads);

    // allocate memory
    h = (b-a)/n;
    thread_handles = malloc(num_threads * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    
    GET_TIME(start);

    //create threads
    for (thread = 0; thread < num_threads; thread++)
        pthread_create(&thread_handles[thread], NULL, compute_trap, (void*) thread);

    for (thread = 0; thread < num_threads; thread++)
        pthread_join(thread_handles[thread], NULL);
    
    GET_TIME(finish);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.15f\n", a, b, total_sum);
    printf("Calculations took %f seconds\n", finish - start);
    
    // close threads
    pthread_mutex_destroy(&mutex);
    free(thread_handles); // free memory
    return 0;
}
