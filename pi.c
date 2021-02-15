// pi.c: Serial Calculation of pi by Monte-Carlo Integration

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <time.h>

#define max 100000 // number of stones to be thrown
#define seed 68222 // seed for number generator
#define USE_MPI

void MontePi();
void MPIMontePi(int argc, char *argv[]);

void main(int argc, char *argv[])
{
    int msec = 0, trigger = 1;
    clock_t before = clock();

    do // timer function
    {
        MontePi();
        // MPIMontePi(argc, argv);
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
    } while (msec < trigger);

    printf("Time taken %d seconds %d milliseconds.\n", msec / 1000, msec % 1000);
}

void MontePi() // 39ms for 100,000 stones; pi = 3.147080
{
    int i, pi = 0;
    double x, y, area;

    FILE *output;
    output = fopen("pond.dat", "w");
    srand48(seed);
    for (i = 1; i <= max; i++)
    {
        x = drand48() * 2 - 1;
        y = drand48() * 2 - 1;
        if ((x * x + y * y) < 1)
            pi++;
        area = 4 * (double)pi / i;
        fprintf(output, "%i\t%f\n", i, area);
    }
    printf("data stored in pond.dat\n");
    fclose(output);
}

void MPIMontePi(int argc, char *argv[]) // 22ms for 100,000 stones; pi = 3.15936
{
    int niter = 0;
    double x, y;
    int i, j, count = 0, mycount; // # of points in the 1st quadrant of the unit circle
    double z;
    double pi;
    int ierr, procid, numprocs;
    MPI_Status status;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    sscanf(argv[1], "%d", &niter); // 1st argument is the number of iterations

    // Initilizing Random Numbers
    mycount = 0;
    for (i = 0; i < niter; i++)
    {
        x = drand48() * 2 - 1;
        y = drand48() * 2 - 1;
        z = x * x + y * y;
        if (z <= 1)
            mycount++;
    }
    if (procid == 0) // if this is the master node
    {
        count = mycount;
        for (int proc = 1; proc < numprocs; proc++)
        {
            MPI_Recv(&mycount, 1, MPI_REAL, proc, 123, MPI_COMM_WORLD, &status);
            count += mycount;
        }
        pi = (double)count / (niter * numprocs) * 4;
        printf("\n # of trials= %d, estimate of pi is %g \n", niter * numprocs, pi);
    }
    else
    { // for all slave nodes
        printf("Processor %d sending results= %d to master process\n", procid, mycount);
        MPI_Send(&mycount, 1, MPI_REAL, 0, 123, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}