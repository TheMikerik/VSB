package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import static java.lang.Math.floor;

public class DrawingThread extends AnimationTimer {

	private final Canvas canvas;
	private final GraphicsContext gc;

	public DrawingThread(Canvas canvas) {
		this.canvas = canvas;
		this.gc = canvas.getGraphicsContext2D();

	}


	public void generate_playboard(double width, double height, int scr1, int scr2){

		gc.setFill(Color.GRAY);
		gc.fillRect(0, 0, width, 20);
		gc.fillRect(0, height-20, width, 20);
		double middle = floor(width/2) - 10;

		for(int offset = 20; offset < height-20; offset += 40){
			gc.fillRect(middle, offset, 20, 20);
		}

		gc.setFont(Font.font("Times New Roman", FontWeight.BOLD, 100));
		gc.fillText(String.valueOf(scr1), middle - 70, 100);
		gc.fillText(String.valueOf(scr2), middle + 40, 100);
	}

	private void puck(double width, double height){
		gc.setFill(Color.WHITE);
		double x_init = floor(width/2) + 70;
		double y_init = floor(height/3) - 20;

		gc.fillRect(x_init, y_init, 15, 15);
	}
	private void player1(double height){
		gc.setFill(Color.WHITE);
		double x_init = 20;
		double y_init = floor(height/3);

		gc.fillRect(x_init, y_init, 15, 120);
	}
	private void player2(double width, double height){
		gc.setFill(Color.WHITE);
		double x_init = width - 20 - 15;
		double y_init = floor(height/3) * 2;

		gc.fillRect(x_init, y_init, 15, 120);
	}

	@Override
	public void handle(long now) {
		// put your code here
		double width = canvas.getWidth();
		double height = canvas.getHeight();
		int score_1 = 4;
		int score_2 = 1;

		generate_playboard(width, height, score_1, score_2);
		puck(width, height);
		player1(height);
		player2(width, height);
	}
}