package org.example;

import java.util.Objects;

class CarTest {
    public static void main(String[] args) {
        System.out.println("Unit tests:");
        testCarEquality();
        testExtendedCarEquality();
        System.out.println("Unit tests finished\n");
    }

    private static void testCarEquality() {
        Car car1 = Car.builder("Toyota", "Corolla")
                .year(2022)
                .color("Red")
                .fuelType(FuelType.PETROL)
                .maxSpeed(180)
                .build();

        Car car2 = Car.builder("Toyota", "Corolla")
                .year(2022)
                .color("Red")
                .fuelType(FuelType.PETROL)
                .maxSpeed(180)
                .build();

        boolean carsEqual = car1.equals(car2);
        System.out.println("Are cars equal? " + carsEqual);
        assert carsEqual : "Cars should be equal";
    }

    private static void testExtendedCarEquality() {
        ExtendedCar car1 = new ExtendedCar("Toyota", "Corolla", 2022, "Red",
                FuelType.PETROL, 180, true);

        ExtendedCar car2 = new ExtendedCar("Toyota", "Corolla", 2022, "Red",
                FuelType.PETROL, 180, true);

        boolean extendedCarsEqual = car1.equals(car2);
        System.out.println("Are extended cars equal? " + extendedCarsEqual);
        assert extendedCarsEqual : "Extended cars should be equal";
    }
}
