#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    int pid, status;
    double sine(double);    
    double quad(unsigned int, double, double, double (*)(double));
    unsigned int n;
    double a, b, I;
    
    a = 0.0;
    b = 1.0;
    I = 0.0;
    n = 3200;
    
    switch(fork())
    {
        case -1:
            perror("<!> blad inicjalizacji potomka");
            exit(1);
            break;
        case 0:
            I = quad(n, a, b, sine);
            printf("[%d] wartosc calki \t%16.6f\n", (int)getpid(), I);
            exit(0);
        default:
            printf("[%d] wykonuje wazne rzeczy ... \n", (int) getpid());
            pid = (int)wait(&status);
            printf("[%d] zakonczyl z kodem %d \n", pid, status);
            printf("[%d] otrzymal wartosc \t %16.6f \n", (int)getpid(), I);
            break;
    } 

    return 0;
}

double sine(double x) 
{ return sin(2 * M_PI * x) * exp(-x); }

double quad(unsigned int n, double a, double b, double (*fun)(double))
{
    unsigned int k;
    double xk, sum;
    
    sum = fun(a) + fun(b);

    for (k = 1; k < n; k++) 
    {
        xk = a + (b - a) * k / n;
        sum += 2.0 * fun(xk);    
    }

    return ((b - a) / (2.0 * n) * sum);
}
