package cz.vsb.fei.java2.lab03;

import javafx.scene.paint.Color;

public class ColorPoint extends Point {

	private Color color;

	public ColorPoint(double x, double y, Color color) {
		super(x, y);
		this.color = color;
	}

	public Color getColor() {
		return color;
	}

}
