
/* Use MonteCarlo ways to calculate π */

#include <stdio.h>

#include <string.h>

#include <pthread.h>

#include <math.h>

#include <stdlib.h>

 

int i  = 0;

int amtWanted = 0;

int totalPts  = 0;

 

void* count(void* X)

{

    /* Initializing */

    for(i=0; i< amtWanted; i++)

    {

        double X = (double)rand() / RAND_MAX;

        double  Y = (double)rand() / RAND_MAX;
 
        

        if(((X * X) + (Y * Y)) <= 1)

        {

            totalPts++;

        }

    }

    return NULL;

}

 

int main()

{

    printf("\n\nWelcome to Threaded Monte Carlo, by liusendong\n\n");

    srand(time(NULL));

    pthread_t thread;

    do

    {

       printf("How many points do you want to genernate? \n");

        scanf("%d", &amtWanted);

    }while(amtWanted<= 0);

    

    pthread_create(&thread,NULL, &count, NULL);

    pthread_join(thread, NULL);

    

    double points = 4.0 * totalPts;

    double pi = points / amtWanted;

    printf("The approximate value of π is (%d) is: %f \n", amtWanted, pi);

    return 0;

}