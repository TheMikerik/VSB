package cz.jezek.lab11;

import jakarta.xml.bind.annotation.XmlAttribute;
import jakarta.xml.bind.annotation.XmlElement;

import java.util.Objects;

public class Match {

	@XmlElement
	private Oponents oponents;

	@XmlAttribute
	private int player1Scorel;

	@XmlAttribute
	private int player2Scorel;


	public Match(){}

	public Match(Player player1, int player1Scorel, Player player2, int player2Scorel) {
		this.oponents = new Oponents(player1, player2);
		this.player1Scorel = player1Scorel;
		this.player2Scorel = player2Scorel;
	}

	public int getScoreForPlayer(Player player) {
		if (Objects.equals(player, oponents.getPlayer1())) {
			return player1Scorel;
		} else if (Objects.equals(player, oponents.getPlayer2())) {
			return player2Scorel;
		}
		throw new IllegalArgumentException("Player is not participant of this match.");
	}

	public Oponents getOponents() {
		return oponents;
	}

	public int getPlayer1Scorel() {
		return player1Scorel;
	}

	public int getPlayer2Scorel() {
		return player2Scorel;
	}

	@Override
	public String toString() {
		return String.format("Match: %s score: %02d:%02d", oponents, player1Scorel, player2Scorel);
	}

}
