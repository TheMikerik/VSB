package lab;

import java.util.Random;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

public class World {
	
	private final static int NUMBER_OF_DRAGONS = 5;
	
	private double width;
	private double height;
	private DrawableSimulable []entities; 
	
	public World(double width, double height) {
		super();
		this.width = width;
		this.height = height;
		Cannon cannon = new Cannon(this, new Point2D(50, 50), new Point2D(100, 20));
		entities = new DrawableSimulable[2 + NUMBER_OF_DRAGONS];
		entities[0] = cannon;
		entities[1] = new BulletAnimated(this, cannon, new Point2D(30, 60), new Point2D(0, 0), 40);
		Random rnd = new Random();
		
		for (int i = 2; i < entities.length; i++) {
			int x = rnd.nextInt((int) width);
			int y = rnd.nextInt((int) height);
			int vel_x = (rnd.nextInt(10) - 5) * 10;
			int vel_y = (rnd.nextInt(10) - 5) * 10;
			entities[i] = new Dragon(this, new Point2D(x, y), new Point2D(vel_x, vel_y));
		}
	}

	public Point2D getCanvasPoint(Point2D worldPoint) {
		return new Point2D(worldPoint.getX(), height - worldPoint.getY());
	}

	public void draw(GraphicsContext gc) {
		gc.clearRect(0, 0, width, height);
		for(DrawableSimulable entity: entities) {
			entity.draw(gc);
		}
	}

	public void simulate(double timeDelta) {
		for(DrawableSimulable entity: entities) {
			entity.simulate(timeDelta);
			if (entity instanceof Collisionable) {
				Collisionable thisCollinsable = (Collisionable) entity;
				for(DrawableSimulable entity2 : entities) {
					if (entity != entity2 && entity2 instanceof Collisionable) {
						Collisionable thatCollinsable = (Collisionable) entity2;
						if (thisCollinsable.intersects(thatCollinsable)) {
							thisCollinsable.hitBy(thatCollinsable);
							thatCollinsable.hitBy(thisCollinsable);
						}
					}
				}
			}
		}
		
	}
	public void setCannonAngle(double angle){
		Cannon c = (Cannon)entities[ 0 ];
		c.setCannonAngle(angle);
	}

	public void setCannonPower(double power){
		BulletAnimated b = (BulletAnimated)entities[1];
		b.setPower(power);
	}

	public void fire() {
		BulletAnimated b = (BulletAnimated)entities[1];
		b.fire();
	}

	public double getWidth() {
		return width;
	}

	public void setWidth(double width) {
		this.width = width;
	}

	public double getHeight() {
		return height;
	}

	public void setHeight(double height) {
		this.height = height;
	}

}
