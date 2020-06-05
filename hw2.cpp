#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

double f(double x){
    return 1/(1+x*x);
}

double sum(int a, int b, int n){
    double r = 0;
    for(int i = a; i<b; i++)
        r += f(i/(double)n);
    return r;
}

int main(){
    int n, k;
    printf("n=");
    scanf("%d", &n); //number of terms
    printf("k=");
    scanf("%d", &k); // number of processes
    
    int step = n/k;

    
    int shm_id;
    int fds[2];
    pipe(fds);
    pid_t pid;
    
    for(int i=0;i<k;i++)
    { 
        if(fork() == 0) 
        { 
            int start;
            if (i==0)
                start = 1;
            else
                start = i*step;
            double r = sum(start, (i+1)*step, n); 
            write(fds[1], &r, sizeof(double));
            // printf("%d, %d: %g\n", i, getpid(), r);
            return 0;
        } 
    } 
    
    for(int i=0;i<k;i++)
        wait(NULL);
        
    double r, s=0;
    for(int i=0;i<k;i++)
    {
        read(fds[0], &r, sizeof(double));
        //printf("%d: %g\n", getpid(), r);
        s += r;
    }
    close(fds[1]);
    printf("pi = %g\n", 2*(f(0.0)+f(1.0)+2*(s))/n);
    return 0;
}