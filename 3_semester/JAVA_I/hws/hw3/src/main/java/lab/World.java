package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import static java.lang.Math.floor;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

import javafx.scene.image.Image;

public class World {

	private final double width;
	private final double height;

	private final double player_limit_top;
	private final double player_limit_bottom;

	private final double ball_limit_top;
	private final double ball_limit_bottom;

	private final Player player1;
	private final Player player2;
	private final Ball ball;
	private final int velocity = 100;


	public World(double width, double height) {
		this.width = width;
		this.height = height;

		this.player_limit_top = 20;
		this.player_limit_bottom = this.height - 20 - 120;

		this.ball_limit_top = 20;
		this.ball_limit_bottom = this.height - 20 - 20;

		this.player1 = new Player(new Point2D(20, floor(height/3)));
		this.player2 = new Player(new Point2D(width - 35, floor(height/3) * 2));
		this.ball = new Ball(new Point2D(40, 40));
	}

	public void generate_playboard(GraphicsContext gc, int score1, int score2){
		gc.setFill(Color.GRAY);
		gc.fillRect(0, 0, width, 20);
		gc.fillRect(0, height-20, width, 20);
		double middle = floor(width/2) - 10;

		for(int offset = 20; offset < height-20; offset += 40){
			gc.fillRect(middle, offset, 20, 20);
		}

		gc.setFont(Font.font("Times New Roman", FontWeight.BOLD, 100));
		gc.fillText(String.valueOf(score1), middle - 70, 100);
		gc.fillText(String.valueOf(score2), middle + 40, 100);
	}

	public void move_player(Player pl, GraphicsContext gc){
		if( pl.position.getY() >= player_limit_bottom || pl.position.getY() <= player_limit_top){
			pl.swap_direction();
		}
		pl.draw(gc);
	}
	public void move_ball(Ball b, GraphicsContext gc){
		if( b.position.getY() >= ball_limit_bottom || b.position.getY() <= ball_limit_top){
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
		this.ball.simulate(deltaT);

		if (ball.getPosition().getX() <= player1.position.getX() + Player.WIDTH &&
				ball.getPosition().getY() >= player1.position.getY() &&
				ball.getPosition().getY() <= player1.position.getY() + Player.HEIGHT) {
			ball.swap_directionX();
			ball.velocity *= 0.5;
		}

		if (ball.getPosition().getX() + Ball.SIZE >= player2.position.getX() &&
				ball.getPosition().getY() >= player2.position.getY() &&
				ball.getPosition().getY() <= player2.position.getY() + Player.HEIGHT) {
			ball.swap_directionX();
			ball.velocity *= 2;
		}
	}
}
