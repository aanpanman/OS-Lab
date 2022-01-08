#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t write;
pthread_mutex_t mutex;
int count = 1;
int no_reader = 0;

void *writer(void *writer_no)
{   
    sem_wait(&write); 
    count = count+2;
    printf("Writer %d accessed count, changed to %d\n", (*((int *)writer_no)),  count);
    sem_post(&write);

}
void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    no_reader++;
    if(no_reader == 1) {
        sem_wait(&write); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    printf("Reader %d accessed count, read as %d\n", *((int *)rno), count);

    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    no_reader--;
    if(no_reader == 0) {
        sem_post(&write); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[2],write[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&write,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 2; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for(int i = 0; i < 2; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&write);

    return 0;
    
}