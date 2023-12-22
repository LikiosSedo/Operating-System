#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int numOfThreads = 10;
long long totalPoints = 100000000;	//the number of all points
long long totalPointsInCircle = 0;	//The numbe of all points in the circle
pthread_mutex_t mutex;

void *calc(void *arg);	//generate and calculate points
int getMicSec();

int main()
{
	int err;
	double pi = 0;
	long long add[numOfThreads];
	pthread_t thread[numOfThreads];
	
	for (int i = 0; i < numOfThreads; i++)	//create the threads
	{
		add[numOfThreads] = i;
		err = pthread_create (&thread[i], NULL, calc, &add[i]);	
		if (err != 0)	//error
		{
			printf ("Cannot create thread No.%d, please retry!\n", i);
			system ("pause");
			return -1;
		}
	}
	
	printf ("The number of points in the circle for EACH thread:\n");
	
	for (int j = 0; j < numOfThreads; j++)	//join the threads
		pthread_join (thread[j], NULL);
		
	pi = 4 * (double)totalPointsInCircle / totalPoints;
printf ("\n The approximate value of pi is: %lf\n", pi);
	printf ("\n\nThe whole number of points in the circle: %lld\n", totalPointsInCircle);
	printf ("The number of all points: %lld\n", totalPoints);
	
	pthread_mutex_destroy (&mutex);	//destroy the mutex lock
	return 0;	
}

void *calc(void *arg)
{
		long long pointsInThread = totalPoints / numOfThreads;	//number of points in one thread
		long long pointsInCircle = 0;	//number of points in the circle in this thread
		srand(getMicSec());
		for (long long i = 0; i < pointsInThread; i++)
		{
			
			double x = 1.0 * rand()/(double)RAND_MAX;
	        double y = 1.0 * rand()/(double)RAND_MAX;
	        if(x * x + y * y <= 1)	//the point is in the circle
	            pointsInCircle ++;
		}
		
		pthread_mutex_lock (&mutex);	//lock
		totalPointsInCircle += pointsInCircle;
		pthread_mutex_unlock (&mutex);	//unlock
		
		printf ("%lld  ", pointsInCircle);
		pthread_exit(0);		
}

int getMicSec()
{
	struct timeval tv;
	gettimeofday (&tv, NULL);
	
	return tv.tv_usec / 1000;
}

