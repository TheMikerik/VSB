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
	protected boolean moving = false;
	protected double size;
	private final World world;

	private ScoreListener = new EmptyScoreListener();


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
		if(moving) {
			double x = position.getX() + (directionX * 2) * velocity;
			double y = position.getY() + (directionY * 2) * velocity;

			if (position.getX() < 20 || position.getX() > world.width-20 ) {
				this.moving = false;
				position = new Point2D((this.world.width / 2), (this.world.height / 2));
			}
			else {
				position = new Point2D((x + this.world.width) % this.world.width, (y + this.world.height) % this.world.height);
			}

			System.out.println("position: " + position);
		}
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

	public void start_moving(){
		this.moving = true;
	}
}

