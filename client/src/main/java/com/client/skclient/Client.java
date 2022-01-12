package com.client.skclient;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Collections;
import java.util.List;

public class Client {

    private Socket connectionSocket;
    private String username;
    private List<String> documents;
    private Thread thread;

    public void Client(){
        connectionSocket = null;
        documents = Collections.emptyList();
    }

    public List<String> getDocuments(){
        return documents;
    }

    public Socket getConnectionSocket(){
        return connectionSocket;
    }

    public String getUsername(){
        return username;
    }

    public void connect(String host, int port, String username) throws IOException {
        this.username = username;
        InetAddress address = InetAddress.getByName(host);
        connectionSocket = new Socket(address, port);
    }

    public void disconnect() throws IOException {
        connectionSocket.close();
    }

    public void handleConnection(){
        ClientThread clientThread = new ClientThread(connectionSocket);
        thread = new Thread(clientThread);
        thread.start();
    }

}
