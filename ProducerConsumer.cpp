//Avantika Suryawanshi, 20BCE2051
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t write; //initializing semaphore write and mutex 
pthread_mutex_t mutex;
int count = 1;
int no_reader = 0;

void *writer(void *writer_no)
{   
    sem_wait(&write); //wait operation on write semaphore 
    count = count+2; //writer process increases the count by 2
    printf("Writer %d accessed count, changed to %d\n", (*((int *)writer_no)),  count);
    sem_post(&write); //signal operation on write semaphore

}
void *reader(void *reader_no)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex); //locking the mutex
    no_reader++; //increasing the no.of readers
    if(no_reader == 1) {
        sem_wait(&write); //wait operation to block the write process
    }
    pthread_mutex_unlock(&mutex); //unlocking the mutex to access count variable
    printf("Reader %d accessed count, read as %d\n", *((int *)reader_no), count);
    pthread_mutex_lock(&mutex); //locking the mutex
    no_reader--; // decreasing the no.of reader
    if(no_reader == 0) {
        sem_post(&write); //signal operation to give access to writer process
    }
    pthread_mutex_unlock(&mutex);//unlocking mutex
}

int main()
{ 
    pthread_t read[4],wrt[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&write,0,1);

    int a[4] = {1,2,3,4}; //for numbering the producer and consumer
    
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]); //creating 2 reader processes
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&wrt[i], NULL, (void *)writer, (void *)&a[i]); //creating 2 writer porcesses
    }
    for (int i = 2; i < 4; i++)
    {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]); //creating 2 more reader processes
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join(read[i], NULL); //join operation for letting all the reader processes to be completed
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(wrt[i], NULL); //join operation for letting all the reader processes to be completed
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&write);

    return 0;
    
}