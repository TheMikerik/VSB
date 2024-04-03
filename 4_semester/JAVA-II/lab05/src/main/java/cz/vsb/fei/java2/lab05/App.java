package cz.vsb.fei.java2.lab05;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

import org.h2.tools.Server;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import lombok.extern.log4j.Log4j2;

/**
 * Class <b>App</b> - extends class Application and it is an entry point of the
 * program
 * 
 * @author Java I
 */
@Log4j2
public class App extends Application {
    
    private static final Random RANDOM = new Random();
    private static final List<String> COURSE_NAMES = Collections
	    .unmodifiableList(Arrays.asList("Java 1", "Java 2", "C# 1", "C# 2", "Python", "Databáze I", "Databáze II",
		    "Funkcionální programování", "OOP", "PS", "APPS", "SWI"));
    private static final List<String> FIRST_NAMES = Collections
	    .unmodifiableList(Arrays.asList("Petr", "Marie", "Jan", "Jana", "Tomáš", "Kateřina", "Lukáš", "Tereza",
		    "Martin", "Veronika", "David", "Eva", "Jakub", "Lucie", "Michal", "Anna", "Adam", "Monika", "Tom",
		    "Klára", "Robert", "Kristýna", "Marek", "Simona", "Filip", "Petra", "Ondřej", "Lenka", "Matěj",
		    "Markéta", "Pavel", "Hana", "Jakub", "Adéla", "Daniel", "Barbora", "Lukáš", "Eliška", "Josef"));
    private static final List<String> LAST_NAMES = Collections.unmodifiableList(Arrays.asList("Novák", "Svoboda",
	    "Novotný", "Dvořák", "Černý", "Procházková", "Kučera", "Veselý", "Horák", "Němec", "Pokorný", "Mareš",
	    "Pospíšilová", "Hájek", "Jelínek", "Král", "Růžička", "Beneš", "Fiala", "Sedláček", "Kříž", "Němcová",
	    "Vlček", "Kolář", "Bartoš", "Bílý", "Veselá", "Kovařík", "Havelka", "Malý", "Urban", "Kopecký", "Vlach",
	    "Šimek", "Konečný", "Doležal", "Šťastný", "Kopečná", "Holub", "Pospíchal"));

    public static <T> T randomElement(List<T> list) {
	return list.get(RANDOM.nextInt(list.size()));
    }
    
    public static String randomCode() {
	return String.format("%d-%d/%02d", 400+RANDOM.nextInt(80), 2015+RANDOM.nextInt(10), 1+RANDOM.nextInt(5));
    }
    public static void main(String[] args) {
	log.info("Launching JavaFX application.");

	EntityManagerFactory emf = Persistence.createEntityManagerFactory("java2");
	EntityManager em = emf.createEntityManager();

//	launch(args);

	//Start HTTP server for access H2 DB for look inside 
	try {
	    Server server = Server.createWebServer();
	    log.info("To inspect DB go to URL: " + server.getURL());
	    server.start();
	} catch (SQLException e) {
	    e.printStackTrace();
	}

    }

    private AppController controller;

    @Override
    public void start(Stage primaryStage) {
	try {
	    // Construct a main window with a canvas.

	    FXMLLoader loader = new FXMLLoader(this.getClass().getResource("AppWindow.fxml"));

	    BorderPane root = loader.load();

	    Scene scene = new Scene(root);

	    primaryStage.setScene(scene);
	    primaryStage.setTitle("Hello word app");
	    primaryStage.show();
	    controller = loader.getController();

	    // Exit program when main window is closed
	    primaryStage.setOnCloseRequest(this::exitProgram);
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }

    private void exitProgram(WindowEvent evt) {
	System.exit(0);
    }
}