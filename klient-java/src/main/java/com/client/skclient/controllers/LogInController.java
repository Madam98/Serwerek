package com.client.skclient.controllers;

import com.client.skclient.Client;
import com.client.skclient.Main;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import java.io.*;
import java.net.SocketTimeoutException;

public class LogInController {

    private Scene scene;
    private Stage stage;
    private Client client;
    private Parent root;

    @FXML
    private Label warningLabel;

    @FXML
    private TextField serverAddressTF;

    @FXML
    private TextField serverPortTF;

    @FXML
    private TextField usernameTF;

    public void initialize(Client client, Stage stage){
        this.client = client;
        this.stage = stage;
    }

    private Boolean connectToServer(String username) {
        try {
            String serverAddress = serverAddressTF.getText().trim();
            String serverPort = serverPortTF.getText().trim();

            // połącz
            client.connect(serverAddress, serverPort);
//            client.connect(serverAddress, serverPort, username);

//            // wyślij wiadomość testową
//            OutputStream os = client.getConnectionSocket().getOutputStream();
            return true;

        } catch(IOException | InterruptedException ex) {
            System.out.print("Nie udało się nawiązać połączenia z serwerem:: " + ex);
            warningLabel.setText("Nie udało się nawiązać połączenia z serwerem.");
            warningLabel.setVisible(true);
            return false;
        }
    }

    private void switchContext() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        root = fxmlLoader.load();

        MainController mainController = fxmlLoader.getController();
        mainController.initialize(client, stage);

        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }


    @FXML
    protected void onLogInButtonClick(ActionEvent actionEvent) throws IOException {
        warningLabel.setVisible(false);
        String username = usernameTF.getText().trim();
        if (username.isEmpty()){
            warningLabel.setText("Nazwa użytkownika jest wymagana.");
            warningLabel.setVisible(true);
        }
        else {
            client.setUsername(username);
            System.out.print("Logowanie użytkownika: " + username + "\n");

            // połącz z serwerem i przełącz konteks jeśli udało się połączyć
            if (connectToServer(username)) {
                //uruchom wątek nasłuchujący
                //client.handleConnection();
                switchContext();
            }
        }
    }
}