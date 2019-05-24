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

struct carrinho{
    int itens;
    int valor;
};
carrinho car;

void * adiciona(void *i){ //Escritora
    sem_wait(&semaforoE);
    cout << "(THREAD ESCRITORA) Antes de adicionar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    car.itens++;
    sleep(0.7);
    car.valor += *((int *)i);
    cout << "(THREAD ESCRITORA) Depois de adicionar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    countWriter--;
    sem_post(&semaforoE); 
    sem_post(&semaforoL);
}

void * retira(void *i){ //Escritora
    sem_wait(&semaforoE);
    cout << "(THREAD ESCRITORA) Antes de retirar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    car.itens--;
    sleep(0.7);
    car.valor -=*((int*)i);
    cout << "(THREAD ESCRITORA) Depois de retirar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    countWriter--;
    sem_post(&semaforoE);
    sem_post(&semaforoL);
}

void * consulta(void *i){ //Leitora
    while(countWriter!=0){
        sem_wait(&semaforoL);
    }
    cout << "(THREAD LEITORA) Carrinho| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    sem_post(&semaforoL);
}

int main(){
    sem_init(&semaforoL,0,1);
    sem_init(&semaforoE,0,1);
    int leitoras, num_adiciona,num_retira;
    cout << "Insira a quantidade de adiciona, retira e leitoras: ";
    cin >> num_adiciona >> num_retira >> leitoras;
    countWriter = num_adiciona+num_retira;
    pthread_t threads[num_adiciona+num_retira+leitoras];
    int add,rm;
    cout << "Qual valor de adicionar e retirar: ";
    cin >> add >> rm;
    for (int i = 0; i < num_adiciona; i++){
        pthread_create(&threads[i],NULL,adiciona,&add);
    }

    for (int i = num_adiciona; i < num_adiciona+num_retira; i++){
        pthread_create(&threads[i],NULL,retira,&rm);
    }
    
    for (int i = num_adiciona+num_retira; i < num_adiciona+num_retira+leitoras; i++){
        pthread_create(&threads[i],NULL,consulta,(void *)0);
    }
    
    for (int i = 0; i < num_adiciona+num_retira+leitoras; i++){
        pthread_join(threads[i],NULL);
    }
    
    cout << "VALORES FINAIS| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
}
