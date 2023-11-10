package lab;

public final class Routines {

	private Routines() {	}
	
	public static void sleep(int timeInMilisenonds) {
		try {
			Thread.sleep(timeInMilisenonds);
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
		}
	}
	
	public static boolean isEndOfThreadRequestedByJavaVM() {
		return Thread.interrupted();
	}
}
