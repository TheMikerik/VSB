package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class CarTest {

	@Test
	void testCarEquality() {
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

		assertTrue(car1.equals(car2), "Cars should be equal");
	}

	@Test
	void testExtendedCarEquality() {
		ExtendedCar car1 = new ExtendedCar("Toyota", "Corolla", 2022, "Red",
				FuelType.PETROL, 180, true);

		ExtendedCar car2 = new ExtendedCar("Toyota", "Corolla", 2022, "Red",
				FuelType.PETROL, 180, true);

		assertTrue(car1.equals(car2), "Extended cars should be equal");
	}
}