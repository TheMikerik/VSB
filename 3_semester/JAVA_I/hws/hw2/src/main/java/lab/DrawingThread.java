package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class DrawingThread extends AnimationTimer {

	private final GraphicsContext gc;
	private final World world;
	
	private long lastTime;

	public DrawingThread(Canvas canvas) {
		this.gc = canvas.getGraphicsContext2D();
		this.world = new World(canvas.getWidth(), canvas.getHeight());
	}

	/**
	  * Draws objects into the canvas. Put you code here. 
	 */
	@Override
	public void handle(long now) {
		if (lastTime > 0) {
			double deltaT = (now - lastTime) / 1e9;
			// call simulate on world
			this.world.simulate(deltaT);
		}
		//call draw on world
		this.world.draw(gc);
		lastTime= now;

	}

}
