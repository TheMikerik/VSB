package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import static java.lang.Math.floor;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

import javafx.scene.image.Image;

public class World {

	private final double width;

	private final double height;

	private final Player player1;
	private final Player player2;
	private final Ball ball;
	private final int velocity = 50;


	public World(double width, double height) {
		this.width = width;
		this.height = height;

		this.player1 = new Player(new Point2D(20, floor(height/3)));
		this.player2 = new Player(new Point2D(width - 35, floor(height/3) * 2));
//		this.ball = new Ball(new Point2D(floor(width/2) + 70, floor(height/3) - 20), new Point2D(50, 50));
		this.ball = new Ball(new Point2D(0, 0), new Point2D(velocity, velocity));
	}

	public void generate_playboard(GraphicsContext gc, int score1, int score2){
		gc.setFill(Color.GRAY);
		gc.fillRect(0, 0, width, 20);
		gc.fillRect(0, height-20, width, 20);
		double middle = floor(width/2) - 10;

		for(int offset = 20; offset < height-20; offset += 40){
			gc.fillRect(middle, offset, 20, 20);
		}

		gc.setFont(Font.font("Times New Roman", FontWeight.BOLD, 100));
		gc.fillText(String.valueOf(score1), middle - 70, 100);
		gc.fillText(String.valueOf(score2), middle + 40, 100);
	}
	public void draw(GraphicsContext gc) {

		gc.save();
		gc.clearRect(0, 0, width, height);

		this.player1.draw(gc);
		this.player2.draw(gc);
		this.ball.draw(gc);
		this.generate_playboard(gc, 4, 1);
		gc.restore();


	}

	public void simulate(double deltaT) {
		this.player1.simulate(deltaT);
		this.player2.simulate(deltaT);
		this.ball.simulate(deltaT);
	}
}
