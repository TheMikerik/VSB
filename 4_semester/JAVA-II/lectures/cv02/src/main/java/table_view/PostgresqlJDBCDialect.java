package table_view;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

class PostgresqlJDBCDialect implements JDBCDialect{

	@Override
	public String getDriverClazzName() {
		return "org.postgresql.Driver";
	}

	@Override
	public Connection getConnection(String dbName) throws SQLException {
		return DriverManager.getConnection("jdbc:postgresql://localhost/"+dbName,"java1","java4ever");
	}

	@Override
	public String getCreateTable() {
		return "CREATE TABLE IF NOT EXISTS person(id SERIAL PRIMARY KEY, first_name varchar(64), last_name varchar(64), email varchar(64))";
	}

	@Override
	public void handleExceptionForCreation(SQLException e)  {
		e.printStackTrace();
	}
}
