package cz.vsb.fei.java2.lab03;

import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.Stream;

import javafx.beans.binding.ObjectBinding;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.paint.Color;

public class AppController {

	private static final Random RANDOM = new Random();
	private static final List<Color> COLORS = Arrays.asList(Color.RED, Color.BLUE);

	@FXML
	private TableView<Point> table1;

	@FXML
	private TableView<Point> table2;

	private ObservableList<Point> points1 = FXCollections.observableArrayList();

	private ObservableList<Point> points2 = FXCollections.observableArrayList();

	@FXML
	public void initialize() {
		table1.setItems(points1);
		table2.setItems(points2);
		initColumns(table1);
		initColumns(table2);
		table1.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
		table2.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
		table1.getSelectionModel().selectedItemProperty()
				.addListener((ObservableValue<? extends Point> observable, Point oldValue, Point newValue) -> {
					table2.getSelectionModel().clearSelection();
					for (int i = 0; i < points2.size(); i++) {
						if (newValue != null && newValue.equals(points2.get(i))) {
							table2.getSelectionModel().select(i);
						}
					}
				});
	}

	private void initColumns(TableView<Point> tab) {
		((TableColumn<Point, Double>) tab.getColumns().get(0)).setCellValueFactory(new PropertyValueFactory<>("x"));
		((TableColumn<Point, Double>) tab.getColumns().get(1)).setCellValueFactory(new PropertyValueFactory<>("y"));
		((TableColumn<Point, Color>) tab.getColumns().get(2)).setCellValueFactory(param -> {
			if (param.getValue() instanceof ColorPoint p) {
				return new MyObservableValue<>(p.getColor());
			}
			return null;
		});
		((TableColumn<Point, Integer>) tab.getColumns().get(3))
				.setCellValueFactory(param -> new MyObservableValue<>(System.identityHashCode(param.getValue())));
	}

	@FXML
	private void generatePressed(ActionEvent event) {
		Stream.generate(this::generate).limit(10).forEach(points1::add);
		Stream.generate(this::generate).limit(6).forEach(points2::add);
		Stream.generate(() -> RANDOM.nextInt(points1.size())).limit(4).map(points1::get).forEach(points2::add);
	}

	@FXML
	private void clearPressed(ActionEvent event) {
		table2.getSelectionModel().clearSelection();
		table1.getSelectionModel().clearSelection();
		points1.clear();
		points2.clear();
	}

	private Point generate() {
		if (RANDOM.nextBoolean()) {
			return new Point(RANDOM.nextInt(2), RANDOM.nextInt(2));
		} else {
			return new ColorPoint(RANDOM.nextInt(2), RANDOM.nextInt(2), COLORS.get(RANDOM.nextInt(COLORS.size())));
		}
	}

	public static class MyObservableValue<T> extends ObjectBinding<T> {

		private T value;

		public MyObservableValue(T color) {
			this.value = color;
		}

		@Override
		public T computeValue() {
			return value;
		}

	}
}
