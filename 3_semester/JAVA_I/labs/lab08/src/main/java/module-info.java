module lab01 {
    requires transitive javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    opens lab to javafx.fxml;
    exports lab;
}