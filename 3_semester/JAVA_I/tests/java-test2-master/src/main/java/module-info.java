module cz.vsb.java1.test2 {
    opens cz.vsb.java1.test2 to jakarta.xml.bind;

    exports cz.vsb.java1.test2;
    requires java.sql;
    requires jakarta.xml.bind;
}