package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.Transform;

public class Player {

	double width;
	double height;
	protected Point2D position;
	protected short direction = -1;
	
	public Player(Point2D position, double wdth, double hght) {
		this.position = position;
		this.width = wdth;
		this.height = hght;
	}

	public void swap_direction(){
		this.direction *= -1;
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		//gc.transform(new Affine(Transform.rotate(angle, position.getX(), position.getY())));
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), width, height);
		gc.restore();
	}
	
	public void simulate(double deltaT) {
		//do nothing yet
		this.position = new Point2D(position.getX(), position.getY() + (direction * 2));
	}

	public Rectangle2D getBounding(){
		return new Rectangle2D(this.position.getX(), this.position.getY(), width, height);
	}
}
