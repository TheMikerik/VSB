package org.example;

import java.sql.Connection;
import java.sql.SQLException;

public interface JDBCDialect {
	String getDriverClazzName();
	Connection getConnection(String dbName) throws SQLException;
	String getCreateTable();
	void handleExceptionForCreation(SQLException e);
}
