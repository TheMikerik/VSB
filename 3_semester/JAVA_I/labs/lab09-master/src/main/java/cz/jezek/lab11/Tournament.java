package cz.jezek.lab11;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Tournament implements Serializable {

  private List<Player> players;
  private List<Match> matches;

  public static Tournament generate() {
	// TODO 1.a Generate a list of 10 random players using the stream and then filter so that it does not contain players with the same name
	List<Player> players = Stream.
            generate(() -> Player.generateRandom())
            .limit(10)
            .collect(Collectors.toList());

    // TODO 1.b Use the stream to generate a list of 50 matches between random players (from the list of players) with a random result. Make sure the player does not play with himself.
    Random rand = new Random();
    List<Match> matches = Stream.generate(() -> new Match(
                    RandomGenerator.selectRandom(players), new Random().nextInt(50),
                    RandomGenerator.selectRandom(players), new Random().nextInt(50)))
            .filter(x -> x.getOponents().getPlayer1().equals(x.getOponents().getPlayer2()))
            .limit(50)
            .collect(Collectors.toList());


    return new Tournament(players, matches);
  }

  public Tournament(List<Player> players, List<Match> matches) {
    this.players = players;
    this.matches = matches;
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
    builder.append(
            players.stream()
                    .map(x->x.toString())
                    .collect(Collectors.joining("\n"))
    );

    builder.append("\n\nMatches:\n");
    // TODO 2.b Use the stream to add a listing of all entries to the builder. Individual matches are separated by a "\ n" character
    builder.append(
            matches.stream()
                    .map(x->x.toString())
                    .collect(Collectors.joining("\n"))
    );

    int[] a = new int[] {1,2,3,4,5,6,7};
    int tmp = Arrays.stream(a).map(x -> x * 2).sum();
    System.out.println(tmp);

    return builder.toString();
  }

}
