#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

void ini();
void print();
void *request(void *arg);
int safe();

int num[3] = {0, 0, 0};
pthread_mutex_t mutex;
pthread_t customer[NUMBER_OF_CUSTOMERS];

int main (int argc, char* argv[])
{
	if (argc != 4)
	{
		fprintf (stderr, "error!\n");
		return -1;
	}
	
	for (int i = 0; i < 3; i++) num[i] = atoi(argv[i + 1]);
	
	pthread_mutex_init (&mutex, NULL);
	srand((unsigned)time(NULL));
	ini();
	
	if (!safe())	
	{
		printf ("unsafe\n");
		return 0;
	}
	//create threads
	for (int j = 0; j < NUMBER_OF_CUSTOMERS; j++)	
	{
		pthread_t cust;
		customer[j] = cust;
		pthread_attr_t attr;
		pthread_attr_init (&attr);
		pthread_create (&customer, &attr, request, (void*)j);
	}
	
	for (int k = 0; k < NUMBER_OF_CUSTOMERS; k++)
	{
		pthread_join (customer[k], NULL);	//join the threads
	}
	
	return 0;	
}

void ini()
{
	for (int i = 0; i < 3; i++)
		available[i] = num[i];
		
	pthread_mutex_init (&mutex, NULL);
	
	for (int j = 0; j < NUMBER_OF_CUSTOMERS; j++)
		for (int k = 0; k < NUMBER_OF_RESOURCES; k++)
		{
			maximum[j][k] = (int)(rand() / (RAND_MAX + 1.0) * (available[k] + 1));
			allocation[j][k] = 0;
			need[j][k] = maximum[j][k] - allocation[j][k];
		}
		
	print();
}

void print()
{
	int i, j;
	
	printf ("Available: \n");
	for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		printf ("%d  ", available[i]);
		
	printf ("\nMaximum: \n");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
			printf ("%d  ", maximum[i][j]);
			
	printf ("\nAllocation: \n");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
			printf ("%d  ", allocation[i][j]);
			
	printf ("\nNeed: \n");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
			printf ("%d  ", need[i][j]);
}

int safe()	//return 1 for safe and 0 for unsafe
{
	int work[NUMBER_OF_RESOURCES];
	int finish[NUMBER_OF_CUSTOMERS];
	
	for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
		work[i] = available[i];
		
	for (int j = 0; j < NUMBER_OF_CUSTOMERS; j++)
		finish[j] = 0;
		
	while (1)
	{
		int flag = 1;
		for (int k = 0; k < NUMBER_OF_CUSTOMERS; k++)
		{
			int num1 = 1;
			for (int m = 0; m < 3; m++)
				if (need[k][m] > work[m])
					num1 = 0;
			
			if (finish[k] == 0 && num1)
			{
				for (int n = 0; n < 3; n++)
					work[n] = allocation[k][n];
				
				finish[k] = 1;
				flag = 0;
			}
		}
		
		if (flag == 1)
			break;
	}
	
	int flag1 = 1;
	for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		if (finish[i] != 0)	//unsafe
			flag1 = 0;
			
	if (flag1 == 1)
		return 1;
	else
		return 0;
}

void *request(void *arg)
{
	int num1 = (int)arg;
	while(1)
	{
		int req[NUMBER_OF_RESOURCES];
		pthread_mutex_lock(&mutex);
		
		for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
			req[i] = (int)(rand() / (RAND_MAX + 1.0) * (need[num1][i] + 1));
			
		printf("\nThread%d  Request: %d %d %d", num1 + 1, req[0], req[1], req[2]);
		if (req[0] <= available[0] && req[1] <= available[1] && req[2] <= available[2])
		{
			for (int j = 0; j < 3; j++)
			{
				available[j] -= req[j];
				allocation[num1][j] += req[j];
				need[num1][j] -= req[j];
			}
			
			if (!safe())	//unsafe
			{
				for (int k = 0; k < 3; k++)
				{
					available[k] += req[k];
					allocation[num1][k] -= req[k];
					need[num1][k] += req[k];
					
				}
				
				printf ("  UNSAFE  ");
				printf("Available: %d %d %d \n", available[0], available[1], available[2]);
			}
			
			else
				printf ("  SAFE  Available: %d %d %d \n", available[0], available[1], available[2]);
		}
		
		else
			printf ("  No Enough Resources!  Available: %d %d %d \n", available[0], available[1], available[2]);

		pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}
