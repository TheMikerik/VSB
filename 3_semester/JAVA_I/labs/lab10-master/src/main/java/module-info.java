module cz.jezek.lab10 {
    opens cz.jezek.lab11 to javafx.fxml, jakarta.xml.bind;
    exports cz.jezek.lab11;
    requires jakarta.xml.bind;
    requires org.eclipse.persistence.moxy;
    requires jakarta.json;
    requires com.sun.tools.xjc;
}