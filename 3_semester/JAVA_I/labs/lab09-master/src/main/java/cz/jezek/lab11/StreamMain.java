package cz.jezek.lab11;

import java.io.*;
import java.util.Comparator;

public class StreamMain implements Serializable {

  public static void main(String[] args) {
    Tournament tournament = Tournament.generate();

    printStatAboutTournament(tournament);

    saveTournament(tournament);
    loadTournament();
  }

  public static void printStatAboutTournament(Tournament tournament) {
    System.out.println(tournament);
    Player player = tournament.getRandomPlayer();

    System.out.println(player);
    System.out.print("Number of matches: ");
    //TODO 3.a Show the number of matches played by a given player (using Streams)

    long count = tournament.getMatches().stream().filter(x -> x.getOponents().contains(player)).count();
    System.out.println(count);

    
    System.out.print("Goals scored: ");
    //TODO 3.b Show the number of goals scored by a given player (help Streams)

    long sum = tournament.getMatches().stream().filter(x -> x.getOponents().contains(player))
            .map(x -> x.getScoreForPlayer(player))
            .mapToInt(x -> x).sum();
    System.out.println(sum);

    Oponents oponents = new Oponents(tournament.getRandomPlayer(),
        tournament.getRandomPlayer());
    System.out.println("Mutual statistics of oponents:" + oponents);
    
    System.out.print("Matches: ");
    //TODO 4.a List the matches played between the given players (using the stream)

     tournament.getMatches().stream().filter(x -> x.getOponents().equals(oponents)).
             forEach(x -> System.out.println(x.toString()));


    System.out.print("Number of mathes: ");
    //TODO 4.b Print the number of matches played between the given players (using the stream)

    long count2 = tournament.getMatches().stream()
            .filter(x -> x.getOponents().equals(oponents))
            .count();

    System.out.println(count2);



    System.out.print("Match with the largest total number:");
    //TODO 4.c Show match with the largest total number (sum of both players) scored goals between relevant players (help Streams)

    String name = tournament.getMatches()
            .stream()
            .max(Comparator.comparingInt(x -> x.getPlayer1Scorel() + x.getPlayer1Scorel()))
            .map(x -> x.toString())
            .orElse("Match was not found");

    System.out.println(name);
  }

  public static void loadTournament() {
    //TODO 5.b Load a serialized tournament from a file
    try(ObjectInputStream is = new ObjectInputStream(new FileInputStream("data.obj")))
    {
      Tournament tournament = (Tournament)is.readObject();
      System.out.println(tournament);
    }
    catch(IOException e)
    {
      e.printStackTrace();
    }
    catch(ClassNotFoundException e)
    {
      e.printStackTrace();
    }
  }

  public static void saveTournament(Tournament tournament) {
    //TODO 5.a Save the tournament to a file using object serialization.
    try(ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream("data.obj")))
    {
      os.writeObject(tournament);
    }
    catch(IOException e)
    {
      e.printStackTrace();
    }


  }



  }
}
