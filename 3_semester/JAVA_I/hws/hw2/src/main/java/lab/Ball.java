package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Ball {
	private static final double SIZE = 15;

	private  Point2D position;
	private  Point2D velocity;


	public Ball(Point2D position, Point2D velocity) {
		this.position = position;
		this.velocity = velocity;
	}

	public void draw(GraphicsContext gc) {
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), SIZE, SIZE);
	}

	public void simulate(double deltaT) {
		position = position.add(velocity.multiply(deltaT));
	}

	protected Point2D getPosition() {
		return position;
	}
}
