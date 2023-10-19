package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

public class BulletAnimated extends Bullet{

	private static final double SIZE = 40;
	private Image image = new Image(this.getClass().getResourceAsStream("fireball-transparent.gif"));
	
	public BulletAnimated(Point2D position, Point2D velocity, Point2D acceleration) {
		super(position, velocity, acceleration);
	}
	
	@Override
	public void draw(GraphicsContext gc) {
		gc.drawImage(image, getPosition().getX(), getPosition().getY(), SIZE, SIZE);
	}
	

}
