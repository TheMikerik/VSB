package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

import static java.lang.Math.floor;

public class Playground implements DrawableSimulable {
    private final World world;
    private short score1;
    private short score2;

    public Playground(World wrld){
        this.world = wrld;
        this.score1 = 0;
        this.score2 = 0;
    }

    @Override
    public void draw(GraphicsContext gc) {
        gc.setFill(Color.GRAY);
        gc.fillRect(0, 0, world.width, world.offset);
        gc.fillRect(0, world.height-world.offset, world.width, world.offset);
        double middle = floor(world.width/2) - 10;

        for(int counter = 20; counter < world.height-20; counter += 40){
            gc.fillRect(middle, counter, 20, 20);
        }

        gc.setFont(Font.font("Times New Roman", FontWeight.BOLD, 100));
        gc.fillText(String.valueOf(this.score1), middle - 90, 100);
        gc.fillText(String.valueOf(this.score2), middle + 40, 100);
    }

    @Override
    public void simulate(double deltaT) {

    }
}