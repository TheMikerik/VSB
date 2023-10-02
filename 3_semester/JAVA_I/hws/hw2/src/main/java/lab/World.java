package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import static java.lang.Math.floor;
import javafx.scene.image.Image;

public class World {

	private final double width;

	private final double height;

	private final Player player1;
	private final Player player2;
	private final Ball ball;


	public World(double width, double height) {
		this.width = width;
		this.height = height;

		this.player1 = new Player(new Point2D(20, floor(height/3)));
		this.player2 = new Player(new Point2D(width - 35, floor(height/3) * 2));
		this.ball = new Ball(new Point2D(floor(width/2) + 70, floor(height/3) - 20), new Point2D(30, 30));
	}

	public void draw(GraphicsContext gc) {
		this.player1.draw(gc);
		this.player2.draw(gc);
		this.ball.draw(gc);
		gc.restore();
	}

	public void simulate(double deltaT) {
		this.player1.simulate(deltaT);
		this.player2.simulate(deltaT);
		this.ball.simulate(deltaT);
	}
}
