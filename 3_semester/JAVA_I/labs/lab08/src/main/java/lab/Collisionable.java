package lab;

import javafx.geometry.Rectangle2D;

public interface Collisionable {
	Rectangle2D getBoundingBox();
	
	default boolean intersects(Collisionable other) {
		return getBoundingBox().intersects(other.getBoundingBox());
	}
	
	void hitBy(Collisionable other);
}
