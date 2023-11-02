	package lab;

import javafx.animation.AnimationTimer;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

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
	private TextField name_input;

	@FXML
	private ListView<Score> player_list;

	private ObservableList<Score> scores;
	
	private AnimationTimer animationTimer;
	
	public GameController() {
		scores = FXCollections.observableList(new ArrayList<Score>());

		scores.addListener(new ListChangeListener<Score>() {

			@Override
            public void onChanged(Change<? extends Score> c) {
				System.out.println("Zmeneno");
            }
		});
	}
	
	public void startGame() {

		player_list.setItems(scores);

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
	private void game_over() {
		System.out.println("Game Over");

		Random random = new Random();

		Score score = new Score(
				random.nextInt(50),
				name_input.getText()
				);
		System.out.println(score.toString());

		scores.add(score);
	/*
		scores.sort(new Comparator<Score>() {
			@Override
			public int compare(Score o1, Score o2) {
				return o2.getScore() - o1.getScore();
			}
		});
	 */
		scores.sort((x, y) -> y.getScore() - x.getScore());
	};

	@FXML
	private void high_score() {
		HashSet<Score> unique = new HashSet<Score>();
		for(Score x : scores){
			unique.add(x);
		}

		scores.clear();
		scores.addAll(unique);

		scores.sort((x, y) -> y.getScore() - x.getScore());
	};

	@FXML
	private void save_score() {
		try (FileWriter fw = new FileWriter("data.csv")){
			for(Score x : scores){
                fw.write(x.getName() + "," + x.getScore() + "\n");
            }

		}catch(IOException e) {
			e.printStackTrace();
		}
	};

	@FXML
	private void load_score() {

		try(Scanner scanner = new Scanner(new java.io.File("data.csv"))) {
			scanner.useDelimiter("[;\\n]");
			while(scanner.hasNext()) {
				String name = scanner.next();
				int score = scanner.nextInt();
				scores.add(new Score(score, name));
			}

		} catch (IOException e) {
			e.printStackTrace();
		}

		/*
		try (BufferedReader br = new BufferedReader(
				new FileReader("data.csv"))) {

			while(true) {
				String line = br.readLine();
				if(line == null) break;

				String[] parts = line.split(",");
				String name = parts[0];
				int scoreVal = Integer.parseInt(parts[1]);

				scores.add(new Score(scoreVal, name));
			}

		} catch (IOException e) {
			e.printStackTrace();
		}
		 */
	};

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
