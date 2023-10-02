package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.Transform;

public class Player {

	private static final double WIDTH = 15;
	private static final double HEIGHT = 120;
	private Point2D position;
	
	public Player(Point2D position) {
		this.position = position;
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		//gc.transform(new Affine(Transform.rotate(angle, position.getX(), position.getY())));
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), WIDTH, HEIGHT);
		gc.restore();
	}
	
	public void simulate(double deltaT) {
		//do nothing yet
		this.position = new Point2D(position.getX(), position.getY() + 1);
	}
}
