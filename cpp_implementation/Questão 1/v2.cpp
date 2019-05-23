#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>
using namespace std;

int dinheiro=0;
sem_t semaforo; //Semaforo unico pois nao temos preferencia entre Leitores e Escritores, pode gerar LEITURA SUJA!

void * deposito(void *i){ //Escritora
    sem_wait(&semaforo);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do deposito:" << dinheiro<< endl;
    a += *((int *)i);
    sleep(0.5);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do deposito:" << dinheiro<< endl;
    sem_post(&semaforo);
}

void * saque(void *i){ //Escritora
    sem_wait(&semaforo);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do saque:" << dinheiro<< endl;
    a -=*((int*)i);
    sleep(0.5);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do saque:" << dinheiro<< endl;
    sem_post(&semaforo);
}

void * consulta(void *i){ //Leitora
    sem_wait(&semaforo);
    cout << "(THREAD LEITORA) Valor na conta:"<< dinheiro << endl;
    sem_post(&semaforo);
}

int main(){
    sem_init(&semaforo,0,1);
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
    
    cout << "\nVALOR FINAL:"<<dinheiro<<endl;

}
