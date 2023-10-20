package lab;

import javafx.geometry.Rectangle2D;

public interface Collisionable {
    Rectangle2D getBoundingBox();

    void hitBy(Collisionable that);

    default void checkCollision(Object obstacle){
        if (obstacle instanceof Collisionable obs && this.getBoundingBox().intersects(obs.getBoundingBox())){
            this.hitBy(obs);
        }
    }
}

