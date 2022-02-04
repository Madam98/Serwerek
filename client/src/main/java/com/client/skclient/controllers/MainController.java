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
import javafx.scene.control.TextField;
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
    private TextFile file;

    @FXML
    private Label loggedInUserLabel;

    @FXML
    private TextField filenameTF;


    private void switchToNewFile() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-new-file-view.fxml"));
        root = fxmlLoader.load();

        MainController mainController = fxmlLoader.getController();
        mainController.initialize(client, stage);

        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    private void switchToOpenFile() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-open-file-view.fxml"));
        root = fxmlLoader.load();

        MainController mainController = fxmlLoader.getController();
        mainController.initialize(client, stage);

        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void initialize(Client client, Stage stage){
        this.client = client;
        this.stage = stage;
        this.file = new TextFile(client);
        loggedInUserLabel.setText("Zalogowano jako: " + client.getUsername());
        //TODO: ask server for a list of owned/shared(?) files
    }

    private void goToTextEditor() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("editor-view.fxml"));
        root = fxmlLoader.load();
        EditorController editorController = fxmlLoader.getController();
        editorController.initialize(client, file);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onCreateFileButtonClick(ActionEvent actionEvent) throws IOException {

        String filename = filenameTF.getText();
        file.setFilename(filename);
        file.createFile(filename);
//        file.testCreateFile();
        goToTextEditor();
    }

    @FXML
    protected void onOpenFileButtonClick(ActionEvent actionEvent) throws IOException {

        String filename = filenameTF.getText();
        file.setFilename(filename);
        file.openFile();
        goToTextEditor();
    }

    @FXML
    protected void onNewFileClick(ActionEvent actionEvent) throws IOException {
        switchToNewFile();

        //        TextInputDialog dialog = new TextInputDialog();
//        dialog.setTitle("Nowy plik");
//        dialog.setHeaderText("Podaj nazwę pliku");
//        System.out.print("scene: "+scene+"\n");
//        System.out.print("stage: "+stage+"\n");
//        Optional<String> result = dialog.showAndWait();
//        String filename = "";

//        if (result.isPresent()) {
//            filename = result.get();
////            file.createFile(filename);
//            file.testCreateFile(filename);
//            goToTextEditor(filename);
//        }
    }

    @FXML
    protected void onOpenFileClick(ActionEvent actionEvent) throws IOException {
        switchToOpenFile();
//        TextInputDialog dialog = new TextInputDialog();
//        dialog.setTitle("Otwórz plik");
//        dialog.setHeaderText("Podaj nazwę pliku");
//        Optional<String> result = dialog.showAndWait();
//        String filename = "";
//
//        if (result.isPresent()) {
//            filename = result.get();
//            file.setFilename(filename);
//            file.openFile();
//            goToTextEditor();
//        }
    }

    private void goToLogIn() throws IOException {

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
        root = fxmlLoader.load();
        LogInController logInController = fxmlLoader.getController();
        logInController.initialize(client, stage);
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

