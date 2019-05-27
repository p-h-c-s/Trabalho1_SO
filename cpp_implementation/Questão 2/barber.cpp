#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

sem_t mutex;
sem_t sem_clientes;
sem_t sem_barbeiros;
int MAX_CLIENTES;

vector<int> buffer;
int in=0;
int out=0;

int num_clientes;
int num_threads_clientes = num_clientes;
int num_barbeiros;

int fila = 0;

void *barbeiro(void *arg){
    int i =  *((int*) arg);
    while (num_clientes>0){
        cout<< "Babeiro "<<i<<" esperando cliente\n"; 
        sem_wait(&sem_clientes);
        num_clientes--;
        cout<< "Babeiro "<<i<<" cortando cabelo do cliente "<<buffer[out]<<endl;
        buffer[out]=0; //Retira um cliente da fila. Necessario estar dentro de uma area critica pois se nao podemos ter escrita suja
        out = (out+1)%MAX_CLIENTES;//Garante que nao saia do vetor
        sleep(5);
        cout<< "Babeiro "<<i<<" cortou cabelo.\n";
        sem_post(&sem_barbeiros); //Libera um barbeiro.
    }
}

void *cliente(void *arg){
    int i = *((int*)arg);
    if(buffer[in]==0){
        cout<< "Cliente "<<i<<" está na fila.\n";
        buffer[in]=i; //Adiciona um cliente na fila
        in = (in+1)%MAX_CLIENTES; //Garante que nao saia do vetor
        sem_post(&sem_clientes); //Aumenta o valor do semaforo dos clientes
        sem_wait(&sem_barbeiros); //Diminui o valor do semaforo dos barbeiros
        cout << "Cliente "<<i<<" cortou o cabelo.\n";
    }
    else{
        cout<<"Cliente "<<i<<" foi embora pois barbearia estava lotada.\n";
        num_clientes--;
    }
}

int main(){
    cout <<"Informe o numero de barbeiros, cadeiras de espera e clientes: ";
    cin >>num_barbeiros >> MAX_CLIENTES >> num_clientes;
    num_threads_clientes = num_clientes;
    buffer.resize(MAX_CLIENTES);
    sem_init(&mutex,0,1);
    sem_init(&sem_clientes,0,0);
    sem_init(&sem_barbeiros,0,0);
    int n;
    pthread_t threads[num_barbeiros+num_clientes];
    cout << endl;
    for (int i = 0; i < num_barbeiros; i++){
        pthread_create(&threads[i],NULL,barbeiro,&i);
        sleep(0.00001); //Tempo infimo apenas para dar tempo de atualizar o i.
        
    }

    int copia;
    for (int i = num_barbeiros; i < num_barbeiros+num_threads_clientes; i++){
        copia = i-num_barbeiros+1;
        pthread_create(&threads[i],NULL,cliente,&copia);
        sleep(0.00001);
    }
    
    for (int i = 0; i < num_barbeiros+num_threads_clientes; i++){
        pthread_join(threads[i],NULL);
    }
    return 0;
}