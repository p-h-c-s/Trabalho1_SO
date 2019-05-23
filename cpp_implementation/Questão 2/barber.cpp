#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

sem_t mutex;
sem_t sem_clientes;
sem_t sem_barbeiros;
int MAX_CLIENTES=3;

int num_clientes =5;
int num_threads_clientes = num_clientes;
int num_barbeiros=1;

int fila = 0;

void *barbeiro(void *arg){
    int i =  *((int*) arg);
    while (1){
        cout<< "Babeiro "<<i<<" esperando cliente\n"; 
        sem_wait(&sem_clientes);
        // sem_wait(&mutex);
        fila--; //Retira um cliente da fila. Necessario estar dentro de uma area critica pois se nao podemos ter escrita suja
        cout<< "Babeiro "<<i<<" cortando cabelo de algum cliente.\n";
        sleep(15);
        cout<< "Babeiro "<<i<<" cortou cabelo.\n";
        // sem_post(&mutex);
        sem_post(&sem_barbeiros); //Libera um barbeiro.
    }
}

void *cliente(void *arg){
    int i = *((int*)arg);
    // sem_wait(&mutex);
    if(fila < MAX_CLIENTES){
        cout<< "Cliente "<<i<<" está na fila.\n";
        fila++; //Adiciona um cliente na fila
        sem_post(&sem_clientes); //Aumenta o valor do semaforo dos clientes
        sem_post(&mutex);
        sem_wait(&sem_barbeiros); //Diminui o valor do semaforo dos barbeiros
        cout << "Cliente "<<i<<" cortou o cabelo.\n";
    }
    else{
        cout<<"Cliente "<<i<<" foi embora pois barbearia estava lotada.\n";
        // sem_post(&mutex);
    }
}

int main(){
    sem_init(&mutex,0,1);
    sem_init(&sem_clientes,0,0);
    sem_init(&sem_barbeiros,0,0);
    int n;
    pthread_t threads[num_barbeiros+num_clientes];

    for (int i = 0; i < num_barbeiros; i++){
        pthread_create(&threads[i],NULL,barbeiro,&i);
        sleep(0.01); //Tempo infimo apenas para dar tempo de atualizar o i.
        
    }

    sleep(3);

    int copia;
    for (int i = num_barbeiros; i < num_barbeiros+num_threads_clientes; i++){
        copia = i-num_barbeiros;
        pthread_create(&threads[i],NULL,cliente,&copia);
        sleep(1);
    }
    
    for (int i = 0; i < num_barbeiros+num_barbeiros; i++){
        pthread_join(threads[i],NULL);
    }
    return 0;
}