package com.company.questao2;

import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

/**
 * Classe que essencialmente funciona como um buffer sincronizado para os clientes que chegam na barbearia
 */
public class FilaDeEspera {

    private Queue<Cliente> fila;

    /**
     * Tamanho maximo da fila de espera
     */
    private int maxSize;

    public FilaDeEspera(int maxSize){
        this.maxSize = maxSize;
        this.fila = new LinkedList<>();
    }

    public synchronized boolean enfileiraCliente(Cliente c){
        if(this.fila.size() < this.maxSize){
            this.fila.add(c);
            notifyAll();
            return true;
        }else{
            return false;
        }

    }

    public synchronized Cliente getNextCliente(long threadId){
        try{
            try {
                Thread.sleep(250);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return this.fila.remove();
        }catch (NoSuchElementException e){
            System.out.println("Thread de Barbeiro: " + threadId + " Dormindo...");
            try {
                wait();
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
            return null;
        }

    }

    public int getSize(){
        return this.fila.size();
    }

}
