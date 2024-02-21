package org.example;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import lombok.extern.log4j.Log4j2;

/**
 *  Class <b>App</b> - extends class Application and it is an entry point of the program
 * @author     Java I
 */
@Log4j2
public class App extends Application {

	public static void main(String[] args) {
		log.info("Launching JavaFX application.");
		launch(args);
	}
	
	private AppController controller;

	@Override
	public void start(Stage primaryStage) {
		try {
			//Construct a main window with a canvas.  
			
			FXMLLoader loader = new FXMLLoader(this.getClass().getResource("AppWindow.fxml"));
			
			BorderPane root = loader.load();
			
			Scene scene = new Scene(root);
			
			
			primaryStage.setScene(scene);
			primaryStage.setTitle("Hello word app");
			primaryStage.show();
			controller = loader.getController();
			
			//Exit program when main window is closed
			primaryStage.setOnCloseRequest(this::exitProgram);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void exitProgram(WindowEvent evt) {
		System.exit(0);
	}
}