package lab;

import javafx.scene.control.Label;

public class GameListener1 implements GameListener{
    private Label scores;

    @Override
    public void update(int score) {
        scores.setText(String.valueOf(score));
    }

    @Override
    public void gameOver() {
        this.scores.setText("GAME OVER");
    }

}
