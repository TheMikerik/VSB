package cz.vsb.java1.test2.task;

import cz.vsb.java1.test2.Vector3D;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Task3a {
    private final Connection connection;
    private final PreparedStatement insertStmt;

    public Task3a() throws SQLException {
        this("jdbc:derby:memory:vector;create=true");
    }

    public Task3a(String connectionString) throws SQLException {
        this.connection = DriverManager.getConnection(connectionString);
        var createStmt = connection.createStatement();
        createStmt.execute("CREATE TABLE vectors (id INT NOT NULL GENERATED ALWAYS AS IDENTITY, name VARCHAR(20), x INT NOT NULL, y INT NOT NULL, z INT NOT NULL, PRIMARY KEY (id))");
        this.insertStmt = connection.prepareStatement("INSERT INTO vectors (name, x, y, z) VALUES (?, ?, ?, ?)");
    }

    public void run() throws SQLException {
        var toBeInserted = TaskUtils.generateListOfVectors();
        for (var vector : toBeInserted) {
            insertStmt.setString(1, vector.getName());
            insertStmt.setInt(2, vector.getX());
            insertStmt.setInt(3, vector.getY());
            insertStmt.setInt(4, vector.getZ());
            insertStmt.addBatch();
        }
    }

    private static class TaskUtils {
        public static List<Vector3D> generateListOfVectors() {
            return Stream.generate(Vector3D::generate).limit(13).collect(Collectors.toList());
        }
    }
}
