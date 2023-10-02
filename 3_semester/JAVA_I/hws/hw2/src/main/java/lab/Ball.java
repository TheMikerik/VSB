package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Ball {
	private static final double SIZE = 20;

	protected Point2D position;
	protected short direction = -1;

	public Ball(Point2D position) {
		this.position = position;
	}

	public void swap_direction(){
		this.direction *= -1;
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), SIZE, SIZE);
		gc.restore();
	}

	public void simulate(double deltaT) {
		double x = position.getX() + 1;
		double y = position.getY() + (direction * 5);
		position = new Point2D(x, y);

//		System.out.print("x: ");
//		System.out.println(x);
//		System.out.print("y: ");
//		System.out.println(y);

	}

	protected Point2D getPosition() {
		return position;
	}
}
