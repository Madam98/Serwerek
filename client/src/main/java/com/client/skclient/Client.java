package com.client.skclient;

import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.Collections;
import java.util.List;

public class Client {

    private Socket connectionSocket;
    private String username;
    private List<String> documents;
    private Thread thread;

    private PrintWriter writer;
    private BufferedReader reader;

    public void Client(){
        connectionSocket = null;
        documents = Collections.emptyList();
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public List<String> getDocuments(){
        return documents;
    }

    public BufferedReader getReader(){
        return reader;
    }

    public PrintWriter getWriter(){
        return writer;
    }

    public Socket getConnectionSocket(){
        return connectionSocket;
    }

    public String getUsername(){
        return username;
    }


    public void connect(String host, String port) throws IOException {
//    public void connect(String host, String port, String username) throws IOException {
//        this.username = username;
        InetAddress address = InetAddress.getByName(host);
        connectionSocket = new Socket();
        connectionSocket.connect(new InetSocketAddress(address, Integer.parseInt(port)), 5000);

        writer = new PrintWriter(connectionSocket.getOutputStream(), true);
        reader = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
    }

    public void disconnect() throws IOException {
        connectionSocket.close();
    }

    public void handleConnection(){
        ClientThread clientThread = new ClientThread(connectionSocket, this);
        thread = new Thread(clientThread);
        thread.start();
    }

}
