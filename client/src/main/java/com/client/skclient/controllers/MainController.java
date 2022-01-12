package com.client.skclient.controllers;

import com.client.skclient.Client;
import com.client.skclient.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.TilePane;
import javafx.stage.Stage;
import java.io.IOException;
import java.util.List;

public class MainController {

    private Scene scene;
    private Stage stage;
    private Parent root;
    private Client client;

    @FXML
    private Label loggedInUserLabel;
//
//    @FXML
//    private TilePane mainTilePane;

    public void initialize(Client client){
        this.client = client;
        loggedInUserLabel.setText("Zalogowano jako: " + client.getUsername());
        //TODO: ask server for a list of owned/shared(?) files
    }


    @FXML
    protected void onNewFileClick(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("new-file-view.fxml"));

        Scene newFileScene = new Scene(fxmlLoader.load());
        Stage newFileWindow = new Stage();
        newFileWindow.setTitle("Nowy plik");
        newFileWindow.setResizable(false);
        newFileWindow.setScene(newFileScene);
        newFileWindow.show();

    }

    @FXML
    protected void onOpenFileClick(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("open-file-view.fxml"));

        Scene scene = new Scene(fxmlLoader.load());
        Stage newFileWindow = new Stage();
        newFileWindow.setTitle("Otwórz plik");
        newFileWindow.setResizable(false);
        newFileWindow.setScene(scene);
        newFileWindow.show();
    }

    @FXML
    protected void onSaveFileAsClick(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("save-file-as-view.fxml"));

        Scene scene = new Scene(fxmlLoader.load());
        Stage newFileWindow = new Stage();
        newFileWindow.setTitle("Zapisz plik jako");
        newFileWindow.setResizable(false);
        newFileWindow.setScene(scene);
        newFileWindow.show();
    }

    @FXML
    protected void onDeleteFileClick(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("delete-file-view.fxml"));

        Scene scene = new Scene(fxmlLoader.load());
        Stage newFileWindow = new Stage();
        newFileWindow.setTitle("Usuń plik");
        newFileWindow.setResizable(false);
        newFileWindow.setScene(scene);
        newFileWindow.show();
    }

    private void switchContext() throws IOException {
        scene = loggedInUserLabel.getScene();
        stage = (Stage)scene.getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
        root = fxmlLoader.load();
        LogInController logInController = fxmlLoader.getController();
        logInController.initialize(client);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onLogOutButtonClick(ActionEvent actionEvent) throws IOException {
        System.out.print("Wylogowywanie użytkownika: " + client.getUsername() + "\n");
        client.disconnect();
        switchContext();
    }


}

