package lab;

import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.layout.BorderPane;
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

			FXMLLoader loader = new FXMLLoader(
					getClass().getResource("GameView.fxml")
			);
			BorderPane pane = loader.load();
//			loader.load();

			// Diky FXML nepotrebuju nasledujici:
//			Group root = new Group();
//			canvas = new Canvas(800, 600);
//			root.getChildren().add(canvas);
//			Scene scene = new Scene(root);

			Scene scene = new Scene(pane);

			primaryStage.setScene(scene);
			primaryStage.resizableProperty().set(false);
			primaryStage.setTitle("Java 1 - 5th laboratory");
			primaryStage.show();
			controller = loader.getController();
			controller.startGame();
			//Exit program when main window is closed
			primaryStage.setOnCloseRequest(this::exitProgram);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	

	
	private void exitProgram(WindowEvent evt) {
		controller.stopGame();
		System.exit(0);
	}
}