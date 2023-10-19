package lab;

import javafx.scene.canvas.GraphicsContext;

public interface DrawableSimulable {
	
	void draw(GraphicsContext gc);
	
	void simulate(double deltaT);
	
}
