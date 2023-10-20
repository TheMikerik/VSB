package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.Transform;

public class Player implements Collisionable, DrawableSimulable {

	double width;
	double height;
	protected Point2D position;
	private static int player_counter = 0;
	public int player_index;
	protected short direction = -1;
	private final World world;
	
	public Player(Point2D position, double wdth, double hght, World wrld) {
		this.position = position;
		this.width = wdth;
		this.height = hght;
		this.world = wrld;
		this.player_index = player_counter;

		player_index++;
	}

	public void swap_direction(){
		this.direction *= -1;
	}

	public void move(int dir){
		this.position = new Point2D(position.getX(), position.getY() + (dir * 3));
	}

	@Override
	public void draw(GraphicsContext gc) {
		if( this.getBoundingBox().intersects(world.upper_barrier) || this.getBoundingBox().intersects(world.bottom_barrier)){
			this.swap_direction();
		}

//		gc.save();
		gc.setFill(Color.WHITE);
		gc.fillRect(position.getX(), position.getY(), width, height);
//		gc.restore();
	}

	@Override
	public void simulate(double deltaT) {
//		this.position = new Point2D(position.getX(), position.getY());
	}

	@Override
	public Rectangle2D getBoundingBox(){
		return new Rectangle2D(this.position.getX(), this.position.getY(), width, height);
	}

	@Override
	public void hitBy(Collisionable that) {
		if (that instanceof Ball) {
			hit();
		}
	}

	public void hit() {
		direction *= -1;
	}
}
