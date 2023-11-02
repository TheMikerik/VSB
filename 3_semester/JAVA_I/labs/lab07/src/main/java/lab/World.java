package lab;

import java.util.Random;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

public class World {
	
	private final static int NUMBER_OF_DRAGONS = 2;
	
	private double width;
	private double height;
	
	private GameListener gameListener = new EmptyGameListener();
	
	private int hits = 0;
	
	private int shoots = 0;
	
	private DrawableSimulable []entities; 
	
	public World(double width, double height) {
		super();
		this.width = width;
		this.height = height;
		Cannon cannon = new Cannon(this, new Point2D(50, 50), new Point2D(100, 20));
		entities = new DrawableSimulable[2 + NUMBER_OF_DRAGONS];
		entities[0] = cannon;
		entities[1] = new BulletAnimated(this, cannon, new Point2D(30, 60), new Point2D(0, 0), 40);
		((BulletAnimated)entities[1]).setHitListener(this::hitOfBullet);
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
		gc.clearRect(0, 0, getWidth(), getHeight());
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

	public void setCannonAngle(double doubleValue) {
		for (DrawableSimulable d: entities) {
			if (d instanceof Cannon) {
				Cannon cannon = (Cannon) d;
				cannon.setAngle(doubleValue);
			}
		}
		
	}
	
	public void setCannonStrength(double doubleValue) {
		for (DrawableSimulable d: entities) {
			if (d instanceof Cannon) {
				Cannon cannon = (Cannon) d;
				cannon.setStrength(doubleValue);
			}
		}
		
	}

	public void fire() {
		for (DrawableSimulable e: entities) {
			if (e instanceof BulletAnimated) {
				BulletAnimated ba = (BulletAnimated) e;
				ba.fire();
				shoots++;
				gameListener.stateChanged(shoots, hits);
				if (shoots > 10) {
					gameListener.gameOver();
				}
			}
		}
	}

	public void setGameListener(GameListener gameListenerImpl) {
		this.gameListener = gameListenerImpl;
		
	}
	
	private void hitOfBullet() {
		hits++;
		gameListener.stateChanged(shoots, hits);
	}
	
}
