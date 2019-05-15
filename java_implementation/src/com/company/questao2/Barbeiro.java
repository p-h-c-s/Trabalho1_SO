package com.company.questao2;

import com.company.questao1.ContaBancariaSemControle;
import com.company.questao1.ContaBancariaSemPreferencia;
import com.company.questao1.ContaBancariaSincronized;


/*
Ideia geral: Os clientes chegam  e sao enfileirados em uma fila sincronizada. Enquanto existirem barbeiros livres, mandar um barbeiro
desinfileirar um clilente e o atender. Se a fila estiver cheia os clientes sao descartados.
 */

public class Barbeiro implements Runnable {



    private static int numTotalClientes;
    private static int numBarbeiros;

    //variavel que determina se um dado barbeiro está ocupado;
    private boolean isBusy;

    private FilaDeEspera filaDeEspera;

    public Barbeiro(FilaDeEspera filaDeEspera){
        this.filaDeEspera = filaDeEspera;
    }


    public void atendeCliente(){
        Cliente clt;
        /*
        o motivo da filaDeEspera lidar com isso e porque ela e synchronized. Caso eu quisesse lidar com o wait() na classe Barbeiro
        esse metodo iria ter que ser synchronized.
        */
        clt = this.filaDeEspera.getNextCliente(Thread.currentThread().getId());
        if(clt != null){
            clt.notifyAtendimento(Thread.currentThread().getId());
        }

    }


    public static void setNumTotalClientes(int numTotalClientes) {
        Barbeiro.numTotalClientes = numTotalClientes;
    }

    @Override
    public void run(){
        System.out.println("Thread de Barbeiro: " + Thread.currentThread().getId() + " Inicializando...");
        numBarbeiros++;

        /*
        enquanto todos os clientes nao forem atendidos, tentar atender. Obs: esse numero nao corresponde ao numero de clientes esperando o atendimento nas filas.
        Isso ocorre para simular uma entrada dinâmica de clientes.
        */
        while(numTotalClientes > 0){
            atendeCliente();
        }


        numBarbeiros--;
        System.out.println("Thread de Barbeiro: " + Thread.currentThread().getId() + " Finalizando...");
    }
}
