package cz.vsb.java1.test2;

import cz.vsb.java1.test2.helpers.RandomGenarator;

public class Vector3D {

	private String name;
	private int x;
	private int y;
	private int z;

	public static Vector3D generate() {
		return new Vector3D(RandomGenarator.generateRandomVectorName(), // name
				100 - RandomGenarator.random.nextInt(200), // X
				100 - RandomGenarator.random.nextInt(200), // Y
				100 - RandomGenarator.random.nextInt(200)); // Z
	}

	public Vector3D() {
	}

	public Vector3D(String name, int x, int y, int z) {
		this.name = name;
		this.x = x;
		this.y = y;
		this.z = z;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public int getZ() {
		return z;
	}

	public void setZ(int z) {
		this.z = z;
	}

	public double getLength() {
		return Math.sqrt(x * x + y * y + z * z);
	}

	public String nicerText() {
		return String.format("\u21A6%s(%3d, %3d, %3d)", name, x, y, z);
	}
	
	@Override
	public String toString() {
		return "Vector3D [name=" + name + ", x=" + x + ", y=" + y + ", z=" + z + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		result = prime * result + x;
		result = prime * result + y;
		result = prime * result + z;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Vector3D other = (Vector3D) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		if (x != other.x)
			return false;
		if (y != other.y)
			return false;
		if (z != other.z)
			return false;
		return true;
	}

}
