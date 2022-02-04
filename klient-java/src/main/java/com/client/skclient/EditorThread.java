package com.client.skclient;

import com.client.skclient.controllers.EditorController;

import java.io.IOException;
import java.net.Socket;

public class EditorThread implements Runnable{

    private EditorController editor;
    private Client client;
    private Boolean isReading = true;

    private void setReading(Boolean toggle) {
        isReading = toggle;
    }

    public EditorThread(EditorController editorController, Client client){
        this.editor = editorController;
        this.client = client;
    }

    @Override
    public void run() {
        while(isReading){
            try {
                String serverMessage = client.getReader().readLine();
                System.out.print("Wiadomość z serwera: " + serverMessage);
            } catch (IOException e) {
                System.out.print("Połączenie z serwerem zostało przerwane\n");
            }

        }
    }
}
