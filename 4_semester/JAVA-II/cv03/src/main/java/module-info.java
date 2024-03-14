module cz.vsb.fei.java2.lab03 {
    requires transitive javafx.controls;
    requires javafx.fxml;
	requires static lombok;
	requires org.apache.logging.log4j;
    opens cz.vsb.fei.java2.lab03 to javafx.fxml;
    exports cz.vsb.fei.java2.lab03;
}