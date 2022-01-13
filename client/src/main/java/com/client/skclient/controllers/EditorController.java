package com.client.skclient.controllers;

import com.client.skclient.Client;
import com.client.skclient.Main;
import com.client.skclient.TextFile;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextInputDialog;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Optional;

public class EditorController {

    private Scene scene;
    private Stage stage;
    private Parent root;
    private Client client;
    private String filename;
    private int caret;

    @FXML
    private TextArea mainTextArea;

    public void initialize(Client client, String filename) {
        this.client = client;
        this.filename = filename;
        this.caret = 0;

        mainTextArea.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String oldValue, String newValue) {
                System.out.print("Zmiana: " + observableValue + "\n");
            }
        });

        mainTextArea.caretPositionProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number oldValue, Number newValue) {
                caret = mainTextArea.getCaretPosition();
                System.out.print("Pozycja: " + caret + "\n");
            }
        });
    }

    public void setText(String text) {
        mainTextArea.setText(text);
    }

    public String getText() {
        return mainTextArea.getText();
    }

    private void goToMain() throws IOException {
        scene = mainTextArea.getScene();
        stage = (Stage)scene.getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        root = fxmlLoader.load();
        MainController mainController = fxmlLoader.getController();
        mainController.initialize(client);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onSaveFileAsClick(ActionEvent actionEvent) throws IOException {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Zapisz jako");
        dialog.setHeaderText("Podaj nazwę pliku");
        Optional<String> result = dialog.showAndWait();
        String filename = "";

        if (result.isPresent()) {
            filename = result.get();
            TextFile.createFile(filename);
            // TODO: OPEN NEW COPY IN EDITOR
        }
    }

    @FXML
    protected void onDeleteFileClick(ActionEvent actionEvent) throws IOException {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Usuwanie pliku");
        alert.setHeaderText("Czy na pewno chcesz usunąć plik?");
        Optional<ButtonType> result = alert.showAndWait();
        if (result.get() == ButtonType.OK){
            // TODO: SEND DELETE COMMAND TO SERVER
            goToMain();
        }
    }

    @FXML
    protected void onCloseFileClick(ActionEvent actionEvent) throws IOException {
        // TODO: let server know that file is closed
        goToMain();

    }

}

