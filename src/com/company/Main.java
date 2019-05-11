package com.company;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Main {


    //https://stackoverflow.com/questions/11073841/why-doesnt-this-synchronized-method-work-as-expected

    public static void item1(int[] vetEntradas, ContaBancariaSemControle contaBancariaSemControle, int numLeitores){
        ContaBancariaThread contaBancariaThread;
        /**
         * Criar *numEscritores* threads de escrita. Cada uma ira depositar um valor que está guardado em vetEntradas.
         */
        for (int i:vetEntradas) {
            contaBancariaThread = new ContaBancariaThread('d',i,contaBancariaSemControle);
            //passar objeto runnable pra classe.
            Thread thread = new Thread(contaBancariaThread);
            thread.start();
        }

        /**
         * Criar *numLeitores* threads de leitura. Cada uma ira ler o valor da contaBancariaSemControle.
         */
        for (int i = 0;i < numLeitores; i++) {
            contaBancariaThread = new ContaBancariaThread('g',i,contaBancariaSemControle);
            Thread thread = new Thread(contaBancariaThread);
            thread.start();
        }
    }

    public static void item2(int[] vetEntradas, ContaBancariaSincronized ContaBancariaSincronized, int numLeitores){
        /**
         * Criar *numEscritores* threads de escrita. Cada uma ira depositar um valor que está guardado em vetEntradas.
         */
        for (int i:vetEntradas) {
            ContaBancariaThread contaBancariaThread = new ContaBancariaThread('d',i,ContaBancariaSincronized);
            //passar objeto runnable pra classe.
            Thread thread = new Thread(contaBancariaThread);
            thread.setPriority(Thread.MAX_PRIORITY);
            thread.start();
        }

        /**
         * Criar *numLeitores* threads de leitura. Cada uma ira ler o valor da contaBancariaSemControle.
         */
        for (int i = 0;i < numLeitores; i++) {
            ContaBancariaThread contaBancariaThread = new ContaBancariaThread('g',i,ContaBancariaSincronized);
            Thread thread = new Thread(contaBancariaThread);
            thread.setPriority(Thread.MAX_PRIORITY);
            thread.start();
        }
    }

    public static void item3(int[] vetEntradas, ContaBancariaSincronized contaBancariaSincronized, int numLeitores){

        //Thread[] threads = new Thread[numLeitores+vetEntradas.length];

        ArrayList<Thread> threads = new ArrayList<>();

        //ContaBancariaThread[] contasEscrita = new ContaBancariaThread[vetEntradas.length];

        //ContaBancariaThread[] contasLeitura = new ContaBancariaThread[numLeitores];

        /**
         * Criar *numEscritores* threads de escrita. Cada uma ira depositar um valor que está guardado em vetEntradas.
         */
        for (int i:vetEntradas) {
            ContaBancariaThread contaBancariaThread = new ContaBancariaThread('d',i,contaBancariaSincronized);
            //passar objeto runnable pra classe.
            Thread thread = new Thread(contaBancariaThread);
            threads.add(thread);
            thread.setPriority(Thread.MAX_PRIORITY);
            thread.start();
        }

        /**
         * Criar *numLeitores* threads de leitura. Cada uma ira ler o valor da ContaBancariaSincronized.
         */
        for (int i = 0;i < numLeitores; i++) {
            ContaBancariaThread contaBancariaThread = new ContaBancariaThread('g',i,contaBancariaSincronized);
            Thread thread = new Thread(contaBancariaThread);
            thread.setPriority(Thread.MIN_PRIORITY);
            threads.add(thread);
            thread.start();
        }



        for (int i = 0; i < 5; i++) {

            for (Thread t:threads) {
                if(t.getState() == Thread.State.BLOCKED){
                    System.out.println("Thread " + t.getId() + " estado: " + t.getState());
                }
                if(!(t.isAlive())){
                    System.out.println("Thread " + t.getId() + " estado: finalizado" );
                }
            }

            //gambi pra poder achar as threads bloqueadas
            try {
                Thread.sleep(250);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }


    }



    public static void main(String[] args) {


        /**
         * Leitura
         */
        Scanner inp = new Scanner(System.in);

        final int numEscritores;
        final int numLeitores;

        ContaBancariaSemControle contaBancariaSemControle = new ContaBancariaSemControle();

        ContaBancariaSincronized contaBancariaSincronized2 = new ContaBancariaSincronized();
        ContaBancariaSincronized contaBancariaSincronized3 = new ContaBancariaSincronized();

        System.out.println("Insira o numero de escritores");
        numEscritores = inp.nextInt();

        System.out.println("Insira o numero de Leitores");
        numLeitores = inp.nextInt();

        final int[] vetEntradas = new int[numEscritores];

        System.out.println("Insira o vetor de entrada");

        for (int i = 0 ; i < numEscritores; i++){
            vetEntradas[i] = inp.nextInt();
        }

/*
        System.out.println("Item 1:");

        //item1(vetEntradas,contaBancariaSemControle,numLeitores);


        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


        System.out.println("Item 2:");

        item2(vetEntradas,contaBancariaSincronized2,numLeitores);


        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
*/
        System.out.println("Item 3:");

        item3(vetEntradas,contaBancariaSincronized3,numLeitores);

        inp.close();




        System.out.println(contaBancariaSincronized3.getSaldo());

        /*
        ContaBancariaSincronized conta1 = new ContaBancariaSincronized();

        ContaBancariaSemControle contaSemControle = new ContaBancariaSemControle();

        ContaBancariaThread threadEscrita = new ContaBancariaThread('s', 100,contaSemControle);

        ContaBancariaThread threadAdd = new ContaBancariaThread('d', 100,contaSemControle);

        ContaBancariaThread threadLeitura = new ContaBancariaThread('g', 0,contaSemControle);

        Thread threadSetter = new Thread(threadEscrita);
        threadSetter.setName("setter");
        threadSetter.start();

        Thread threadAdder = new Thread(threadAdd);
        threadAdder.setName("adder");
        threadAdder.start();

        Thread threadLer = new Thread(threadLeitura);
        threadLer.setName("adder");
        threadLer.start();

        try {
            threadSetter.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            threadAdder.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            threadLer.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println(contaSemControle.getSaldo());
*/
        //IMPORTANTE: A main pode acabar antes da thread, entao nao e confiavel dar print


    }
}
