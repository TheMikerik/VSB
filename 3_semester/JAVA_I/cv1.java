package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class DrawingThread extends AnimationTimer {

	private final Canvas canvas;
	private final GraphicsContext gc;

	public DrawingThread(Canvas canvas) {
		this.canvas = canvas;
		this.gc = canvas.getGraphicsContext2D();
		
	}

	/**
	  * Draws objects into the canvas. Put you code here.
	 *
	 *
	 * https://easings.net/
	 */

	private double currentX = 0;
	private long lastTime = 0;

	@Override
	public void handle(long now) {
		/*
		double ellapsed = (now - lastTime) / 1_000_000_000.0;

		if(lastTime == 0){
			lastTime = now;
			return;
		}
		lastTime = now;
		*/

		double t = now % 2_000_000_000L; // 10mld = 10sec, 1mld = 1sec --- L = long
		t /= 2_000_000_000.0;

		double width = canvas.getWidth();
		double height = canvas.getHeight();
		double x = easeOutBounce(t) * width-325;
		double y = easeOutBounce(t) * height-50;

		gc.clearRect(0,0, width, height);

		draw(x, y, 3);
		draw(x+100, y, 1);
		draw(x+200, y, 2);
		draw(x+300, y, 3);

		// currentX += ellapsed * 50.0;

	}

	private double easeOutBounce(double x) {
		double n1 = 7.5625;
		double d1 = 2.75;

		if (x < 1 / d1) {
			return n1 * x * x;
		} else if (x < 2 / d1) {
			return n1 * (x -= 1.5 / d1) * x + 0.75;
		} else if (x < 2.5 / d1) {
			return n1 * (x -= 2.25 / d1) * x + 0.9375;
		} else {
			return n1 * (x -= 2.625 / d1) * x + 0.984375;
		}
	}

	private void draw(double x, double y, int color){
		if (color == 1){
			gc.setFill(Color.GRAY);
			gc.setStroke(Color.BLACK);
		}
		else if (color == 2){
			gc.setFill(Color.RED);
			gc.setStroke(Color.GREEN);
		}
		else {
			gc.setFill(Color.BLUE);
			gc.setStroke(Color.PURPLE);
		}

		gc.fillRect(x-25, y, 50, 50);
		gc.strokeRect(x-25, y, 50, 50);

		gc.setStroke(Color.RED);

		gc.beginPath();
		gc.moveTo(x-25, y);
		gc.lineTo(x, y-30);
		gc.lineTo(x+25, y);
		gc.stroke();
		gc.closePath();

		//gc.fillText("Muj dum", x-30, y-50);
		gc.setFont(Font.font(30));
		gc.setFont(Font.font("Times New Roman", FontWeight.BOLD, 30));
		gc.strokeText("Muj dum", x-30, y-50);

	}

}
