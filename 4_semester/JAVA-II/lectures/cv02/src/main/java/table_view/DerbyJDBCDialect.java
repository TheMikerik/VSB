package table_view;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Objects;

class DerbyJDBCDialect implements JDBCDialect{

	@Override
	public String getDriverClazzName() {
		return "org.apache.derby.jdbc.EmbeddedDriver";
	}

	@Override
	public Connection getConnection(String dbName) throws SQLException {
		return DriverManager.getConnection("jdbc:derby:" + dbName + ";create=true");
	}

	@Override
	public String getCreateTable() {
		return "CREATE TABLE  person(id int GENERATED ALWAYS AS IDENTITY, first_name varchar(64), last_name varchar(64), email varchar(64))";
	}

	@Override
	public void handleExceptionForCreation(SQLException e) {
		//table already exist
		if(Objects.equals(e.getSQLState(), "X0Y32")) {
			return;
		}
		e.printStackTrace();
	}

}
