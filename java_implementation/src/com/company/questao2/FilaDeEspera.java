package com.company.questao2;

import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

/**
 * Classe que essencialmente funciona como um buffer sincronizado para os clientes que chegam na barbearia
 */
public class FilaDeEspera {

    private final Queue<Cliente> fila;

    private static int numTotalClientes;

    /**
     * Tamanho maximo da fila de espera
     */
    private int maxSize;

    public FilaDeEspera(int maxSize){
        this.maxSize = maxSize;
        this.fila = new LinkedList<>();
    }

    public synchronized boolean enfileiraCliente(Cliente c,long threadId){
        if (this.fila.size() < this.maxSize) {
            Barbeiro.updateAll();
            try {
                    Thread.sleep(250);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                this.fila.add(c);
                System.out.println("Thread Cliente: " + threadId + " enfileirando...");
                //libera a fila
                notifyAll();
                //e preciso dar notifyAll em algum barbeiro aqui
                /*
                synchronized (BarbeariaMain.barbeiros.get(0)){
                    BarbeariaMain.barbeiros.get(0).notifyAll();
                }*/

                return true;
            } else {
                if(Barbeiro.numBarbeiros > 0){
                    Barbeiro.updateAll();
                    //tranca a fila de espera que consequentemente tranca o cliente
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                return false;
            }
    }

    public synchronized Cliente getNextCliente(long threadId){
        System.out.println(FilaDeEspera.getNumTotalClientes());
            if (FilaDeEspera.getNumTotalClientes() == 0) {
                //faz os barbeiros que estao dormindo finalizarem
                notifyAll();
                return null;
            }
            try {
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                Cliente clt = this.fila.remove();
                if(clt != null){
                    FilaDeEspera.decrNumTotalClientes();
                    System.out.println("Thread barbeiro " + threadId + " consumindo cliente " + clt.getThreadId());
                }
                notifyAll();
                return clt;
            } catch (NoSuchElementException e) {
                //System.out.println("total = "  + Barbeiro.getNumTotalClientes());

                System.out.println("Thread de Barbeiro: " + threadId + " Dormindo...");
                try {
                    wait();
                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
                System.out.println("Thread de Barbeiro: " + threadId + " Acordando...");
                return null;
            }
    }

    public synchronized static void setNumTotalClientes(int numTotalClientes) {
        FilaDeEspera.numTotalClientes = numTotalClientes;
    }

    public synchronized static int getNumTotalClientes() {
        return numTotalClientes;
    }

    public synchronized static void decrNumTotalClientes(){
        FilaDeEspera.numTotalClientes--;
    }


    public int getSize(){
        return this.fila.size();
    }

}
