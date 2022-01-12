package com.client.skclient.controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class DeleteFileController {

    @FXML
    private Label warningLabel;

    @FXML
    private TextField filenameTF;

    @FXML
    protected void onDeleteButtonClick(ActionEvent actionEvent) throws IOException {
        String filename = filenameTF.getText();
        if (filename.isEmpty()){
            warningLabel.setText("Nazwa pliku jest wymagana.");
            warningLabel.setVisible(true);
        }
        else{
            System.out.print("Usuwanie pliku: " + filename + ".txt\n");
            Stage stage = (Stage)warningLabel.getScene().getWindow();
            stage.close();
        }
        System.out.print("Potwierdzono usuwanie pliku: " + filename + ".txt\n");

    }

    @FXML
    protected void onCancelButtonClick(ActionEvent actionEvent) throws IOException {


    }
}