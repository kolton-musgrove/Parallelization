#include <stdio.h>
#include <time.h>

#define max 40

void laplace();

void main()
{
    int msec = 0, trigger = 1;
    clock_t before = clock();

    do
    {
        laplace();
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
    } while (msec < trigger);

    printf("Time taken %d seconds %d milliseconds.\n", msec / 1000, msec % 1000);
}

void laplace()
{
    double x, p[max][max];
    int i, j, iter, y;

    FILE *output;
    output = fopen("laplace.data", "w");

    // clear the array
    for (i = 0; i < max; i++)
    {
        for (j = 0; j < max; j++)
        {
            p[i][j] = 0;
        }
    }

    // setting p[i][0] to 100
    for (i = 0; i < max; i++)
    {
        p[i][0] = 100;
    }

    // itterating in the x and y directions
    for (iter = 0; iter < 1000; iter++)
    {
        for (i = 0; i < (max - 1); i++)
        {
            for (j = 0; j < (max - 1); j++)
            {
                p[i][j] = 0.25 * (p[i + 1][j] + p[i - 1][j] + p[i][j + 1] + p[i][j - 1]);
            }
        }
    }

    // write data to file
    for (i = 0; i < max; i++)
    {
        for (j = 0; j < max; j++)
        {
            fprintf(output, "%f\n", p[i][j]);
        }
        fprintf(output, "\n");
    }

    // close program
    printf("data stored in laplace.dat\n");
    fclose(output);
}