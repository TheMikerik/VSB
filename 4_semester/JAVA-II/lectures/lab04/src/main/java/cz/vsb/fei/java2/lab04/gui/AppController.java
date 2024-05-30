package cz.vsb.fei.java2.lab04.gui;

import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import cz.vsb.fei.java2.lab04.measurment.Measurment;
import cz.vsb.fei.java2.lab04.measurment.Measurment.InsertContainsMeasurmentResult;
import cz.vsb.fei.java2.lab04.measurment.Measurment.ReleabilityMeasurmentResult;
import cz.vsb.fei.java2.lab04.points.ColorPoint;
import cz.vsb.fei.java2.lab04.points.Point;
import cz.vsb.fei.java2.lab04.points.Point.HashImpl;
import javafx.beans.binding.ObjectBinding;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Label;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import lombok.extern.log4j.Log4j2;

@Log4j2
public class AppController {

    private static final Random RANDOM = new Random();

    @FXML
    private TableView<Point> table1;
    private ObservableList<Point> points1 = FXCollections.observableArrayList();

    private Canvas canvas = new Canvas() {
	@Override
	public boolean isResizable() {
	    return true;
	}
    };

    @FXML
    private BorderPane pane;

    private BarChart<String, Double> insertTimeChart;

    private BarChart<String, Double> containsTimeCahrt;
    private BarChart<String, Number> releabilityChart;

    @FXML
    private VBox chartBox;

    @FXML
    public void initialize() {
	table1.setItems(points1);

	initColumns(table1);
	table1.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
	table1.getSelectionModel().selectedItemProperty()
		.addListener((ObservableValue<? extends Point> observable, Point oldValue, Point newValue) -> draw());
	canvas.setWidth(200);
	canvas.setHeight(200);
	pane.setCenter(canvas);
	pane.widthProperty()
		.addListener((observer, oldValue, newValue) -> canvas.setWidth(newValue.doubleValue() * 0.9));
	pane.heightProperty()
		.addListener((observer, oldValue, newValue) -> canvas.setHeight(newValue.doubleValue() * 0.9));
	canvas.boundsInLocalProperty().addListener((observable, oldValue, newValue) -> draw());
	canvas.setOnMouseClicked(this::mouseClickedInDrawingArea);
	draw();
	insertTimeChart = new BarChart<>(new CategoryAxis(), new LogarithmicAxis());
	containsTimeCahrt = new BarChart<>(new CategoryAxis(), new LogarithmicAxis());
	releabilityChart = new BarChart<>(new CategoryAxis(), new NumberAxis());
	chartBox.getChildren().add(new Label("Time of inserting points into set in seconds"));
	chartBox.getChildren().add(insertTimeChart);
	chartBox.getChildren().add(new Label("Average time (20 attempts) of method contains for set in seconds"));
	chartBox.getChildren().add(containsTimeCahrt);
	chartBox.getChildren().add(new Label("Releability of method contains (100 attempts) in percentage"));
	chartBox.getChildren().add(releabilityChart);

    }

    private void draw() {
	GraphicsContext gc = canvas.getGraphicsContext2D();
	double maxX = canvas.getWidth();
	double maxY = canvas.getHeight();
	double centerX = maxX / 2;
	double centerY = maxY / 2;
	gc.setFill(Color.WHITE);
	gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
	gc.setStroke(Color.BLACK);
	gc.strokeLine(centerX, 0, centerX, maxY);
	gc.strokeLine(0, centerY, maxX, centerY);
	gc.setFill(Color.BLACK);
	Point selectedPoint = table1.getSelectionModel().getSelectedItem();
	for (Point point : points1) {
	    if (point instanceof ColorPoint colorPoint) {
		gc.setFill(colorPoint.getColor());
		gc.fillOval(centerX + colorPoint.getX() - 2, centerY + colorPoint.getY() - 2, 4, 4);
	    } else {
		gc.setStroke(Color.BLACK);
		gc.strokeOval(centerX + point.getX() - 2, centerY + point.getY() - 2, 4, 4);
	    }
	    if (point.equals(selectedPoint)) {
		drawCroshairAroundPoint(gc, point);
	    }
	}
    }

    private void drawCroshairAroundPoint(GraphicsContext gc, Point point) {
	double maxX = canvas.getWidth();
	double maxY = canvas.getHeight();
	double centerX = maxX / 2;
	double centerY = maxY / 2;
	gc.setStroke(Color.RED);
	gc.strokeLine(centerX + point.getX() - 15, centerY + point.getY(), centerX + point.getX() - 6,
		centerY + point.getY());
	gc.strokeLine(centerX + point.getX() + 6, centerY + point.getY(), centerX + point.getX() + 15,
		centerY + point.getY());
	gc.strokeLine(centerX + point.getX(), centerY + point.getY() - 15, centerX + point.getX(),
		centerY + point.getY() - 6);
	gc.strokeLine(centerX + point.getX(), centerY + point.getY() + 6, centerX + point.getX(),
		centerY + point.getY() + 15);
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
	double maxX = canvas.getWidth();
	double maxY = canvas.getHeight();
	try {
	    Stream.generate(() -> Point.generateInRange(-maxX / 2, maxX / 2, -maxY / 2, maxY / 2)).limit(10)
	    	.forEach(points1::add);
	} catch (Exception ex) {
	    showErrorAlert(ex.getMessage());
	    log.error("Error while generate points.", ex);
	}
	draw();
    }

