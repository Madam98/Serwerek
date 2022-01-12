package com.client.skclient.controllers;

import com.client.skclient.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MenuController {

    @FXML
    protected void onNewFileClick(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("new-file-view.fxml"));

        Group root = new Group();
        Scene scene = new Scene(fxmlLoader.load());
        Stage newFileWindow = new Stage();
        newFileWindow.setTitle("Nowy plik");
        newFileWindow.setResizable(false);
        newFileWindow.setScene(scene);
        newFileWindow.show();
    }

    @FXML
    protected void onOpenFileClick(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("open-file-view.fxml"));

        Group root = new Group();
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

        Group root = new Group();
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

        Group root = new Group();
        Scene scene = new Scene(fxmlLoader.load());
        Stage newFileWindow = new Stage();
        newFileWindow.setTitle("Usuń plik");
        newFileWindow.setResizable(false);
        newFileWindow.setScene(scene);
        newFileWindow.show();
    }

    public void initialize(){

    }
}

