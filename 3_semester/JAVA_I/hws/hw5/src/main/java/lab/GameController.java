package lab;

import javafx.animation.AnimationTimer;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;

public class GameController {

    public Button pl1_up;
    public Button pl1_down;
    public Button pl2_up;
    public Button pl2_down;

    private World world;

    @FXML
    private Canvas canvas;

    @FXML
    private void pl1_elevate(){
        int player_index = 0;

        world.move_player(player_index, -1);
    }
    @FXML
    private void pl1_shift(){
        int player_index = 0;

        world.move_player(player_index, 1);
    }


    @FXML
    private void pl2_elevate(){
        int player_index = 1;

        world.move_player(player_index, -1);
    }
    @FXML
    private void pl2_shift(){
        int player_index = 1;

        world.move_player(player_index, 1);
    }


    @FXML
    private Button start_button;


    private AnimationTimer animationTimer;

    public GameController(){

    }

    public void startGame(){

        this.world = new World(canvas.getWidth(), canvas.getHeight());


        animationTimer = new DrawingThread(canvas, world);
        animationTimer.start();
    }

    public void stopGame(){
        animationTimer.stop();
    }


    public void start_play() {
        world.getBall().start_moving();
    }
}
