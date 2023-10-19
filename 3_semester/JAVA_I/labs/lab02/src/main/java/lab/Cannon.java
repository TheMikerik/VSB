package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.Transform;

public class Cannon {

	private static final double LENGTH = 60;
	private static final double WIDTH = 15;
	private Point2D position;
	private double angle;
	
	public Cannon(Point2D position, double angle) {
		this.position = position;
		this.angle = angle;
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		gc.transform(new Affine(Transform.rotate(angle, position.getX(), position.getY())));
		gc.setFill(Color.LIGHTSTEELBLUE);
		gc.fillRect(position.getX(), position.getY(), LENGTH, WIDTH);
		gc.restore();
	}
	
	public void simulate(double deltaT) {
		//do nothing yet
		angle += 25 * deltaT;
	}
}
