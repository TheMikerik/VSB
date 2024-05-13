package cz.vsb.fei.java2.lab04.points;

import java.util.*;

import javafx.scene.paint.Color;

public class Point {

    public static final Random RANDOM = new Random();
    private static final List<Color> COLORS = Collections.unmodifiableList(Arrays.asList(Color.RED, Color.BLUE, Color.YELLOW, Color.BLACK,
            Color.ORANGE, Color.PINK, Color.PURPLE));
    protected static HashImpl hashImpl = HashImpl.SAME;
    protected Integer hashCode = null;
    private double x;
    private double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public static void setHashImplTo(HashImpl hashImpl) {
        Point.hashImpl = hashImpl;
    }

    public static HashImpl getHashImpl() {
        return hashImpl;
    }

    public static Point generateInRange(double minX, double maxX, double minY, double maxY) {
        double x = RANDOM.nextDouble(maxX - minX) + minX;
        double y = RANDOM.nextDouble(maxY - minY) + minY;
        if (RANDOM.nextBoolean()) {
            return new Point(x, y);
        } else {
            return new ColorPoint(x, y, COLORS.get(RANDOM.nextInt(COLORS.size())));
        }

    }

    public static Point generateInRadius(Point center, double radius) {
        double angle = Math.toRadians(RANDOM.nextDouble() * 360);
        double distance = Math.sqrt(RANDOM.nextDouble()) * radius;

        double x = center.getX() + distance * Math.cos(angle);
        double y = center.getY() + distance * Math.sin(angle);

        if (RANDOM.nextBoolean()) {
            return new Point(x, y);
        } else {
            return new ColorPoint(x, y, COLORS.get(RANDOM.nextInt(COLORS.size())));
        }
    }


    public Point createCopy() {
        return new Point(x, y);
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    @Override
    public int hashCode() {
        if (hashCode != null) {
            return hashCode;
        }
        switch (hashImpl) {
            case SAME:
                return super.hashCode();
            case FULL_RANDOM:
                return RANDOM.nextInt();
            case RANDOM:
                return Objects.hash(x, y, RANDOM.nextInt());
            case STANDARD:
                return Objects.hash(x, y);
            default:
                throw new IllegalStateException("Unknown hash implementation: " + hashImpl);
        }
    }


    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (!(obj instanceof Point))
            return false;
        Point other = (Point) obj;
        if (!other.canEqual(this)) {
            return false;
        }
        return Double.doubleToLongBits(x) == Double.doubleToLongBits(other.x)
                && Double.doubleToLongBits(y) == Double.doubleToLongBits(other.y);
    }

    public boolean canEqual(Point p) {
        return p instanceof Point;
    }

    public enum HashImpl {
        SAME, FULL_RANDOM, RANDOM, STANDARD;
    }
}