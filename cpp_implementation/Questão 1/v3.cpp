#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>
using namespace std;

int dinheiro=0;
int countWriter=2;
sem_t semaforoL; //Semaforo para os leitores.
sem_t semaforoE; //Semaforo para os escritores.
//A prioridade das threads de leitura e escrita ficam definidas na ordem em que os semaforos sao liberados!
void * deposito(void *i){ //Escritora
    sem_trywait(&semaforoL);
    sem_wait(&semaforoE);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do deposito:" << dinheiro<< endl;
    a += 10;
    sleep(0.2);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do deposito:" << dinheiro<< endl;
    countWriter--;
    sem_post(&semaforoE); 
    sem_post(&semaforoL);
}

void * saque(void *i){ //Escritora
    sem_trywait(&semaforoL);
    sem_wait(&semaforoE);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do saque:" << dinheiro<< endl;
    a -=5;
    sleep(0.2);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do saque:" << dinheiro<< endl;
    countWriter--;
    sem_post(&semaforoE);
    sem_post(&semaforoL);
}

void * consulta(void *i){ //Leitora
    while(countWriter!=0){
        sleep(0.9);
    }
    cout << "(THREAD LEITORA) Valor na conta:"<< dinheiro << endl;
    sem_post(&semaforoL);
}

int main(){
    sem_init(&semaforoL,0,1);
    sem_init(&semaforoE,0,1);
    pthread_t threads[3];
    int n;
    pthread_create(&threads[0],NULL,deposito,(void *) 0);
    pthread_create(&threads[1],NULL,consulta,(void *) 0);
    pthread_create(&threads[2],NULL,saque,(void *) 0);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);
    
    cout << "\nVALOR FINAL:"<<dinheiro<<endl;

}
