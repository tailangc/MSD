module com.example.synthesizerc {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.synthesizerc to javafx.fxml;
    exports com.example.synthesizerc;
}