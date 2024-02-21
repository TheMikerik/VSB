module org.example {
    requires transitive javafx.controls;
    requires javafx.fxml;
    requires static lombok;
    requires org.apache.logging.log4j;
    opens org.example to javafx.fxml;
    exports org.example;
}