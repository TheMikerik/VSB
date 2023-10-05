package lab;

import javafx.scene.image.Image;

public final class Constants {
	private Constants() {}
	
	public static final double GRAVITATIONAL_ACCELERATION = 9.81;
	
	public static final double AIR_DENSITY = 1.2;
	
	static final int REFRESH_TIMEOUT = 25;
	
	public static final Image DRAGON_IMAGE;
	
	static{ 
		DRAGON_IMAGE = new Image(Constants.class.getResourceAsStream("dragon.gif"));
	}
}
