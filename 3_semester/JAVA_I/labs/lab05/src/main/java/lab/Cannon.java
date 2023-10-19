package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;

public class Cannon implements DrawableSimulable {

	private int direction=-1;
	private double angle = 0;
	private Point2D position;
	private Point2D size;
	private World world;
	
	
	 

	public Cannon(World world, Point2D position, Point2D size) {
		super();
		this.world = world;
		this.position = position;
		this.size = size;
	}

	public void simulate(double timeStep) {
//		angle = angle + direction*0.8;
//		if(angle <=-90 || angle >= 0) {
//			direction*=-1;
//		}
	}
	
	public void draw(GraphicsContext gc) {
		gc.save();
		Point2D worldPosition = world.getCanvasPoint(position);
		gc.setFill(Color.BROWN);
		gc.fillRect(worldPosition.getX()-10, worldPosition.getY()+size.getY(), size.getX()+20, size.getY()/2);
		gc.fillOval(worldPosition.getX()-20, worldPosition.getY()+size.getY()/2, 40, 40);
		gc.fillOval(worldPosition.getX()+size.getX(), worldPosition.getY()+size.getY()/2, 40, 40);
		gc.setTransform(new Affine(Affine.rotate(angle, worldPosition.getX(), worldPosition.getY()+size.getY()/2)));
		gc.setFill(Color.BLACK);
		gc.fillRect(worldPosition.getX(), worldPosition.getY(), size.getX(), size.getY());
		gc.restore();
	}

	public void setCannonAngle(double angle){
		this.angle = -angle;
	}

	public double getAngle() {
		return (angle * -1) / 180 * Math.PI;
	}
}