    private void showErrorAlert(List<String> messages) {
	String message = "Exception messages:\n\t" + messages.stream().collect(Collectors.joining("\n\t"));
	Alert alert = new Alert(AlertType.ERROR);
	alert.setTitle("ExceptionOccurred");
	Label text = new Label(message);
	text.setWrapText(true);
	Label header = new Label("Can We Implement It?\n\tYes We Can!!!");
	header.setWrapText(true);
	alert.getDialogPane().setContent(text);
	alert.getDialogPane().setHeader(header);
	alert.show();
    }

    private void showErrorAlert(String message) {
	Alert alert = new Alert(AlertType.ERROR);
	alert.setTitle("ExceptionOccurred");
	Label text = new Label(message);
	text.setWrapText(true);
	Label header = new Label("Can We Implement It?\nYes We Can!!!");
	header.setWrapText(true);
	alert.getDialogPane().setContent(text);
	alert.getDialogPane().setHeader(header);
	alert.show();
    }

    @FXML
    private void generateInRadiusPressed(ActionEvent event) {
	double radius = 10 + RANDOM.nextDouble(200);
	final Point center = Optional.ofNullable(table1.getSelectionModel().getSelectedItem()).orElse(new Point(0, 0));
	try {
	    Stream.generate(() -> Point.generateInRadius(center, radius)).limit(30).forEach(points1::add);
	} catch (Exception ex) {
	    showErrorAlert(ex.getMessage());
	    log.error("Error while generate points in radius.", ex);
	}
	draw();
    }

    @FXML
    private void mouseClickedInDrawingArea(MouseEvent event) {
	double maxX = canvas.getWidth();
	double maxY = canvas.getHeight();
	double x = event.getX() - maxX / 2;
	double y = event.getY() - maxY / 2;
	points1.stream().filter(p -> Math.abs(p.getX() - x) < 5 && Math.abs(p.getY() - y) < 5).findFirst()
		.ifPresent(p -> {
		    table1.selectionModelProperty().get().select(p);
		    table1.scrollTo(p);
		});
    }

    @FXML
    private void clearPressed(ActionEvent event) {
	table1.getSelectionModel().clearSelection();
	points1.clear();
	draw();
    }

    @FXML
    private void measure1000(ActionEvent event) {
	measure(1000);
    }

    @FXML
    private void measure10000(ActionEvent event) {
	measure(10000);
    }

    @FXML
    private void measure100000(ActionEvent event) {
	measure(100000);
    }

    private void measure(int maxCount) {
	insertTimeChart.getData().clear();
	containsTimeCahrt.getData().clear();
	releabilityChart.getData().clear();
	XYChart.Series<String, Number> containsSameReleability = new XYChart.Series<>();
	XYChart.Series<String, Number> containsEqualReleability = new XYChart.Series<>();
	containsSameReleability.setName("for same instance.");
	containsEqualReleability.setName("for equal instance.");
	List<String> errorMessages  =new LinkedList<String>();
	for (HashImpl hashImpl : HashImpl.values()) {
	    try {
		Point.setHashImplTo(hashImpl);
		XYChart.Series<String, Double> containsSpeed = new XYChart.Series<>();
		XYChart.Series<String, Double> insertSpeed = new XYChart.Series<>();
		containsSpeed.setName("implementation " + Point.getHashImpl());
		insertSpeed.setName("implementation " + Point.getHashImpl());
		int i = 10;
		while (i <= maxCount) {
		InsertContainsMeasurmentResult measureResult = Measurment.mesure(i);
		Data<String, Double> d = new Data<>(Integer.toString(i), measureResult.containsDuration() / 1000000d);
		containsSpeed.getData().add(d);
		insertSpeed.getData().add(new Data<>(Integer.toString(i), measureResult.insertDuration() / 1000000d));
		i *= 10;
		}
		ReleabilityMeasurmentResult result = Measurment.mesureReleability();
		containsSameReleability.getData().add(new Data<>(hashImpl.toString(), result.countSameInstance()));
		containsEqualReleability.getData().add(new Data<>(hashImpl.toString(), result.countEqualObject()));
		insertTimeChart.getData().add(insertSpeed);
		containsTimeCahrt.getData().add(containsSpeed);
	    } catch (Exception ex) {
		errorMessages.add(ex.getMessage());
		log.error("Error while mesure speed." , ex);
	    }
	}
	releabilityChart.getData().addAll(containsSameReleability, containsEqualReleability);
	if(!errorMessages.isEmpty()) {
	    showErrorAlert(errorMessages);
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
