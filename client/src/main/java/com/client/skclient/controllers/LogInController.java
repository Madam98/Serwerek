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

public class LogInController {

    private Scene scene;
    private Stage stage;
    private Client client;
    private Parent root;

    public void initialize(Client client){
        System.out.print("Initializing...\n");
        this.client = client;
    }

    private Boolean connectToServer(String username) {
        try {
            // połącz
            client.connect("127.0.0.1", 1234, username);

            // wyślij wiadomość testową
            OutputStream os = client.getConnectionSocket().getOutputStream();
            PrintWriter writer = new PrintWriter(os, true);
            writer.println("Dzień dobry");
            return true;

        } catch(Exception ConnectException) {
            warningLabel.setText("Nie udało się nawiązać połączenia z serwerem.");
            warningLabel.setVisible(true);
            return false;
        }
    }

    private void switchContext() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        root = fxmlLoader.load();

        MainController mainController = fxmlLoader.getController();
        mainController.initialize(client);

        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private Label warningLabel;

    @FXML
    private TextField usernameTF;

    @FXML
    protected void onLogInButtonClick(ActionEvent actionEvent) throws IOException {
        String username = usernameTF.getText();
        if (username.isEmpty()){
            warningLabel.setText("Nazwa użytkownika jest wymagana.");
            warningLabel.setVisible(true);
        }
        else {
            System.out.print("Logowanie użytkownika: " + username + "\n");
            scene = warningLabel.getScene();
            stage = (Stage)scene.getWindow();

            // połącz z serwerem i przełącz konteks jeśli udało się połączyć
            if (connectToServer(username)) {
                client.handleConnection();
                switchContext();
            }
        }
    }
}