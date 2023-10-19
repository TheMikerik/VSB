package lab;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;

public class GameController {

	private World world;

	@FXML
	private Canvas canvas;

	@FXML
	private Slider leftSlider;

	@FXML
	private Slider rightSlider;

	@FXML
	private void fire(){
		world.fire();
	};

	@FXML
	Button firebtn;

	private AnimationTimer animationTimer;
	
	public GameController() {

	}
	
	public void startGame() {
		firebtn.setText("Vystrel!");

		this.world = new World(canvas.getWidth(), canvas.getHeight());

		leftSlider.valueProperty().addListener( (obj, oldValue, newValue) -> world.setCannonAngle(newValue.doubleValue()));
		rightSlider.valueProperty().addListener( (obj, oldValue, newValue) -> world.setCannonPower(newValue.doubleValue()));
//		fire.valueProperty().addListener( (obj, oldValue, newValue) -> world.setCannonPower(newValue.doubleValue()));
		//Draw scene on a separate thread to avoid blocking UI.
		animationTimer = new DrawingThread(canvas, world);
		animationTimer.start();
	}


	public void stopGame() {
		animationTimer.stop();
	}

	
}
