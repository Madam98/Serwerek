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
        System.out.println("Zakończono czytanie. Odebrano " + loadedText.length() + " znaków.");
    }

//
//    public void testCreateFile() throws IOException {
//        System.out.print("Testowanie odbierania pliku lorem.txt\n");
//        client.getWriter().println(client.getUsername());
//        client.getWriter().println("touch:"+filename);
//        receiveFileContent();
//    }

    static public void createFile(String filename) throws IOException {
        if (checkIfLegalFilename(filename)) {
            System.out.println("Utwórz plik: touch:" + filename);
            client.getWriter().println("touch:" + filename);
        } else {
            System.out.println("Podano niedozwoloną nazwę pliku:" + filename);
        }
    }

    public void openFile() {
        System.out.println("Otwórz plik: enter:" + filename);
        client.getWriter().println("enter:"+filename);
    }

    public void deleteFile() {
        System.out.println("Usuń plik: delete:" + filename);
        client.getWriter().println("delete:"+filename);
    }

    public void copyFile() {
        System.out.println("Utwórz kopię pliku: copy:" + filename);
        client.getWriter().println("copy:"+filename);
    }

    public void renameFile(String newname) {
        System.out.println("Zmień nazwę pliku: newname:" + filename + " > " +newname);
        client.getWriter().println("newname:" + filename + " > " +newname);

        // TODO:przydałoby się jakieś potwierdzenie czy zmiana przebiegła poprawnie
        this.filename = newname;
        System.out.println("Zmieniono nazwę pliku!");
    }

    public void closeFile() {
        System.out.println("Zamknij plik: close:" + filename);
        client.getWriter().println("close:" + filename);
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
