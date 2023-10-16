package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Ball {
	protected Point2D position;
	protected short directionY = -1;
	protected short directionX = 1;
	protected double velocity = 3;
	protected double size;

	public Ball(Point2D position, double sz) {
		this.position = position;
		this.size = sz;
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
		gc.fillRect(position.getX(), position.getY(), size, size);
		gc.restore();
	}

	public void simulate(double deltaT, World world) {
		double x = position.getX() + (directionX * 4) * velocity;
		double y = position.getY() + (directionY * 5) * velocity;
		position = new Point2D(
				(x + world.width) % world.width,
				(y + world.height) % world.height);
		System.out.println(velocity);
	}

	protected Point2D getPosition() {
		return position;
	}

	public Rectangle2D getBoundingBox(){
		return new Rectangle2D(this.position.getX(), this.position.getY(), size, size);
	}
	public void hit(){
		this.velocity *= -1;
		this.swap_directionY();
	}
}

