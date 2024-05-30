package cz.vsb.fei.java2.lab04.points;

import java.util.Objects;

import javafx.scene.paint.Color;

public class ColorPoint extends Point {

    private Color color;

    public ColorPoint(double x, double y, Color color) {
	super(x, y);
	this.color = color;
    }

    @Override
    public Point createCopy() {
	return new ColorPoint(getX(), getY(), color);
    }

    public Color getColor() {
	return color;
    }

    @Override
    public int hashCode() {
	return super.hashCode();
	//TODO: compute hash. Choose algorithm base on Point.hashImpl
    }

    @Override
    public boolean equals(Object obj) {
	if (this == obj)
	    return true;
	if (!super.equals(obj))
	    return false;
	if (!(obj instanceof ColorPoint))
	    return false;
	ColorPoint other = (ColorPoint) obj;
	if (!other.canEqual(this)) {
	    return false;
	}
	return Objects.equals(color, other.color);
    }

    @Override
    public boolean canEqual(Point p) {
	return p instanceof ColorPoint;
    }
}
