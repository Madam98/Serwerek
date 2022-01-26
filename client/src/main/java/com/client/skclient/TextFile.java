package com.client.skclient;

import javafx.scene.control.Alert;

import java.io.IOException;

public class TextFile {

    private static Client client;
    private static final char[] ILLEGAL_CHARACTERS = { '/', '\n', '\r', '\t', '\0', '\f', '`', '?', '*', '\\', '<', '>', '|', '\"', ':' };
    private String loadedText = "";
    private String filename;

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

    private void receiveFileContent() throws IOException {
        String buffer = "";
        while(!buffer.equals("EOF")) {
            buffer = client.getReader().readLine();
            if (!buffer.equals("EOF")) {
//                System.out.print(buffer + "\n");
                loadedText += buffer;
            }
        }
        System.out.print("Zakończono czytanie. Odebrano " + loadedText.length() + " znaków.\n");
    }

    public void testCreateFile() throws IOException {
        System.out.print("Testowanie odbierania pliku lorem.txt\n");
        client.getWriter().println(client.getUsername());
        client.getWriter().println("touch "+filename);
        receiveFileContent();
    }

    static public void createFile(String filename) throws IOException {
        if (checkIfLegalFilename(filename)) {
            System.out.print("Utwórz plik: touch " + filename + " " + client.getUsername());
            // touch <filename> <username>
            client.getWriter().println(client.getUsername());
            client.getWriter().println("touch "+filename);
//            client.getReader().readLine();

        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Błąd");
            alert.setHeaderText("Błąd");
            alert.setContentText("Podana nazwa pliku zawiera niedozwolone znaki.");
            alert.showAndWait();
        }
    }

    public void openFile() {
        System.out.print("Otwórz plik: open " + filename + " " + client.getUsername());
        client.getWriter().println(client.getUsername());
        client.getWriter().println("open "+filename);
//        client.getReader().readLine();
    }

    public void deleteFile(String filename) {
        System.out.print("Otwórz plik: open " + filename + " " + client.getUsername());
        client.getWriter().println(client.getUsername());
        client.getWriter().println("open "+filename);
//        client.getReader().readLine();
    }

    public void copyFile(String filename) {
        System.out.print("Otwórz plik: open " + filename + " " + client.getUsername());
        client.getWriter().println(client.getUsername());
        client.getWriter().println("open "+filename);
//        client.getReader().readLine();
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public String getFilename() {
        return this.filename;
    }

    public String getLoadedText() {
        return this.loadedText;
    }
}
