package table_view;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableColumn.CellEditEvent;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class TableViewSample extends Application {

	private final PersonDAO dao;

	private TableView<Person> table = new TableView<>();

	private final ObservableList<Person> data;

	final GridPane gridPane = new GridPane();
	private TextField addFirstName;
	private TextField addLastName;
	private TextField addEmail;

	public static void main(String[] args) {
		launch(args);
	}

	public TableViewSample() {
		dao = new PersonDAO(new DerbyJDBCDialect());
		data = FXCollections.observableArrayList(dao.getAll());
	}

	@SuppressWarnings("unchecked")
	@Override
	public void start(Stage stage) {
		Scene scene = new Scene(new Group());
		stage.setTitle("Table View Sample");
		stage.setWidth(450);
		stage.setHeight(550);

		final Label label = new Label("Address Book");
		label.setFont(new Font("Arial", 20));

		table.setEditable(true);
		table.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY_ALL_COLUMNS);
		table.setItems(data);

		TableColumn<Person, String> firstNameCol = constructColumn("First Name", "firstName",
				this::handleOnEditCommitFirstName);
		TableColumn<Person, String> lastNameCol = constructColumn("Last Name", "lastName",
				this::handleOnEditCommitLastName);
		TableColumn<Person, String> emailCol = constructColumn("Email", "email", this::handleOnEditCommitEmail);
		table.getColumns().addAll(firstNameCol, lastNameCol, emailCol);

		addFirstName = constructTextField("First Name");
		addLastName = constructTextField("Last Name");
		addEmail = constructTextField("Email");
		final Button addButton = new Button("Add");
		addButton.setMinWidth(Region.USE_PREF_SIZE);
		addButton.setOnAction(this::handleOnAdd);

		gridPane.add(addFirstName, 0, 0);
		gridPane.add(addLastName, 1, 0);
		gridPane.add(addEmail, 2, 0);
		gridPane.add(addButton, 3, 0);
		GridPane.setHgrow(addFirstName, Priority.ALWAYS);
		GridPane.setHgrow(addLastName, Priority.ALWAYS);
		GridPane.setHgrow(addEmail, Priority.ALWAYS);
		GridPane.setHgrow(addButton, Priority.NEVER);
		gridPane.setHgap(5);
		GridPane.setFillWidth(addButton, true);

		final BorderPane borderPane = new BorderPane();
		borderPane.setTop(label);
		BorderPane.setMargin(label, new Insets(10));
		BorderPane.setAlignment(label, Pos.CENTER);

		borderPane.setCenter(table);
		BorderPane.setMargin(table, new Insets(10));

		borderPane.setBottom(gridPane);
		BorderPane.setMargin(gridPane, new Insets(10));

		scene.setRoot(borderPane);
		stage.setScene(scene);

		stage.show();
		stage.setOnCloseRequest(this::exitProgram);
	}

	private TextField constructTextField( String string) {
		TextField result = new TextField();
		result.setPromptText(string);
		return result;
	}

	private TableColumn<Person, String> constructColumn(String name, String propertyName,
			EventHandler<CellEditEvent<Person, String>> callback) {
		TableColumn<Person, String> col = new TableColumn<>(name);
		col.setMinWidth(100);
		col.setCellValueFactory(new PropertyValueFactory<>(propertyName));
		col.setCellFactory(TextFieldTableCell.forTableColumn());
		col.setOnEditCommit(callback);
		return col;
	}

	private void handleOnAdd(ActionEvent e) {
		Person p = new Person(addFirstName.getText(), addLastName.getText(), addEmail.getText());
		p = dao.insertPerson(p);
		data.add(p);
		addFirstName.clear();
		addLastName.clear();
		addEmail.clear();
	}

	private void handleOnEditCommitFirstName(CellEditEvent<Person, String> t) {
		Person p = t.getTableView().getItems().get(t.getTablePosition().getRow());
		p.setFirstName(t.getNewValue());
		dao.updatePerson(p);
	}

	private void handleOnEditCommitLastName(CellEditEvent<Person, String> t) {
		Person p = t.getTableView().getItems().get(t.getTablePosition().getRow());
		p.setLastName(t.getNewValue());
		dao.updatePerson(p);
	}

	private void handleOnEditCommitEmail(CellEditEvent<Person, String> t) {
		Person p = t.getTableView().getItems().get(t.getTablePosition().getRow());
		p.setEmail(t.getNewValue());
		dao.updatePerson(p);
	}

	private void exitProgram(WindowEvent evt) {
		try {
			dao.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.exit(0);
	}
}