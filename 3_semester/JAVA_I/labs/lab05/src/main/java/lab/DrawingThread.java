package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class DrawingThread extends AnimationTimer {

	private final Canvas canvas;
	
	private final GraphicsContext gc;

	private final World world;
	
	private long lasttime = -1;

	public DrawingThread(Canvas canvas, World world) {
		this.canvas = canvas;
		this.gc = canvas.getGraphicsContext2D();
		this.world = world;
	}

	/**
	  * Draws objects into the canvas. Put you code here. 
	 */
	@Override
	public void handle(long now) {
		gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
		world.draw(gc);
		if (lasttime > 0) {
			//time are in nanoseconds and method simulate expects seconds
			world.simulate((now - lasttime) / 1e9);
		}
		lasttime = now;
	}

}
