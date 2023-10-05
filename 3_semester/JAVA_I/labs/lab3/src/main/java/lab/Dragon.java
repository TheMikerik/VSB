package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.image.Image;

public class Dragon {
    private Image img = lab.Constants.DRAGON_IMAGE;
    private double size;
    protected Point2D position;
    private static Point2D velocity;
    private World world;

    public Dragon(World world, Point2D position, Point2D velocity, Double size){
        this.world = world;
        this.position = position;
        this.velocity = velocity;
        this.size = size;
    }
    public void simulate(double deltaT){
        position = position.add(velocity.multiply(deltaT));

        position = new Point2D(
                (position.getX() + world.getWidth())% world.getWidth(),
                (position.getY() + world.getHeight()) % world.getHeight()
        );
    }

    public void draw(GraphicsContext gc){
        //gc.save(); //--> save a restore se pouziva pro rotaci, kdy se toci scena -> restore ji pak navrati do puvodniho stavu
        Point2D tmp = world.getCanvasPoint(position, size); //------- getCanvas->pocita x a y od leva od dola
        gc.drawImage(img, tmp.getX(), tmp.getY(), size, size);
        //gc.restore();
    }

    // Metoda boundixbox = nejmensi mozny ctverec, ktery lze nakreslit okolo obrazce -> pocitame z nej hit (prunik)
    public Rectangle2D getBoundingBox(){
        return new Rectangle2D(this.position.getX(), this.position.getY(), this.size, this.size);
    };

    public void hit(){
        velocity = velocity.multiply(-1);
    }
}
