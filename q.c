
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>


#define MAX_RESOURCES 5


int available_resources = MAX_RESOURCES;
int times = 5;
pthread_mutex_t mutex;
sem_t semaphore; 

/* decrease available_resources by count resources
* return 0 if sufficient resources available,
* otherwise return -1 */
int decrease_count(int count) {
if (available_resources < count) {
    return -1;
} else {
    available_resources -= count;
    printf("Locked %i resources, now available: %i\n" , count , available_resources);
    return 0;
}
}


/* increase available resources by count */
int increase_count(int count) {
if (count + available_resources > 5) {
    return -1;
} else {
    available_resources += count;
    printf("Freed %i resources, now available: %i\n" , count , available_resources);
    return 0;
}
}


void *runTimes(void *null) {
int i = 0 , result;
while (i < times) {
    result = -1;
    while (result < 0) {result = decrease_count(1);}
    result = -1;
    while (result < 0) {result = increase_count(1);}
    i += 1;
    printf("Count; %i\n",i );
}

return NULL;
}

 int main(int argc, char *argv[])
 {
pthread_t thread1 , thread0;
pthread_t threads [2];

decrease_count(2);

 pthread_create(&threads[0], NULL, runTimes, NULL);
 pthread_create(&threads[1], NULL, runTimes, NULL);

 int i = 0;
 while( i < 2) {
    pthread_join(threads[i], NULL);
    i++;
}

pthread_exit(NULL);


printf("Currently available resources (should be 3): %i\n" , available_resources);

return 0;
}

