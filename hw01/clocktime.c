#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

int timespec2str(char *buf ,uint len,struct timespec *ts){
	int ret;
	struct tm t;
	
