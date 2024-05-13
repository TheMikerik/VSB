module org.example {
    requires transitive javafx.controls;
    requires javafx.fxml;
	requires lombok;
	requires org.apache.logging.log4j;
    requires java.sql;
    opens org.example to javafx.fxml;
    exports org.example;
    requires JDBC_dia;
    provides JDBCDialect with DerbyJDBCDialect;
}