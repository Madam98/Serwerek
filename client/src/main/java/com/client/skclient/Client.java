package com.client.skclient;

import javafx.scene.layout.Pane;

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


    public void connect(String host, String port) throws IOException, InterruptedException {
        // połączenie
        InetAddress address = InetAddress.getByName(host);
        connectionSocket = new Socket();
        connectionSocket.connect(new InetSocketAddress(address, Integer.parseInt(port)), 5000);

        // inicjacja obiektów piszących z czytających
        writer = new PrintWriter(connectionSocket.getOutputStream(), true);
        reader = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));

        // wysłanie polecenia add o dodaniu nowego użytkownika
        writer.println("add:"+username);

        // TODO: obsługa ponownego logowania już istniejącego użytkownika
        System.out.println("Połączono z serwerem");


//
//        String msg = reader.readLine();
//        if (msg.equals("username")) {
//            Thread.sleep(1000);
//            System.out.println("Wysyłanie nazwy zalogowanego uztkownika " + this.username);
//            writer.println(this.username);
//        }
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
