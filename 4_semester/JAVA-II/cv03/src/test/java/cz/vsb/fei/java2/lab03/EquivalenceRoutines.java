package cz.vsb.fei.java2.lab03;

import static org.junit.jupiter.api.Assertions.assertTrue;


class EquivalenceRoutines {
	static void assertReflexivity(Object obj) {
		assertTrue(obj.equals(obj));
	}
	
	static void assertSymmetry(Object obj1, Object obj2) {
		if(obj1.equals(obj2)) {
			assertTrue(obj2.equals(obj1));
		} else {
	
			assertTrue(!obj2.equals(obj1));
		}
	}
	
	static void assertTransitivity(Object obj1, Object obj2, Object obj3) {
		if(obj1.equals(obj2) && obj2.equals(obj3)) {
			assertTrue(obj1.equals(obj3));
		} 
	}
}
