package lab;

public interface GameListener {
	
	void stateChanged(int shoots, int hits);
	
	void gameOver();
}
