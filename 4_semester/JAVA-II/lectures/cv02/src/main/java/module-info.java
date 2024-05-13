module lab01 {
    requires transitive javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    opens table_view to javafx.fxml;
    exports table_view;
    uses JVDCDialect;
}