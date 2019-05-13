#include<iostream>
#include<vector>
#include"semaphore.h"
#include"pthread.h"
#include <unistd.h>
using namespace std;

int dinheiro=0;
sem_t semaforo; //Semaforo unico pois nao temos preferencia entre Leitores e Escritores, pode gerar LEITURA SUJA!

void * deposito(void *i){ //Escritora
    sem_wait(&semaforo);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do deposito:" << dinheiro<< endl;
    a += 10;
    sleep(0.2);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do deposito:" << dinheiro<< endl;
    sem_post(&semaforo);
}

void * saque(void *i){ //Escritora
    sem_wait(&semaforo);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do saque:" << dinheiro<< endl;
    a -=5;
    sleep(0.2);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do saque:" << dinheiro<< endl;
    sem_post(&semaforo);
}

void * consulta(void *i){ //Leitora
    sem_wait(&semaforo);
    // sleep(2);
    cout << "(THREAD LEITORA) Valor na conta:"<< dinheiro << endl;
    sem_post(&semaforo);
}

int main(){
    sem_init(&semaforo,0,1);
    pthread_t threads[3];
    int n;
    pthread_create(&threads[0],NULL,deposito,(void *) 0);
    pthread_create(&threads[1],NULL,saque,(void *) 0);
    pthread_create(&threads[2],NULL,consulta,(void *) 0);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);
    
    cout << "\nVALOR FINAL:"<<dinheiro<<endl;

}