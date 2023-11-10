	package lab;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Set;

import javafx.animation.AnimationTimer;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.*;

	public class GameController {

	private World world;
	
	@FXML
	private Slider angleSlider;
	
	@FXML
	private Slider strengthSlider;
	
	@FXML
	private Canvas canvas;
	
	@FXML
	private Label shoots;
	
	@FXML
	private Label hits;
	
	@FXML 
	private TableView<Score> scoreList;
	
	@FXML
	private TextField nameTextField;

	private ScoreDAO scoreDAO;
	
	private List<Score> highScores = new LinkedList<>();
	
	private AnimationTimer animationTimer;
	
	public GameController() {
	}
	
	public void startGame() {

		List<TableColumn<Score, ?>> columns = scoreList.getColumns();
		columns.get(0).setCellValueFactory(x -> new SimpleObjectProperty(x.getValue().getName()));
		columns.get(1).setCellValueFactory(x -> new SimpleObjectProperty(x.getValue().getScore()));

		scoreDAO = new ScoreDAO();

		initScoreList();

		this.world = new World(canvas.getWidth(), canvas.getHeight());
		this.world.setGameListener(new GameListenerImpl());
		//Draw scene on a separate thread to avoid blocking UI.
		animationTimer = new DrawingThread(canvas, world);
		angleSlider.valueProperty().addListener(this::angleChanged);
		world.setCannonAngle(angleSlider.getValue());
		
		strengthSlider.valueProperty().addListener(this::strenghtChanged);
		world.setCannonStrength(strengthSlider.getValue());
		animationTimer.start();
	}


	public void stopGame() {
		animationTimer.stop();
	}
	
	
	@FXML
	private void firePressed() {
		world.fire();
	}
	
	
	private void angleChanged(ObservableValue<? extends Number> observable
								, Number oldValue, Number newValue) {
		world.setCannonAngle(newValue.doubleValue());
	}

	private void strenghtChanged(ObservableValue<? extends Number> observable
			, Number oldValue, Number newValue) {
		world.setCannonStrength(newValue.doubleValue());
	}
	
	@FXML
	private void gameOverPressed() {
		Score score = new Score(new Random().nextInt(11), nameTextField.getText());
		scoreList.getItems().add(score);
		sortScores();
	}
	
	@FXML
	private void highScoresPressed() {
		Set<Score> tempScores = new HashSet<>();
		tempScores.addAll(highScores);
		highScores.clear();
		highScores.addAll(tempScores);
		Collections.sort(highScores,  new ScoreComparator().reversed());
		initScoreList();
	}

	@FXML
	private void savePressed() throws IOException {



		for (Score score : highScores) {
			scoreDAO.insert(score);
		}

//		try(PrintWriter pw = new PrintWriter(new FileWriter("high_score.csv"))){
//			for(Score score: highScores) {
//				pw.printf("%s;%d\n", score.getName(), score.getScore());
//			}
//		}
	}
	
	
	@FXML
	private void loadPressed() throws IOException{
		highScores.clear();

		highScores.addAll(scoreDAO.findAll());

//		try(BufferedReader br = new BufferedReader(new FileReader("high_score.csv"))){
//			String line;
//			while(null != (line = br.readLine())) {
//				String [] tokens = line.split(";");
//				highScores.add(new Score(Integer.parseInt(tokens[1]), tokens[0]));
//			}
//		}
		initScoreList();
	}

	private void initScoreList() {
		scoreList.setItems(FXCollections.observableList(highScores));
	}
	
	private void sortScores() {
		Collections.sort(scoreList.getItems(),  new ScoreComparator().reversed());
	}

	private class GameListenerImpl implements GameListener {

		@Override
		public void stateChanged(int shoots, int hits) {
			GameController.this.shoots.setText("" + shoots);
			GameController.this.hits.setText("" + hits);
		}

		@Override
		public void gameOver() {
			stopGame();
		}
		
	}
	
	
}
