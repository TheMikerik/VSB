package cz.jezek.lab11;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.persistence.jaxb.MarshallerProperties;

import jakarta.xml.bind.JAXBContext;
import jakarta.xml.bind.JAXBException;
import jakarta.xml.bind.Marshaller;
import jakarta.xml.bind.Unmarshaller;

public class StreamMain {

  public static void main(String[] args) {
    //Tournament tournament = Tournament.generate();

    System.setProperty("jakarta.xml.bind.JAXBContextFactory", "org.eclipse.persistence.jaxb.JAXBContextFactory");


    List<Player> players = new ArrayList<Player>();
    List<Match> matches = new ArrayList<Match>();

    players.add(new Player("Jan", "Novak"));
    players.add(new Player("Pavel", "Novy"));

    matches.add(new Match(players.get(0), 5, players.get(1), 1));

    Tournament tournament = new Tournament(players, matches);

    saveToXml(tournament);

    printStatAboutTournament(tournament);

    saveTournament(tournament);
    loadTournament();

    Tournament t2 = loadFromXml();

    if(t2.getPlayers().get(0) == t2.getMatches().get(0).getOponents().getPlayer1())
    {
      System.out.println("YA");
    }
    else
    {
      System.out.println("NAY");
    }

    //json serialize
    saveToJson(tournament);


  }

  private static void saveToJson(Tournament tournament)
  {
    try {
      JAXBContext ctx = JAXBContext.newInstance(Tournament.class);
      Marshaller m = ctx.createMarshaller();
      m.setProperty(MarshallerProperties.MEDIA_TYPE, "application/json");
      m.marshal(tournament,  new java.io.File("data.json"));

    } catch (JAXBException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }

  private static void saveToXml(Tournament tournament)
  {
    try {
      JAXBContext ctx = JAXBContext.newInstance(Tournament.class);
      Marshaller m = ctx.createMarshaller();  //serializuje data
      m.marshal(tournament,new java.io.File("data.xml")); //dokonceni serializace a uzavreni do souboru
    } catch (JAXBException e) {								//Nutno udelat bud settery k serializovane metode, nebo dat k promenam anotaci @XmlElement
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }



  private static Tournament loadFromJson()
  {
    try {
      JAXBContext ctx = JAXBContext.newInstance(Tournament.class);
      Unmarshaller m = ctx.createUnmarshaller();
      return (Tournament)m.unmarshal(new java.io.File("data.json"));
    } catch (JAXBException e) {
      e.printStackTrace();
      return null;
    }
  }

  public static void printStatAboutTournament(Tournament tournament) {
    System.out.println(tournament);
    Player player = tournament.getRandomPlayer();

    System.out.println(player);
    System.out.print("Number of matches: ");
    //TODO 3.a Show the number of matches played by a given player (using Streams)

    System.out.print("Goals scored: ");
    //TODO 3.b Show the number of goals scored by a given player (help Streams)

    Oponents oponents = new Oponents(tournament.getRandomPlayer(),
            tournament.getRandomPlayer());
    System.out.println("Mutual statistics of oponents:" + oponents);

    System.out.print("Matches: ");
    //TODO 4.a List the matches played between the given players (using the stream)
    System.out.print("Number of mathes: ");
    //TODO 4.b Print the number of matches played between the given players (using the stream)
    System.out.print("Match with the largest total number:");
    //TODO 4.c Show match with the largest total number (sum of both players) scored goals between relevant players (help Streams)
  }

  public static void loadTournament() {
    //TODO 5.b Load a serialized tournament from a file
  }

  public static void saveTournament(Tournament tournament) {
    //TODO 5.a Save the tournament to a file using object serialization.
  }
}