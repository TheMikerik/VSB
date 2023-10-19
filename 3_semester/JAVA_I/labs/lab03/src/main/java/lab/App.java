package lab;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
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
	
	private AnimationTimer timer;
	
	@Override
	public void start(Stage primaryStage) {
		try {
			//Construct a main window with a canvas.  
			Group root = new Group();
			canvas = new Canvas(800, 400);
			root.getChildren().add(canvas);
			Scene scene = new Scene(root, 800, 400);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.resizableProperty().set(false);
			primaryStage.setTitle("Java 1 - 3rd laboratory");
			primaryStage.show();
			
			//Exit program when main window is closed
			primaryStage.setOnCloseRequest(this::exitProgram);
			timer = new DrawingThread(canvas);
			timer.start();
			//Draw scene on a separate thread to avoid blocking UI.
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	private void exitProgram(WindowEvent evt) {
		System.exit(0);
	}
}