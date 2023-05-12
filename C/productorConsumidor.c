#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 5

char buffer[BUFFER_SIZE];
int sig = 0;
pthread_mutex_t mutex;

void* produce(){
    while(1){
        while(sig == BUFFER_SIZE);
        //atómico
        pthread_mutex_lock(&mutex);
        printf("Depositado el caracter %c del buffer\n", buffer[sig++] = (rand() % 26) + 'a');
        pthread_mutex_unlock(&mutex);
        //atómico
        usleep((rand() % 500) * 1000);
    }
    pthread_exit(0);
}

void* consume(){
    while(1){
        while(!sig);
        //atómico
        pthread_mutex_lock(&mutex);
        printf("Recogido el caracter %c del buffer\n", buffer[--sig]);
        pthread_mutex_unlock(&mutex);
        //atómico
        usleep((rand() % 500) * 1000);
    }
    pthread_exit(0);
}

int main(){
    //inicializando rand
    srand(time(NULL));

    //inicializando mutex
    pthread_mutex_init(&mutex, NULL);

    //creacion de hilos y juego
    pthread_t h1, h2;
    pthread_create(&h1, NULL, produce, NULL);
    pthread_create(&h2, NULL, consume, NULL);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    return 0;
}
