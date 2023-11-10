package lab;

import java.io.Serializable;

public class Score implements Serializable{
	
	private static final long serialVersionUID = 712213568495641939L;
	
	private final int score;
	private final String name;
	public Score(int score, String name) {
		super();
		this.score = score;
		this.name = name;
	}
	
	
	public String getName() {
		return name;
	}
	
	public int getScore() {
		return score;
	}

	@Override
	public String toString() {
		return name + ": " + score;
	}
	
	@Override
	public boolean equals(Object obj) {
			if (obj instanceof Score) {
				Score score = (Score) obj;
				return this.name.equals(score.name);
			}
			
			return false;
	}
	
	@Override
	public int hashCode() {
		return name.hashCode();
	}
}
