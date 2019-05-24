#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>
using namespace std;

sem_t semaforo;

struct carrinho{
    int itens;
    int valor;
};

carrinho car;
void * adiciona(void *i){
    cout << "(ESCRITORA) Antes de adicionar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    car.itens++;
    sleep(1);
    car.valor +=*((int*)i);
    cout << "(ESCRITORA) Depois de adicionar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
}

void * retira(void *i){
    cout << "(ESCRITORA) Antes de retirar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
    car.itens--;
    sleep(1);
    car.valor -=*((int*)i); 
    cout << "(ESCRITORA) Depois de retirar| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
}

void * consulta(void *i){
    cout << "(LEITIRA) Carrinho| ITENS:" << car.itens<<" VALOR:"<< car.valor<<endl;
}

int main(){
    car.itens=0;
    car.valor=0;
    int leitoras, num_adiciona,num_retira;
    cout << "Insira a quantidade de adiciona, retira e leitoras: ";
    cin >> num_adiciona >> num_retira >> leitoras;
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