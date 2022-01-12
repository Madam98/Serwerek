package com.client.skclient;

import com.client.skclient.controllers.LogInController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    private Stage stage;
    private Scene scene;
    private Parent root;
    private Client client;

    public void initialize(){

    }

    @Override
    public void start(Stage startingStage) throws IOException {
        client = new Client();
        stage = startingStage;

        // zainicjuj kontroler okna logowania (przekaż instancję klasy Client)
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
        root = fxmlLoader.load();
        LogInController logInController = fxmlLoader.getController();
        logInController.initialize(client);

        scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Współbieżny edytor tekstu");
        stage.sizeToScene();
        stage.show();
    }

    public static void main(String[] args) { launch(args); }


}

