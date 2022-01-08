//Avantika Suryawanshi, 20BCE2051
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>

#define N 5 //variable to store size of the buffer

sem_t empty;//inintialzing semaphores empty and full
sem_t full;
int in = 0, out = 0;
int buffer[N];//buffer array to store the items
pthread_mutex_t mutex;//mutex semaphore

void *producer(void *producer_no) {   //function for producer process
    int item;
    for(int i = 0; i < N; i++) 
    {
        item = i+1; //value of item to be produced
        sem_wait(&empty);//wait operation on semaphore empty
        pthread_mutex_lock(&mutex);//locking the mutex semaphore
        buffer[in] = item;//inserting the produced item in the buffer
        printf("Producer %d inserts item %d.\n", *((int *)producer_no), buffer[in]);
        in = (in+1)%N; 
        pthread_mutex_unlock(&mutex);//unlocking the mutex semaphore
        sem_post(&full);//signal operation on semaphore full to now allow consumer process to work
    }
}

void *consumer(void *consumer_no) {   //function for consumer process
    for(int i = 0; i < N; i++) 
    {
        sem_wait(&full);//wait operation on semaphore full
        pthread_mutex_lock(&mutex);//locking the mutex semaphore
        int item = buffer[out];//removing the consumed item from the buffer
        printf("Consumer %d removes item %d.\n", *((int *)consumer_no), item);
        out = (out+1)%N; 
        pthread_mutex_unlock(&mutex);//unlocking the mutex sempahore
        sem_post(&empty);//signal operation on semaphore empty to now allow producer process to work
    }
}

int main() { 
    pthread_t pro[N],con[N];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    int a[5] = {1,2,3,4,5};

    pthread_create(&pro[0], NULL, (void *)producer, (void *)&a[0]);//creating 1 producer
    pthread_create(&con[0], NULL, (void *)consumer, (void *)&a[0]);//creating 1 comsumers

    pthread_join(pro[0], NULL);//join operation for letting all the producer processes to be completed
    pthread_join(con[0], NULL);//join operation for letting all the consumer processes to be completed 

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}