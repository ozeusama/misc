#include <windows.h>
#include <math.h>
#include <stdio.h>

// in ms
double winclock()
{
    LARGE_INTEGER count, freq;
    QueryPerformanceCounter(&count);
    QueryPerformanceFrequency(&freq);
    return ((double)count.QuadPart / (double)freq.QuadPart)*1000.0;
}

int main()
{
    double t1 = winclock();

    double sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 1; i < 14458226; i++) {
        sum += log((double)i);
    }
    printf("%f\n", sum);

    double t2 = winclock();

    printf("%f\n", t2 - t1);

    return 0;
}
