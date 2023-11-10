package lab;

import java.util.Comparator;

public class ScoreComparator implements Comparator<Score> {

	@Override
	public int compare(Score o1, Score o2) {
		return Integer.compare(o1.getScore(), o2.getScore());
	}

}
