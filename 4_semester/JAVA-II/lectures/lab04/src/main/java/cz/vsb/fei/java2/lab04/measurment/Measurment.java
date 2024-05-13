package cz.vsb.fei.java2.lab04.measurment;

import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import cz.vsb.fei.java2.lab04.points.Point;

public class Measurment {

    public static InsertContainsMeasurmentResult mesure(int pointCollectionSize) {
        // Generate pointCollectionSize random points
        List<Point> pointsToInsert = Stream.generate(
                        () -> Point.generateInRange(0, 10, 0, 10))
                .limit(pointCollectionSize)
                .collect(Collectors.toList());

        // Generate 20 random points
        List<Point> pointsToTest = Stream.generate(
                        () -> Point.generateInRange(0, 10, 0, 10))
                .limit(20)
                .collect(Collectors.toList());

        // Create hash set
        Set<Point> pointsSet = new HashSet<>();

        long start = System.nanoTime();
        // Insert points to Set
        pointsSet.addAll(pointsToInsert);
        long insertDuration = (System.nanoTime() - start) / pointsToInsert.size();

        start = System.nanoTime();
        // Call method Set.contains with all points in set pointsToTest
        for (Point p : pointsToTest) {
            pointsSet.contains(p);
        }
        long containsDuration = (System.nanoTime() - start) / pointsToTest.size();

        return new InsertContainsMeasurmentResult(insertDuration, containsDuration);
    }

    public static ReleabilityMeasurmentResult mesureReleability() {
        // Generate 100 random points
        List<Point> pointsToInsert = Stream.generate(
                        () -> Point.generateInRange(0, 10, 0, 10))
                .limit(100)
                .collect(Collectors.toList());

        // Create hash set
        Set<Point> pointsSet = new HashSet<>();

        // Insert points to Set
        pointsSet.addAll(pointsToInsert);

        int countSameInstance = 0;
        int countEqualObject = 0;

        // Calculate for how many points in the list the method Set.contains method returns true (should be true for all)
        for (Point p : pointsToInsert) {
            if (pointsSet.contains(p)) {
                countSameInstance++;
            }
            if (pointsSet.contains(new Point(p.getX(), p.getY()))) {
                countEqualObject++;
            }
        }

        return new ReleabilityMeasurmentResult(countSameInstance, countEqualObject);
    }

    public record InsertContainsMeasurmentResult(long insertDuration, long containsDuration) {
    }

    public record ReleabilityMeasurmentResult(int countSameInstance, int countEqualObject) {
    }

}
