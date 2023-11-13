package lab;

import javafx.scene.control.Label;

public class GameListener1 implements GameListener {
    private Label shoots;

    public GameListener1(Label shoots) {
        this.shoots = shoots;
    }

    @Override
    public void stateChanged(int shoots, int hits) {
        this.shoots.setText(String.valueOf(hits));
    }

    @Override
    public void gameOver() {
        this.shoots.setText("Game Over");
    }
}
