package lab;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ScoreDAO {

    public ScoreDAO() {
        init();

        insert(new Score(10, "John Doe"));
        findAll();
    }

    public void deleteScore(){
        List<Score> results = new ArrayList<>();

        String sql = "DELETE FROM score";

        try (Connection conn = getConnection()) {
            try(Statement st = conn.createStatement()) {
                st.execute(sql);
            }
        } catch (SQLException e){
            e.printStackTrace();
        }
    }

    public List<Score> findAll(){
        List<Score> results = new ArrayList<>();

        String sql = "SELECT id, score, name FROM score";

        try (Connection conn = getConnection()) {
            try(Statement st = conn.createStatement()) {

                ResultSet rs = st.executeQuery(sql);
                while(rs.next()) {
                    System.out.println(rs.getInt(1));
                    System.out.println(rs.getInt(2));
                    System.out.println(rs.getString(3));

                    results.add(new Score(rs.getInt(2), rs.getString(3)));
                }
            }
        } catch (SQLException e){
            e.printStackTrace();
        }

        return results;
    }

    public void insert(Score score){
        String sql = "INSERT INTO score (score, name) VALUES (?, ?)";

        try (Connection conn = getConnection()) {
            try(PreparedStatement ps = conn.prepareStatement(sql)) {
                ps.setInt(1, score.getScore());
                ps.setString(2, score.getName());

                ps.execute();
            }
        } catch (SQLException e){
            e.printStackTrace();
        }
    }
    private void init(){

        String sql = "CREATE TABLE score (" +
                    "id INT NOT NULL GENERATED ALWAYS AS IDENTITY," +
                    "score INT NOT NULL," +
                    "name VARCHAR(255) NOT NULL," +
                    "PRIMARY KEY (id)" +
                    ")";
        try(Connection conn = getConnection()) {
            try(Statement stmt = conn.createStatement()) {
                stmt.execute(sql);
            }
        } catch (SQLException e) {
            if(e.getSQLState().equals("X0Y32")){
                return;
            }
            e.printStackTrace();
        }
    }


    private Connection getConnection(){
        try {
            return DriverManager.getConnection(
                    "jdbc:derby:scoreDB;create=true"
            );
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }
}
