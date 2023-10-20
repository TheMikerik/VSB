package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import static java.lang.Math.floor;

public class World {

	public final double width;
	public final double height;
	public final int offset;

	private final DrawableSimulable[] entities;

	public final Rectangle2D upper_barrier;
	public final Rectangle2D bottom_barrier;

	public World(double width, double height) {
		this.width = width;
		this.height = height;
		this.offset = 20;

		double player_height = 120;
		double player_width = 20;
		double ball_size = 20;

		entities = new DrawableSimulable[]{
		/*0*/		new Player(new Point2D(20, floor(height / 3)), player_width, player_height, this),
		/*1*/		new Player(new Point2D(width - 40, offset + 20), player_width, player_height, this),
		/*2*/       new Ball(new Point2D(40, 40), ball_size, this),
		/*3*/		new Playground(this)
        };

		upper_barrier = new Rectangle2D(0,0, width, offset);
		bottom_barrier = new Rectangle2D(0,height- offset, width, offset);

	}

	public void draw(GraphicsContext gc) {
		gc.save();
		gc.clearRect(0, 0, width, height);

		for(DrawableSimulable entity : entities){
			entity.draw(gc);
		}
		gc.restore();
	}

	public void drawInternal(GraphicsContext gc){

	}

	public void move_player(int index, int dir){
		for (DrawableSimulable entity : entities){
			if(entity instanceof Player player){
				if (player.player_index == index){
					player.move(dir);
				}

			}
		}
	}

	public void simulate(double deltaT) {
		for(DrawableSimulable entity : entities){
			entity.simulate(deltaT);
			if (entity instanceof Ball ball){
				for(DrawableSimulable entity2 : entities){
					if(entity2 instanceof Player player){
						ball.checkCollision(player);
					}
				}
			}
		}
	}
}
