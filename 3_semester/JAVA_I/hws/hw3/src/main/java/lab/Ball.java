package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Ball {
	protected static final double SIZE = 20;

	protected Point2D position;
	protected short directionY = -1;
	protected short directionX = 1;
	protected double velocity = 1;

	public Ball(Point2D position) {
		this.position = position;
	}

	public void swap_directionY(){
		this.directionY *= -1;
	}
	public void swap_directionX(){
		this.directionX *= -1;
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), SIZE, SIZE);
		gc.restore();
	}

	public void simulate(double deltaT) {
		double x = position.getX() + (directionX * 4) * velocity;
		double y = position.getY() + (directionY * 5) * velocity;
		position = new Point2D(x, y);
	}

	protected Point2D getPosition() {
		return position;
	}
}
