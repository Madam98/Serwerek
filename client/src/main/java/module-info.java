module com.client.skclient {
    //requires javafx.controls;
    requires javafx.fxml;
    //requires javafx.web;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires validatorfx;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires eu.hansolo.tilesfx;

    opens com.client.skclient to javafx.fxml;
    exports com.client.skclient;
    exports com.client.skclient.controllers;
    opens com.client.skclient.controllers to javafx.fxml;
}