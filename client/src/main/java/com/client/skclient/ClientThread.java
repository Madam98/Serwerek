package com.client.skclient;

import java.io.IOException;
import java.net.Socket;

public class ClientThread implements Runnable{

    private Socket connectionSocketDescriptor;
    private Client client;

    public ClientThread(Socket connectionSocketDescriptor, Client client){
        this.connectionSocketDescriptor = connectionSocketDescriptor;
        this.client = client;
    }

    @Override
    public void run() {
        // odczytaj wiadomości przychodzące od serwera
        while(true){
            try {
                String serverMessage = client.getReader().readLine();
                System.out.print("Serwer: " + serverMessage);
            } catch (IOException e) {
//              e.printStackTrace();
                System.out.print("Połączenie z serwerem zostało przerwane\n");
            }

        }
    }
}
