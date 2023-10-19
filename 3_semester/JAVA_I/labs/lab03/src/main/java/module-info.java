module lab01 {
    requires transitive javafx.controls;
    requires javafx.fxml;
    opens lab to javafx.fxml;
    exports lab;
}