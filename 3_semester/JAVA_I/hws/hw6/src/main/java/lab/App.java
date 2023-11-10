package lab;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 *  Class <b>App</b> - extends class Application and it is an entry point of the program
 * @author     Java I
 */
public class App extends Application {

	public static void main(String[] args) {
		launch(args);
	}
	
	private Canvas canvas;
	private GameController controller;
	
	@Override
	public void start(Stage primaryStage) {
		try {
			//Construct a main window with a canvas.

			FXMLLoader loader = new FXMLLoader(getClass().getResource("GameGenerator.fxml"));
			BorderPane pane = loader.load();

			Scene scene = new Scene(pane);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.resizableProperty().set(false);
			primaryStage.setTitle("Java 1 - hw05");
			primaryStage.show();


			controller = loader.getController();
			controller.startGame();
			//Exit program when main window is closed
			primaryStage.setOnCloseRequest(this::exitProgram);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	@Override
	public void stop() throws Exception {
		controller.stopGame();
		super.stop();
	}
	
	private void exitProgram(WindowEvent evt) {
		System.exit(0);
	}
}