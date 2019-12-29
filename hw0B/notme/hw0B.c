#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h> 
#include <assert.h>

int main(int argc, char **argv) {
	FILE *fd;
	int tempture=40,cputemp = 0;
	fd=fopen("/sys/class/hwmon/hwmon5/temp2_input","r");

	if (argc == 2) 
		tempture=atoi(argv[1]);

	fscanf(fd,"%d",&cputemp);
	printf("target = %d\n", tempture);
	tempture = tempture * 1000;

	for(int i=0;cputemp > tempture;i++) {
		printf("%d sec %d℃\n", i, cputemp/1000);
		sleep(1);
	}

	printf("temp = %d℃, \n", cputemp/1000);

	return 0;
}
