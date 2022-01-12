package com.client.skclient.controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class SaveFileAsController {

    @FXML
    private Label warningLabel;

    @FXML
    private TextField filenameTF;

    @FXML
    protected void onSaveButtonClick(ActionEvent actionEvent) throws IOException {
        //TODO: jeśli plik już istnieje - wyświetl warninga o nadpisaniu
        //TODO: skopiuj plik z nową nazwą!

        String filename = filenameTF.getText();
        if (filename.isEmpty()){
            warningLabel.setText("Nazwa pliku jest wymagana.");
            warningLabel.setVisible(true);
        }
        else{
            System.out.print("Zapisywanie pliku jako:" + filename + ".txt\n");
            Stage stage = (Stage)warningLabel.getScene().getWindow();
            stage.close();
        }

    }
}