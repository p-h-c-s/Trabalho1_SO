#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>
using namespace std;

int dinheiro=0;
sem_t semaforo;

void * deposito(void *i){
    int a =dinheiro;
    cout << "Antes do deposito:" << dinheiro<< endl;
    sleep(0.5);
    a += 10;
    dinheiro = a;
    cout << "Depois do deposito:" << dinheiro<< endl;
}

void * saque(void *i){
    int a =dinheiro;
    cout << "Antes do saque:" << dinheiro<< endl;
    a -=5;
    dinheiro = a;
    cout << "Depois do saque:" << dinheiro<< endl;
}

void * consulta(void *i){
    cout << "Valor na conta:" << dinheiro<< endl;
}

int main(){
    sem_init(&semaforo,0,1);
    pthread_t threads[3];
    int n;
    pthread_create(&threads[0],NULL,deposito,(void *) 0);
    pthread_create(&threads[1],NULL,saque,(void *) 0);
    pthread_create(&threads[2],NULL,saque,(void *) 0);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);  
    sleep(0.9);
    cout << "Valor final:" << dinheiro<< endl;
}