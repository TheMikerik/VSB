package org.example;

import java.util.Objects;

class ExtendedCar extends Car {
    private final boolean fourWheelDrive;

    public ExtendedCar(String brand, String model, int year, String color, FuelType fuelType, int maxSpeed, boolean fourWheelDrive) {
        super(brand, model, year, color, fuelType, maxSpeed);
        this.fourWheelDrive = fourWheelDrive;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        ExtendedCar that = (ExtendedCar) o;
        return fourWheelDrive == that.fourWheelDrive;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), fourWheelDrive);
    }
}
