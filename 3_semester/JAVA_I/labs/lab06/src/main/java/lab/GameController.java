	package lab;

import javafx.animation.AnimationTimer;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;

public class GameController {

	private World world;
	
	@FXML
	private Slider angleSlider;
	
	@FXML
	private Slider strengthSlider;
	
	@FXML
	private Canvas canvas;
	
	@FXML
	private Label shoots;
	
	@FXML
	private Label hits;
	
	private AnimationTimer animationTimer;

	class GameListener2 implements GameListener {

		@Override
		public void stateChanged(int shoots, int hits) {
			GameController.this.shoots.setText(shoots + "");
		}

		@Override
        public void gameOver() {
            GameController.this.shoots.setText("Game Over");
        }
	}
	
	public GameController() {
	}
	
	public void startGame() {
		this.world = new World(canvas.getWidth(), canvas.getHeight());	
		//Draw scene on a separate thread to avoid blocking UI.
		animationTimer = new DrawingThread(canvas, world);
		angleSlider.valueProperty().addListener(this::angleChanged);
		world.setCannonAngle(angleSlider.getValue());
		
		strengthSlider.valueProperty().addListener(this::strenghtChanged);
		world.setCannonStrength(strengthSlider.getValue());
		animationTimer.start();

		world.setGameListener(new GameListener(){

			@Override
            public void stateChanged(int shoots, int hits) {
                GameController.this.hits.setText(hits + "");
				GameController.this.shoots.setText(shoots + "");
            }

			@Override
            public void gameOver() {
                GameController.this.hits.setText("Game Over");
            }
		});
	}


	public void stopGame() {
		animationTimer.stop();
	}
	
	@FXML
	private void firePressed() {
		world.fire();
	}
	
	
	private void angleChanged(ObservableValue<? extends Number> observable
								, Number oldValue, Number newValue) {
		world.setCannonAngle(newValue.doubleValue());
	}

	private void strenghtChanged(ObservableValue<? extends Number> observable
			, Number oldValue, Number newValue) {
		world.setCannonStrength(newValue.doubleValue());
	}
}
