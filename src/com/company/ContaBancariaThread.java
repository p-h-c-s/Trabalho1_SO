package com.company;

public class ContaBancariaThread implements Runnable {

    //qual funcao executar
    private final ContaBancariaSincronized contaBancariaSincronized;
    private final ContaBancariaSemControle contaBancariaSemControle;


    private char modoOperacao;
    private int valorDeposito;
    private int itemQuestao;


    public ContaBancariaThread(char modoOperacao,int valorDeposito ,ContaBancariaSemControle contaBancariaSemControle){
        this.valorDeposito = valorDeposito;
        this.modoOperacao = modoOperacao;
        this.contaBancariaSemControle = contaBancariaSemControle;
        contaBancariaSincronized = null;
    }

    public ContaBancariaThread(char modoOperacao,int valorDeposito, ContaBancariaSincronized contaBancariaSincronized){
        this.valorDeposito = valorDeposito;
        this.modoOperacao = modoOperacao;
        this.contaBancariaSincronized = contaBancariaSincronized;
        this.contaBancariaSemControle = null;
    }

    private void switchModo(){
        if(this.contaBancariaSincronized != null){
            this.itemQuestao = 2;
        }else if(this.contaBancariaSemControle != null){
            this.itemQuestao = 1;
        }
    }

    @Override
    public void run(){
        System.out.println("Thread: " + Thread.currentThread().getId() + " Inicializando... ");
        switchModo();
        if(this.itemQuestao == 1) {
            switch (modoOperacao) {
                case ('d'):
                        System.out.println("Thread: " + Thread.currentThread().getId() + " Escrevendo: " + this.valorDeposito);
                        this.contaBancariaSemControle.depositaSaldo(this.valorDeposito);
                        //deposito
                    break;
                case ('t'):
                   // this.contaBancariaSemControle.transferConta();
                    //transferencia
                    break;
                case ('g'):
                    System.out.println("Thread: " + Thread.currentThread().getId() + " Lendo: " + this.contaBancariaSemControle.getSaldo());

                    //getter
                    break;
                case ('s'):

                    this.contaBancariaSemControle.setSaldo(this.valorDeposito);
                    //setter
                    break;
            }
        }else if(this.itemQuestao==2){
            switch (modoOperacao) {
                case ('d'):
                        System.out.println("Thread: " + Thread.currentThread().getId() + " Escrevendo: " + this.valorDeposito);
                        this.contaBancariaSincronized.depositaSaldo(this.valorDeposito);
                    //deposito
                    break;
                case ('t'):
                    // this.contaBancariaSemControle.transferConta();
                    //transferencia
                    break;
                case ('g'):
                    System.out.println("Thread: " + Thread.currentThread().getId() + " Lendo: " + this.contaBancariaSincronized.getSaldo());
                    //getter
                    break;
                case ('s'):
                    this.contaBancariaSincronized.setSaldo(this.valorDeposito);
                    //setter
                    break;
            }
        }
    }


}
