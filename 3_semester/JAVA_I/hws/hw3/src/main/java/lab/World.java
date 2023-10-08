package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import static java.lang.Math.floor;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

import javafx.scene.image.Image;

public class World {

	public final double width;
	public final double height;

	private final int offset = 20;
	private final double ball_size = 20;

	private final Player player1;
	private final Player player2;
	private final Ball ball;

	private final Rectangle2D upper_barrier;
	private final Rectangle2D bottom_barrier;

	public World(double width, double height) {
		this.width = width;
		this.height = height;

		double player_height = 120;
		double player_width = 20;

		this.player1 = new Player(new Point2D(20, floor(height/3)), player_width, player_height);
		this.player2 = new Player(new Point2D(width - 40, floor(height/3) * 2), player_width, player_height);
		this.ball = new Ball(new Point2D(40, 40), ball_size);

		upper_barrier = new Rectangle2D(0,0, width, offset);
		bottom_barrier = new Rectangle2D(0,height-offset, width, offset);
	}

	public void generate_playboard(GraphicsContext gc, int score1, int score2){
		gc.setFill(Color.GRAY);
		gc.fillRect(0, 0, width, offset);
		gc.fillRect(0, height-offset, width, offset);
		double middle = floor(width/2) - 10;

		for(int counter = 20; counter < height-20; counter += 40){
			gc.fillRect(middle, counter, 20, 20);
		}

		gc.setFont(Font.font("Times New Roman", FontWeight.BOLD, 100));
		gc.fillText(String.valueOf(score1), middle - 70, 100);
		gc.fillText(String.valueOf(score2), middle + 40, 100);
	}

	public void move_player(Player pl, GraphicsContext gc){
		if( pl.getBounding().intersects(upper_barrier) || pl.getBounding().intersects(bottom_barrier)){
			pl.swap_direction();
		}
		pl.draw(gc);
	}
	public void move_ball(Ball b, GraphicsContext gc){
		if( b.getBoundingBox().intersects(upper_barrier) || b.getBoundingBox().intersects(bottom_barrier)){
			b.swap_directionY();
		}
		b.draw(gc);
	}
	public void draw(GraphicsContext gc) {

		gc.save();
		gc.clearRect(0, 0, width, height);

		this.move_player(player1, gc);
		this.move_player(player2, gc);
		this.move_ball(ball, gc);
		this.generate_playboard(gc, 4, 1);
		gc.restore();


	}

	public void simulate(double deltaT) {
		this.player1.simulate(deltaT);
		this.player2.simulate(deltaT);
		this.ball.simulate(deltaT, this);

		Rectangle2D player1_bb = this.player1.getBounding();
		Rectangle2D player2_bb = this.player2.getBounding();

		if ( ball.getBoundingBox().intersects(player1_bb) ){
			ball.hit();
		}
		if ( ball.getBoundingBox().intersects(player2_bb) ){
			ball.hit();
		}
	}
}
