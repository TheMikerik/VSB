package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Bullet {
	private static final double SIZE = 20;
	
	private final Point2D acceleration;
	
	private  Point2D position;
	private  Point2D velocity;
	
	
	public Bullet(Point2D position, Point2D velocity, Point2D acceleration) {
		this.position = position;
		this.velocity = velocity;
		this.acceleration = acceleration;
	}
	
	public void draw(GraphicsContext gc) {
		gc.setFill(Color.SILVER);
		gc.fillOval(position.getX(), position.getY(), SIZE, SIZE);
	}
	
	public void simulate(double deltaT) {
		position = position.add(velocity.multiply(deltaT));
		velocity = velocity.add(acceleration.multiply(deltaT));
	}

	protected Point2D getPosition() {
		return position;
	}
}
