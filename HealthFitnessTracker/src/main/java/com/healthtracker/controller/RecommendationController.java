package com.healthtracker.controller;

import com.healthtracker.dao.UserDAO;
import com.healthtracker.model.User;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class RecommendationController {

    private User loggedInUser;

    @FXML
    private Label bmiLabel;

    @FXML
    private Label suggestionLabel;

    @FXML
    private Button generateButton;

    public void setLoggedInUser(User user) {
        this.loggedInUser = user;
    }

    @FXML
    public void initialize() {
        generateButton.setOnAction(e -> generateSuggestions());
    }

    private void generateSuggestions() {
        double latestWeight = UserDAO.getLatestWeightForUser(loggedInUser.getId());


        int heightCm = loggedInUser.getHeightCm();
        if (heightCm == 0) {
            bmiLabel.setText("IMC: necunoscut");
            suggestionLabel.setText("️ Înălțimea nu este setată. Vă rugăm să o completați.");
            return;
        }
        double heightM = heightCm / 100.0;
        double bmi = latestWeight / (heightM * heightM);

        bmiLabel.setText(String.format("IMC: %.2f", bmi));

        String suggestion;
        if (bmi < 18.5) {
            suggestion = "Greutate scăzută – încearcă mese mai bogate în calorii.";
        } else if (bmi < 25) {
            suggestion = "Greutate normală – menține un stil echilibrat.";
        } else {
            suggestion = "Greutate crescută – recomand 30min mers/alergare azi.";
        }

        suggestionLabel.setText(suggestion);
    }
}
