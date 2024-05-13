module $package {
    requires transitive javafx.controls;
    requires javafx.fxml;
	requires lombok;
	requires org.apache.logging.log4j;
    opens $package to javafx.fxml;
    exports $package;
}