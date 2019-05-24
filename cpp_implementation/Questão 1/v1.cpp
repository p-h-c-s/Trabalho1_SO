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

      int leitoras, num_deposito,num_saque;
    cout << "Insira a quantidade de deposito, saque e leitoras: ";
    cin >> num_deposito >> num_saque >> leitoras;
    pthread_t threads[num_deposito+num_saque+leitoras];
    int dep,saq;
    cout << "Qual valor de deposito e saque: ";
    cin >> dep >> saq;
    for (int i = 0; i < num_deposito; i++){
        pthread_create(&threads[i],NULL,deposito,&dep);
    }

    for (int i = num_deposito; i < num_deposito+num_saque; i++){
        pthread_create(&threads[i],NULL,saque,&saq);
    }
    
    for (int i = num_deposito+num_saque; i < num_deposito+num_saque+leitoras; i++){
        pthread_create(&threads[i],NULL,consulta,(void *)0);
    }
    
    for (int i = 0; i < num_deposito+num_saque+leitoras; i++){
        pthread_join(threads[i],NULL);
    }
    cout << "Valor final:" << dinheiro<< endl;
}