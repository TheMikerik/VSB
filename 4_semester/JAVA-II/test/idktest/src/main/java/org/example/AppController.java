package org.example;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;

public class AppController {

	@FXML
	private Label infoLabel;

	@FXML
	private void menuPressed(ActionEvent event) {
		if(event.getSource() instanceof MenuItem menuItem) {
			infoLabel.setText("Selected menu: " + menuItem.getText());
		}
	}

}
