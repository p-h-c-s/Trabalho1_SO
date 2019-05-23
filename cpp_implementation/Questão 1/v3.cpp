#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>
using namespace std;

int dinheiro=0;
int countWriter;
sem_t semaforoL; //Semaforo para os leitores.
sem_t semaforoE; //Semaforo para os escritores.
//A prioridade das threads de leitura e escrita ficam definidas na ordem em que os semaforos sao liberados!
void * deposito(void *i){ //Escritora
    sem_wait(&semaforoE);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do deposito:" << dinheiro<< endl;
    a += *((int*)i);
    sleep(0.2);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do deposito:" << dinheiro<< endl;
    countWriter--;
    sem_post(&semaforoE); 
    sem_post(&semaforoL);
}

void * saque(void *i){ //Escritora
    sem_wait(&semaforoE);
    sleep(0.1);
    int a =dinheiro;
    cout << "(THREAD ESCRITORA) Antes do saque:" << dinheiro<< endl;
    a -=*((int*)i);
    sleep(0.2);
    dinheiro = a;
    cout << "(THREAD ESCRITORA) Depois do saque:" << dinheiro<< endl;
    countWriter--;
    sem_post(&semaforoE);
    sem_post(&semaforoL);
}

void * consulta(void *i){ //Leitora
    while(countWriter!=0){
        cout<< "conta:" <<countWriter<<endl;
        sem_wait(&semaforoL);
    }
    cout << "(THREAD LEITORA) Valor na conta:"<< dinheiro << endl;
    sem_post(&semaforoL);
}

int main(){
    sem_init(&semaforoL,0,1);
    sem_init(&semaforoE,0,1);
    int leitoras, num_deposito,num_saque;
    cout << "Insira a quantidade de deposito, saque e leitoras: ";
    cin >> num_deposito >> num_saque >> leitoras;
    countWriter = num_deposito+num_saque;
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
