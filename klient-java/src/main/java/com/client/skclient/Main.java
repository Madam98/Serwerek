package com.client.skclient;

import com.client.skclient.controllers.LogInController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    private Stage stage;
    private Scene scene;
    private Parent root;
    private Client client;

    @Override
    public void start(Stage startingStage) throws IOException {
        client = new Client();
        stage = startingStage;

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
        root = fxmlLoader.load();
        LogInController logInController = fxmlLoader.getController();
        logInController.initialize(client, stage);

        scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Współbieżny edytor tekstu");
        stage.sizeToScene();
        stage.show();
    }

    public static void main(String[] args) { launch(args); }


}


//public class Main {
//
//        private int j;
//
//        public static void main(String[] args) {
//            com.client.skclient.Main Main = new com.client.skclient.Main();
//            for(int i=0;i<2;i++){
//                new Thread(Main.new ShareData1()).start();//Increase
//                new Thread(Main.new ShareData2()).start();//Reduce
//            }
//        }
//        //Increase
//        private synchronized void Inc(){
//            j++;
//            System.out.println(Thread.currentThread().getName()+" inc "+j);
//        }
//        // decrement
//        private synchronized void Dec(){
//            j--;
//            System.out.println(Thread.currentThread().getName()+" dec "+j);
//        }
//
//        class ShareData1 implements Runnable {
//            public void run() {
//                for(int i=0;i<5;i++){
//                    Inc();
//                }
//            }
//        }
//        class ShareData2 implements Runnable {
//            public void run() {
//                for(int i=0;i<5;i++){
//                    Dec();
//                }
//            }
//        }
//
//    }
