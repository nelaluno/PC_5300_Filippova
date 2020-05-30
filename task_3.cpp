// Linear structure of processes: P1 -> P2 -> (P3, P4)

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	pid_t pid, pid1, pid2, pid3, pid_temp, pid_temp1, pid_temp2, pid_temp3; 
	pid_t ppid, ppid1, ppid2, ppid_temp, ppid_temp1, ppid_temp2, ppid_temp3;
	int status, status1, status2, status3;

	pid1 = fork();
	pid2 = fork();

	if ( pid1 > 0 and pid2 > 0) {     
	    printf("Parent start\n");
    	pid_temp = getpid();
    	ppid_temp = getppid();
    	printf(" Parent PID :: %i\n",pid_temp);
    	printf(" Parent PPID :: %i\n",ppid_temp);
    	sleep(5);
		return 0; // for stops Parent
	}
	else if (pid1 == 0 and pid2 > 0) {       
		// in Child1
		printf("\tChild1 start\n");
		printf("\t Child1 PID :: %i\n",getpid());
		printf("\t Child1 PPID :: %i\n",getppid());
		sleep(2);  
		return 0; // for stops Child1
	}
	else if (pid2 == 0 and pid1 > 0) {
		// in Child3
		printf("\tChild2 start\n");
		printf("\t Child2 PID :: %i\n",getpid());
		printf("\t Child2 PPID :: %i\n",getppid());
		pid3 = fork();
		if (pid3 < 0){
		    return 1;
		}
		else if (pid3 == 0){
		    // in Child3
				printf("\t\tChild3 start\n");
				printf("\t\t Child3 PID :: %i\n",getpid());
				printf("\t\t Child3 parent PID :: %i\n",getppid());
				return 0; // for stops Child3
		}
		sleep(2);  
		return 0; // for stops Child2
	}
	return 0;
}