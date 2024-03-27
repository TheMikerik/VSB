package org.example;

import java.util.Objects;

class Car {
    private final String brand;
    private final String model;
    private final int year;
    private final String color;
    private final FuelType fuelType;
    private final int maxSpeed;

    public Car(String brand, String model, int year, String color, FuelType fuelType, int maxSpeed) {
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.color = color;
        this.fuelType = fuelType;
        this.maxSpeed = maxSpeed;
    }

    public static Builder builder(String brand, String model) {
        return new Builder(brand, model);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Car car = (Car) o;
        return year == car.year &&
                maxSpeed == car.maxSpeed &&
                Objects.equals(brand, car.brand) &&
                Objects.equals(model, car.model);
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((brand == null) ? 0 : brand.hashCode());
        result = prime * result + ((model == null) ? 0 : model.hashCode());
        result = prime * result + Double.hashCode(maxSpeed);
        result = prime * result + Double.hashCode(year);

        return result;
    }


    static class Builder {
        private final String brand;
        private final String model;
        private int year;
        private String color;
        private FuelType fuelType;
        private int maxSpeed;

        private Builder(String brand, String model) {
            this.brand = brand;
            this.model = model;
        }

        public Builder year(int year) {
            this.year = year;
            return this;
        }

        public Builder color(String color) {
            this.color = color;
            return this;
        }

        public Builder fuelType(FuelType fuelType) {
            this.fuelType = fuelType;
            return this;
        }

        public Builder maxSpeed(int maxSpeed) {
            this.maxSpeed = maxSpeed;
            return this;
        }

        public Car build() {
            return new Car(brand, model, year, color, fuelType, maxSpeed);
        }
    }
}
