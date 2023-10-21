package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Ball implements DrawableSimulable, Collisionable  {
	protected Point2D position;
	protected short directionY = -1;
	protected short directionX = 1;
	protected double velocity = 1;
	protected double size;
	private final World world;


	public Ball(Point2D position, double sz, World wrld) {
		this.position = position;
		this.size = sz;
		this.world = wrld;
	}

	public void swap_directionY(){
		this.directionY *= -1;
	}

	@Override
	public void draw(GraphicsContext gc) {
		if( this.getBoundingBox().intersects(world.upper_barrier) || this.getBoundingBox().intersects(world.bottom_barrier)){
			this.swap_directionY();
		}

//		gc.save();
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), size, size);
//		gc.restore();
	}

	@Override
	public void simulate(double deltaT) {
		double x = position.getX() + (directionX * 4) * velocity;
		double y = position.getY() + (directionY * 5) * velocity;
		position = new Point2D((x + this.world.width) % this.world.width, (y + this.world.height) % this.world.height);
	}

	@Override
	public Rectangle2D getBoundingBox(){
		return new Rectangle2D(this.position.getX(), this.position.getY(), size, size);
	}

	@Override
	public void hitBy(Collisionable obstacle) {
		hit();
	}

	public void hit(){
		this.velocity *= -1;
		this.swap_directionY();
	}
}

