#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void prva_dretva() {
    sem_wait(&semaphore);
    printf("Kraj!\n");
}

void druga_dretva() {
    int i = 100;
    while(i--) {
        printf("%d\n", i);
    }
    sem_post(&semaphore);
}

int main() {
    pthread_t prva, druga;
    sem_init(&semaphore, 0, 0);
    if (pthread_create(&prva, NULL, prva_dretva, NULL)) {
        perror("Couldn't create thread!");
    }
    if (pthread_create(&druga, NULL, druga_dretva, NULL)) {
        perror("Couldn't create thread!");
    }
    perror("TU!");
    pthread_join(prva, NULL);
    pthread_join(druga, NULL);
    perror("TU!");
    int vrijednost;
    sem_getvalue(&semaphore, &vrijednost);
    printf("SEMAFOR: %d\n", vrijednost);
}