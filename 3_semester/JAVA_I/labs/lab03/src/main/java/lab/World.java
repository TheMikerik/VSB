package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.effect.Light;

import java.util.Random;

public class World {
	private double width;
	private double height;
	private BulletAnimated bulletAnimatted;
	private Cannon cannon;
	private Dragon dragon;
	private Dragon[] dragons = new Dragon[5];
	
	public World(double width, double height) {

//		int[] a = new int[20];
//		a[5] = 20;

		this.width = width;
		this.height = height;
		cannon = new Cannon(this, new Point2D(50, 50), new Point2D(100, 20));
		bulletAnimatted = new BulletAnimated(this, cannon, new Point2D(30, 60), new Point2D(0, 0), 40);
		dragon = new Dragon(this, new Point2D(100,150), new Point2D(20,20), 70.0);


		Random rand = new Random();

		for(int i=0; i<dragons.length; i++){
			dragons[i] = new Dragon(this,
									new Point2D(
											rand.nextInt(0, (int)width),
											rand.nextInt(0, (int)height)
										),
									new Point2D(
											rand.nextInt(-300, 300),
											rand.nextInt(-300, 300)
										),
									rand.nextInt(60, 200)
									);
			if( i % 2 == 0){
				dragons[i].position = new Point2D(
										dragons[i].position.getX() * -1,
										dragons[i].position.getY() * -1);
			}
		}
	}

	public Point2D getCanvasPoint(Point2D worldPoint, double heightOfEntity) {
		return new Point2D(worldPoint.getX(), height - worldPoint.getY() - heightOfEntity);
	}

	public void draw(GraphicsContext gc) {
		gc.clearRect(0, 0, width, height);
		cannon.draw(gc);
		bulletAnimatted.draw(gc);
		dragon.draw(gc);
		for(int i=0; i<5; i++) {
		// Slo by take zapsat syntaxem for each:
		// for(Dragon d : dragons)
			dragons[i].draw(gc);
		}
	}

	public void simulate(double timeDelta) {
		bulletAnimatted.simulate(timeDelta);
		cannon.simulate(timeDelta);
		dragon.simulate(timeDelta);
		for(int i=0; i<5; i++) {
			dragons[i].simulate(timeDelta);
		}



		Rectangle2D bulletBox = bulletAnimatted.getBoundingBox();
		for(Dragon d : dragons){
			if(d.getBoundingBox().intersects(bulletBox)){
				d.hit();
				bulletAnimatted.reload();
			}
		}
	}

	public double getWidth() {
		return width;
	}

	public double getHeight() {
		return height;
	}

}
