package com.client.skclient.controllers;

import com.client.skclient.Client;
import com.client.skclient.Main;
import com.client.skclient.TextFile;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.TextInputDialog;
import javafx.scene.layout.TilePane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.io.IOException;
import java.util.List;
import java.util.Optional;
import java.util.regex.Pattern;

public class MainController {

    private Scene scene;
    private Stage stage;
    private Parent root;
    private Client client;

    @FXML
    private Label loggedInUserLabel;


    public void initialize(Client client){
        this.client = client;
        loggedInUserLabel.setText("Zalogowano jako: " + client.getUsername());
        //TODO: ask server for a list of owned/shared(?) files
    }

    private void goToTextEditor(String filename) throws IOException {
        stage = (Stage)loggedInUserLabel.getScene().getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("editor-view.fxml"));
        root = fxmlLoader.load();
        EditorController editorController = fxmlLoader.getController();
        editorController.initialize(client, filename);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onNewFileClick(ActionEvent actionEvent) throws IOException {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Nowy plik");
        dialog.setHeaderText("Podaj nazwę pliku");
        Optional<String> result = dialog.showAndWait();
        String filename = "";

        if (result.isPresent()) {
            filename = result.get();
            TextFile.createFile(filename);
            goToTextEditor(filename);
        }
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

    private void goToLogIn() throws IOException {
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
        goToLogIn();
    }


}

