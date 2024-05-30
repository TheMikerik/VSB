package cz.vsb.fei.java2.lab03;

import static cz.vsb.fei.java2.lab03.EquivalenceRoutines.assertReflexivity;
import static cz.vsb.fei.java2.lab03.EquivalenceRoutines.assertSymmetry;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.MethodOrderer.OrderAnnotation;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import javafx.scene.paint.Color;

/**
 * Unit test for simple App.
 */
@TestMethodOrder(OrderAnnotation.class)
class TestEquals {

	@Test
	@Order(1)
	void testLogicEquality() {
		Point p1 = new Point(1, 2);
		Point p2 = new Point(1, 2);
		assertTrue(p1.equals(p2));

		Point p3 = new Point(1, 1);
		assertTrue(!p1.equals(p3));

		Point cp1 = new ColorPoint(1, 2, Color.BLACK);
		Point cp2 = new ColorPoint(1, 2, Color.BLACK);
		assertTrue(cp1.equals(cp2));

		Point cp3 = new ColorPoint(1, 1, Color.BLACK);
		assertTrue(!cp1.equals(cp3));

		Point cp4 = new ColorPoint(1, 2, Color.WHITE);
		assertTrue(!cp1.equals(cp4));
	}

	@Test
	@Order(2)
	void testRelfexity() {
		Point p1 = new Point(1, 2);
		assertReflexivity(p1);
	}

	@Test
	@Order(3)
	void testSymmetry() {
		Point p1 = new Point(1, 2);
		Point p2 = new Point(1, 2);
		assertSymmetry(p1, p2);

		Point p3 = new Point(1, 1);
		assertSymmetry(p1, p3);

		Point cp1 = new ColorPoint(1, 2, Color.BLACK);
		Point cp2 = new ColorPoint(1, 2, Color.BLACK);
		assertSymmetry(p1, cp2);
		assertSymmetry(cp1, cp2);

		Point cp3 = new ColorPoint(1, 1, Color.BLACK);
		assertSymmetry(p1, cp3);
		assertSymmetry(cp1, cp3);

		Point cp4 = new ColorPoint(1, 2, Color.WHITE);
		assertSymmetry(p1, cp4);
		assertSymmetry(cp1, cp4);
	}

	@Test
	@Order(4)
	void testTransitivity() {

		Point p1 = new ColorPoint(1, 2, Color.WHITE);
		Point p2 = new Point(1, 2);
		Point p3 = new ColorPoint(1, 2, Color.BLACK);
		EquivalenceRoutines.assertTransitivity(p1, p2, p3);
	}

	@Test
	@Order(5)
	void testLiskovPrinciple() {
		Point p1 = new ColorPoint(1, 2, Color.CYAN);
		Point p2 = new ColorPoint(1, 2, Color.CYAN) {

			@Override
			public String toString() {
				return "Moje barva";
			}
		};
		assertTrue(p1.equals(p2));
	}
}
