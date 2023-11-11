package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import static java.lang.Math.floor;

public class World {

	public final double width;
	public short score1;
	public short score2;
	public final double height;
	public final int offset;
	public final double player_height;

	private final DrawableSimulable[] entities;

	private GameListener gameListener = new EmptyGameListener();

	public final Rectangle2D upper_barrier;
	public final Rectangle2D bottom_barrier;

	public World(double width, double height) {
		this.width = width;
		this.height = height;
		this.offset = 20;

		this.score1 = 0;
		this.score2 = 0;

		this.player_height = 120;
		double player_width = 20;
		double ball_size = 20;

		entities = new DrawableSimulable[]{
		/*0*/		new Player(new Point2D(20, floor(height / 3)), player_width, player_height, this, 0),
		/*1*/		new Player(new Point2D(width - 40, offset + 20), player_width, player_height, this, 1),
		/*2*/       new Ball(new Point2D(40, 40), ball_size, this),
		/*3*/		new Playground(this, score1, score2),
        };

		upper_barrier = new Rectangle2D(0,0, width, offset);
		bottom_barrier = new Rectangle2D(0,height - offset, width, offset);



	}

	public void draw(GraphicsContext gc) {
		gc.save();
		gc.clearRect(0, 0, width, height);

		for(DrawableSimulable entity : entities){
			entity.draw(gc);
		}
		gc.restore();
	}

	public Ball getBall(){
		for(DrawableSimulable entity : entities){
			if(entity instanceof Ball){
				return (Ball) entity;
			}
		}
		return null;
	}

	public void move_player(int index, int dir) {
		System.out.println("move_player called with index: " + index + ", dir: " + dir);
		for (DrawableSimulable entity : entities) {
			if (entity instanceof Player player) {
				if (player.player_index == index) {
					player.move(dir);
					System.out.println("Player " + index + " moved.\n");
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
