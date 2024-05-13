package table_view;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Collection;
import java.util.LinkedList;

class PersonDAO implements AutoCloseable{

	private static final String INSERT_SQL = "INSERT INTO person(first_name, last_name, email) values (?,?,?)";
	
	private static final String SELECT_SQL = "SELECT id, first_name, last_name, email FROM person";

	private static final String UPDATE_SQL = "UPDATE person set first_name = ?, last_name = ?, email = ? WHERE id = ?";

	private static final String DELETE_SQL = "DELETE FROM person WHERE id = ?";

	private Connection conn;

	private final JDBCDialect dialect;
	
	public PersonDAO(JDBCDialect dialect) {
		this.dialect = dialect;
		try {
			Class.forName(dialect.getDriverClazzName());
		} catch (ClassNotFoundException e) {
			throw new RuntimeException(e);
		}
	
		
		try {
			conn = dialect.getConnection("java1");
			constructTable();
		} catch (SQLException e) {
			dialect.handleExceptionForCreation(e);
		}
	}
	
	@Override
	public void close() throws Exception {
		checkConnection();
		conn.close();
	}

	public Person insertPerson(Person p) {
		checkConnection();
		try (PreparedStatement ps = conn.prepareStatement(INSERT_SQL, Statement.RETURN_GENERATED_KEYS)){
			ps.setString(1, p.getFirstName());
			ps.setString(2, p.getLastName());
			ps.setString(3, p.getEmail());
			ps.executeUpdate();
			ResultSet rs = ps.getGeneratedKeys();
			rs.next();
			long id = rs.getLong(1);
			return new Person(id, p);
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}

	public Collection<Person> getAll() {
		checkConnection();
		Collection<Person> result = new LinkedList<>();
		try (Statement stm = conn.createStatement()){
			stm.execute(SELECT_SQL);
			ResultSet resultSet = stm.getResultSet();
			while(resultSet.next()) {
				result.add(new Person(resultSet.getLong(1), resultSet.getString(2), resultSet.getString(3),resultSet.getString(4)));
			}
			return result;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public boolean updatePerson(Person p) {
		checkConnection();
		try (PreparedStatement ps = conn.prepareStatement(UPDATE_SQL)){
			ps.setString(1, p.getFirstName());
			ps.setString(2, p.getLastName());
			ps.setString(3, p.getEmail());
			ps.setLong(4, p.getId());
			ps.executeUpdate();
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}
	
	public boolean deletePerson(Person p) {
		checkConnection();
		try (PreparedStatement ps = conn.prepareStatement(DELETE_SQL)){
			ps.setLong(1, p.getId());
			ps.executeUpdate();
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}

	private void constructTable() throws SQLException {
		try(Statement st = conn.createStatement()) {
			st.execute(dialect.getCreateTable());
		}
	}

	private void checkConnection() {
		if (conn == null) {
			throw new IllegalStateException("Connection is not opened");
		}
	}
}
