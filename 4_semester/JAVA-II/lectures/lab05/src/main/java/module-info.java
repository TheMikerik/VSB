module cz.vsb.fei.java2.lab05 {
    requires transitive javafx.controls;
    requires javafx.fxml;
    opens cz.vsb.fei.java2.lab05 to javafx.fxml;
    exports cz.vsb.fei.java2.lab05;

    requires static lombok;
    requires org.apache.logging.log4j;
    
    requires jakarta.persistence;
    requires static jakarta.annotation;
    requires com.h2database;
    opens cz.vsb.fei.java2.lab05.entities;
    requires org.hibernate.orm.core;
}