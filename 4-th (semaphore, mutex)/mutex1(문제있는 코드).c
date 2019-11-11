#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int gValue = 0;
pthread_t gTh[2];

void *thread(void *id)
{
	int tid = (int)(void *)id;
	int i;
	int t;

	printf("Thread%d started...\n", tid);

	for (i=0; i<100; i++) {
		t = gValue;
		usleep((useconds_t)(rand()%1000));
		gValue=t+1;
		usleep((useconds_t)(rand()%1000));
	}
}

int main(int argc, char **argv)
{
	int i;
	int tid[2];
	void *ret;

	for (i=0;i<2;i++) {
		tid[i]=i+1;
		pthread_create(&gTh[i], NULL, thread, (void *)i);
	}

	for (i=0;i<2;i++) {
		pthread_join(gTh[i], &ret);
	}
	printf("-----------------------------------\n");
	printf("gValue = %d\n", gValue);
	
	return 0;
}
