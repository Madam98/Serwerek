package com.client.skclient.controllers;

import com.client.skclient.*;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.scene.Parent;
import javafx.scene.control.*;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.input.ContextMenuEvent;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Optional;

public class EditorController {

    private Scene scene;
    private Stage stage;
    private Parent root;
    private Client client;
    private TextFile file;
    private int caret;
    private String prevKey;
    private TextArea mainTextArea;
    private Thread readerThread;

    @FXML
    private VBox mainTextBox;

    private void closeReaderThread() throws InterruptedException {
        readerThread.join();
    }

    private void goToMain() throws IOException {
        scene = mainTextArea.getScene();
        stage = (Stage)scene.getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        root = fxmlLoader.load();
        MainController mainController = fxmlLoader.getController();
        mainController.initialize(client, stage);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onTextAreaTyped(ActionEvent actionEvent) throws IOException {
        System.out.print("TYPED!\n");
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
            file.deleteFile();
            goToMain();
        }
    }

    @FXML
    protected void onCopyFileClick(ActionEvent actionEvent) {
        file.copyFile();
    }

    @FXML
    protected void onRenameFileClick(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Zmień nazwę pliku");
        dialog.setHeaderText("Podaj nową nazwę");
        Optional<String> result = dialog.showAndWait();
        String filename = "";
        if (result.isPresent()) {
            filename = result.get();
            file.renameFile(filename);
        }
    }

    @FXML
    protected void onCloseFileClick(ActionEvent actionEvent) throws IOException {
        file.closeFile();
        goToMain();
    }

    public void initialize(Client client, TextFile file) {
        this.client = client;
        this.file = file;
        this.caret = 0;
        this.prevKey = null;

        // uruchom wątek nasłuchujący komunikatów serwera
        EditorThread editorThread = new EditorThread(this, client);
        this.readerThread = new Thread(editorThread);
        readerThread.start();

        // zainicjuj pole textArea i jego właściwości
        mainTextArea = new TextArea(file.getLoadedText()) {
            // WYŁĄCZ MOŻLIWOŚĆ WKLEJANIA
            @Override
            public void paste() {}
        };

        mainTextArea.setWrapText(true);
        mainTextArea.setPrefHeight(500.0);

        // ZMIANA POŁOŻENIA WSKAŹNIKA
        mainTextArea.caretPositionProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number oldValue, Number newValue) {
                caret = mainTextArea.getCaretPosition();
                System.out.print("\nPozycja: " + caret + "\n");
            }
        });

        // NACIŚNIĘCIE PRZYCISKU - do wykrywania klawiszy, które nic nie wpisują np. BACKSPACE, DELETE
        mainTextArea.setOnKeyPressed(new EventHandler<KeyEvent>() {
            @Override
            public void handle(KeyEvent keyEvent) {
                System.out.print("Key event type = " + keyEvent.getEventType() + ", character = " + keyEvent.getCharacter() + ", code = " + keyEvent.getCode() + "\n");
                if (keyEvent.getCode() == KeyCode.BACK_SPACE || keyEvent.getCode() == KeyCode.DELETE) {
                    System.out.print("Wysyłanie: editLorem " + caret + " " + keyEvent.getCode() + "\n");
//                    client.getWriter().println("editLorem " + caret + " " + keyEvent.getCode());
                }
            }
        });

        // NAPISANIE ZNAKU - do wykrywania zmiany w tekście (znaki alfanumeryczne + białe znaki)
        mainTextArea.setOnKeyTyped(new EventHandler<KeyEvent>() {
            @Override
            public void handle(KeyEvent keyEvent) {
                System.out.print("Key event type = " + keyEvent.getEventType() + ", character = " + keyEvent.getCharacter() + ", code = " + keyEvent.getCode() + "\n");
                if (!keyEvent.getCharacter().equals("") && !keyEvent.getCharacter().equals("\\u0000")) {
                    System.out.print("Wysyłanie: editLorem " + caret + " " + keyEvent.getCharacter() + "\n");
//                    client.getWriter().println("editLorem " + caret + " " + keyEvent.getCharacter());
                }
            }
        });

        // WYŁĄCZ ZAZNACZANIE TEKSTU
        mainTextArea.setTextFormatter(new TextFormatter<String>(change ->  {
            change.setAnchor(change.getCaretPosition());
            return change ;
        }));

        // WYŁĄCZ MENU KONTEKSTROWE (RMB)
        mainTextArea.addEventFilter(ContextMenuEvent.CONTEXT_MENU_REQUESTED, Event::consume);

        // WYŁĄCZ SKRÓTY KLAWISZOWE
        mainTextArea.addEventFilter(KeyEvent.ANY, event -> {
            if (event.isShortcutDown()) {
                event.consume();
            }
        });

        mainTextBox.getChildren().add(mainTextArea);
        mainTextBox.setVgrow(mainTextArea, Priority.ALWAYS);
    }

    public void setText(String text) {
        mainTextArea.setText(text);
    }

    public String getText() {
        return mainTextArea.getText();
    }



}

