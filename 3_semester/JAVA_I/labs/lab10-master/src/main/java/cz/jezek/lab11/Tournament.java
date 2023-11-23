package cz.jezek.lab11;

import jakarta.xml.bind.annotation.XmlElement;
import jakarta.xml.bind.annotation.XmlElementWrapper;
import jakarta.xml.bind.annotation.XmlRootElement;

import static cz.jezek.lab11.RandomGenerator.random;
import static cz.jezek.lab11.RandomGenerator.selectRandom;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

import java.io.Serializable;
import java.util.List;
import java.util.stream.Stream;

@XmlRootElement
public class Tournament implements Serializable{

  private static final long serialVersionUID = 1L;

  @XmlElementWrapper
  @XmlElement(name="players")
  private List<Player> players;

  @XmlElementWrapper
  @XmlElement(name="matches")
  private List<Match> matches;

  public static Tournament generate() {
	// TO DO 1.a Generate a list of 10 random players using the stream and then filter so that it does not contain players with the same name
	List<Player> players = Stream.generate(Player::generateRandom) 
								 .distinct()
								 .limit(10)
								 .collect(toList());

    // TODO 1.b Use the stream to generate a list of 50 matches between random players (from the list of players) with a random result. Make sure the player does not play with himself.
    List<Match> matches = Stream.generate(() -> generateRandomMatch(players))
    							.filter(m -> m.getOponents().getPlayer1() !=  m.getOponents().getPlayer2())
    							.limit(500)
    							.toList();


    return new Tournament(players, matches);
  }
  
  private static Match generateRandomMatch(List<Player> players) {
	  return new Match(selectRandom(players), random.nextInt(11), selectRandom(players), random.nextInt(11));
  }

  public Tournament(List<Player> players, List<Match> matches) {
    this.players = players;
    this.matches = matches;
  }

  public Tournament(){

  }


  public List<Player> getPlayers() {
    return players;
  }

  public List<Match> getMatches() {
    return matches;
  }

  public Player getRandomPlayer() {
    return RandomGenerator.selectRandom(players);
  }

  @Override
  public String toString() {
    StringBuilder builder = new StringBuilder();
    builder.append("Player count ").append(players.size())
        .append(" Match count: ").append(matches.size());
    builder.append("\n");

    builder.append("\n\nPlayers:\n");
    // TODO 2.a Use the stream to add a listing of all players to the builder. Individual players are separated by a "\ n" character
    builder.append(players.stream()
    					  .map(Object::toString)
    					  .collect(joining("\n")));

    builder.append("\n\nMatches:\n");
    // TODO 2.b Use the stream to add a listing of all entries to the builder. Individual matches are separated by a "\ n" character
    builder.append(matches.stream()
			  			  .map(Object::toString)
			  			  .collect(joining("\n")));

    return builder.toString();
  }

}
