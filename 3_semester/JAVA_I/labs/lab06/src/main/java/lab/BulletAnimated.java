package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

public class BulletAnimated  implements DrawableSimulable, Collisionable{

	private static final double STRENGTH_CANNON_COEFICIENT = 1.;
	
	private Point2D position;
	private Point2D start;
	private Point2D speed;
	private Point2D initialSpeed;
	private double size;
	private double mass = 2;
	private double cannonLength = 100;
	private boolean accelerate = false;
	private boolean hitToGround = false;

	private double crossSectionalArea;
	private double dragCoefficient = 0.47;
	
	private Image image;
	private World world;
	private Cannon cannon;
	private boolean fired;

	private HitListener hitListener = new EmptyHitListener();
	
	public BulletAnimated(World world, Cannon cannon) {
		this(world, cannon, new Point2D(0, 0), new Point2D(0, 0), 10);
	}

	public BulletAnimated(World world, Cannon cannon, Point2D start, Point2D speed, double size) {
		this.start = start;
		this.position = this.start;
		this.initialSpeed = Point2D.ZERO;
		this.speed = speed;
		this.size = size;
		this.world = world;
		this.cannon = cannon;
		image = new Image(getClass().getResourceAsStream("fireball-transparent.gif"), size, size,
				true, true);
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		Point2D canvasPosition = world.getCanvasPoint(position);
		gc.drawImage(image, canvasPosition.getX(), canvasPosition.getY());
		gc.restore();
	}

	public void simulate(double deltaT) {
		if (!fired) {
			return;
		}
		if (accelerate && start.distance(position) < cannonLength) {
			double cannonAngle = cannon.getAngle(); 
			double strenghtOfCannon = cannon.getStrength() * STRENGTH_CANNON_COEFICIENT;
			speed = speed
					.add(new Point2D(Math.cos(cannonAngle) * strenghtOfCannon, Math.sin(cannonAngle) * strenghtOfCannon)
							.multiply(deltaT / mass));
		} else if (!hitToGround) {
			accelerate = false;
			Point2D airResistanceforce = new Point2D(
					-1. / 2 * crossSectionalArea * Constants.AIR_DENSITY * dragCoefficient * Math.pow(speed.getX(), 2),
					-1. / 2 * crossSectionalArea * Constants.AIR_DENSITY * 0.47 * Math.pow(speed.getY(), 2));
			Point2D acceleration = new Point2D(-airResistanceforce.getX() * mass,
					(-Constants.GRAVITATIONAL_ACCELERATION + airResistanceforce.getY()) * mass);
			speed = speed.add(acceleration.multiply(deltaT));
		}
		if (!hitToGround) {
			position = position.add(speed.multiply(deltaT*100));
			if (!accelerate && position.getY() <= size / 2) {
				hitToGround = true;
				position = new Point2D(position.getX(), size / 2);
			}
		} else {
			reload();
		}
		
	}

	public Rectangle2D getBoundingBox() {
		return new Rectangle2D(position.getX() - size, position.getY(), size, size);
	}
	
	public boolean overlaps(Dragon dragon) {
		return getBoundingBox().intersects(dragon.getBoundingBox());
	}
	
	public void hitBy(Collisionable other) {
		hitListener.hit();
		reload();
	}
	
	public void reload() {
		position = start;
		speed = Point2D.ZERO;
		hitToGround = false;
		accelerate = false;
		fired = false;
	}

	public void fire() {
		if (fired) {
			return;
		}
		fired = true;
		accelerate = true;
		speed = initialSpeed;
	}
	
	public void setHitListener(HitListener hitListener) {
		this.hitListener = hitListener;
	}
	
}
