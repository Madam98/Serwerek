package com.client.skclient;

import javafx.scene.control.Alert;

import java.io.IOException;

public class TextFile {

    private Client client;
    private static final char[] ILLEGAL_CHARACTERS = { '/', '\n', '\r', '\t', '\0', '\f', '`', '?', '*', '\\', '<', '>', '|', '\"', ':' };

    public TextFile(Client client) {
        this.client = client;
    }

    static private Boolean checkIfLegalFilename(String name) {
        for (char character : ILLEGAL_CHARACTERS) {
            if (name.contains(Character.toString(character))) {
                return false;
            }
        }
        return true;
    }

    static public void createFile(String filename) throws IOException {
        if (checkIfLegalFilename(filename)) {
            System.out.print("Utwórz plik " + filename + ".txt\n");
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Błąd");
            alert.setHeaderText("Błąd");
            alert.setContentText("Podana nazwa pliku zawiera niedozwolone znaki.");
            alert.showAndWait();
        }
    }
}
