module cz.vsb.fei.java2.lab04 {
    requires transitive javafx.controls;
    requires javafx.fxml;
    requires static lombok;
    requires org.apache.logging.log4j;

    opens cz.vsb.fei.java2.lab04.gui to javafx.fxml,javafx.graphics;
    opens cz.vsb.fei.java2.lab04.points to javafx.base;
}