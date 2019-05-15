package com.company.questao2;

import com.company.questao1.ContaBancariaSemControle;
import com.company.questao1.ContaBancariaSemPreferencia;
import com.company.questao1.ContaBancariaSincronized;

public class Cliente implements Runnable {

    private FilaDeEspera filaDeEspera;
    private boolean foiAtendido = false;

    public Cliente(FilaDeEspera filaDeEspera){
        this.filaDeEspera = filaDeEspera;
    }


    public synchronized void notifyAtendimento(long threadId){
        foiAtendido = true;
        System.out.println("Thread Cliente: " + Thread.currentThread().getId() + " Sendo atendida pelo barbeiro: " + threadId);
    }


    public void enfileiraCliente(){
        //se entrar no if e porque o this nao foi enfileirado devido a fila estar cheia
        if(!this.filaDeEspera.enfileiraCliente(this)){
            System.out.println("Thread Cliente: " + Thread.currentThread().getId() + " Descartada por falta de espaço...");
            //acorda as threads barbeiro que estiverem dormindo
        }
    }

    @Override
    public void run(){
        System.out.println("Thread Cliente: " + Thread.currentThread().getId() + " Inicializando...");
        //coloca o cliente na fila
        enfileiraCliente();
        while(!foiAtendido){
            //notifyAll();
        }
        System.out.println("Thread Cliente: " + Thread.currentThread().getId() + " Finalizando...");
    }
}
