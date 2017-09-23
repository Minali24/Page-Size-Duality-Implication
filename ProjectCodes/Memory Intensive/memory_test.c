#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cycle.h"
//#define SIZE 10*47185920

int main(){

	unsigned long long int SIZE = 2ul << 30, count=0;
	long long int read_request=SIZE;
	char *a = (char *)malloc(SIZE*sizeof(char));
//	char *data = (char *)mmap(NULL, 2ul << 30,
  //                        PROT_READ | PROT_WRITE, FLAGS,
    //                      -1, 0);
	time_t t1;
	clock_t t;
	srand((unsigned) time(&t1));

	unsigned long long int temp,index,i=0;
	double time_taken=0;
	memset(a, 0, SIZE);
	
	int percentage_random=0;
	int percentage_sequential=100;

	int j;	
	printf("Enter the percentage random(-1 for best scenario)\n");
	scanf("%d",&percentage_random);
	if(percentage_random==-1){
	// best scenario for huge page		
		ticks begin = getticks();
		t = clock();
		for(j=0;j<4096;j++){
			for(i=0;i<read_request/10;i+=4096){
				index=rand()%SIZE;
				a[i%SIZE]=0;
				count++;
			}
			for(i=0;i<read_request/10;i+=4096){
				index=rand()%SIZE;
				temp = a[i%SIZE];
				count++;
			}
		}
		t= clock()-t;
		ticks end = getticks();
		printf("Count : %llu\n",count);
		printf("%g\n", elapsed(end, begin));
	}
	else{
		if(percentage_random > 100)
			percentage_random=100;
		else if(percentage_random < 0)
			percentage_random=0;

		percentage_sequential=100 - percentage_random;
		long long int seq_read_request=read_request/10,random_read_request=read_request/10;
		seq_read_request*=(percentage_sequential/100.0);
		random_read_request*=(percentage_random/100.0);
		long long int seq_write=seq_read_request,random_write=random_read_request;
		ticks begin = getticks();
		t = clock();
		for(i=0;i<seq_write;i++){
			index=rand()%SIZE;
			a[i]=0;
			count++;
		}
		for(i=0;i<random_write;i++){
			index=rand()%SIZE;
			a[index]=0;
			count++;
		}
		for(i=0;i<seq_read_request;i++){
			index=rand()%SIZE;
			temp = a[i];
			count++;
		}
		for(i=0;i<random_read_request;i++){
			index=rand()%SIZE;
			temp=a[index];
			count++;
		}

		t= clock()-t;
		ticks end = getticks();
		printf("Count : %llu\n",count);
		printf("%g\n", elapsed(end, begin));
	}
	time_taken+=((double)t)/CLOCKS_PER_SEC;
		
	printf("Total time Taken %f\n",time_taken);
	printf("Enter any character to exit\n");
	char c;
	scanf(" %c",&c);
//	free(a);
	return 0;
}
