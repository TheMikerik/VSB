package cz.jezek.lab11;

import jakarta.xml.bind.annotation.XmlElement;
import jakarta.xml.bind.annotation.XmlID;
import jakarta.xml.bind.annotation.XmlIDREF;

import java.util.Objects;

public class Oponents {

	@XmlElement
	@XmlIDREF
	private Player player1;
	@XmlElement
	@XmlIDREF
	private Player player2;

	public Oponents(Player player1, Player player2) {
		super();
		this.player1 = player1;
		this.player2 = player2;
	}

	public Player getPlayer1() {
		return player1;
	}

	public Player getPlayer2() {
		return player2;
	}

	public boolean contains(Player player) {
		return Objects.equals(player, player1) || Objects.equals(player, player2);
	}

	@Override
	public int hashCode() {
		int result = 1;
		result = result + ((player1 == null) ? 0 : player1.hashCode());
		result = result + ((player2 == null) ? 0 : player2.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Oponents other = (Oponents) obj;
		if (Objects.equals(player1, other.player1) && Objects.equals(player2, other.player2)) {
			return true;
		}
		if (Objects.equals(player1, other.player2) && Objects.equals(player2, other.player1)) {
			return true;
		}
		return false;
	}

	@Override
	public String toString() {
		return player1 + " vs " + player2;
	}

}
