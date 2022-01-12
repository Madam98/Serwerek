package com.client.skclient;

import java.net.Socket;

public class ClientThread implements Runnable{

    private Socket connectionSocketDescriptor;

    public ClientThread(Socket connectionSocketDescriptor){
        this.connectionSocketDescriptor = connectionSocketDescriptor;
    }

    @Override
    public void run() {

    }
}
