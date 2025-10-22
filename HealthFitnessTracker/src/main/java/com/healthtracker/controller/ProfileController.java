package com.healthtracker.controller;

import com.healthtracker.dao.UserDAO;
import com.healthtracker.model.User;
import javafx.fxml.FXML;
import javafx.scene.control.*;

public class ProfileController {

    private User loggedInUser;

    @FXML
    private TextField heightField;

    @FXML
    private TextField weightField;

    @FXML
    private Button saveButton;

    @FXML
    private Label feedbackLabel;



    public void setLoggedInUser(User user) {
        this.loggedInUser = user;

        if (user.getHeightCm() > 0) {
            heightField.setText(String.valueOf(user.getHeightCm()));
        }

        double latestWeight = UserDAO.getLatestWeightForUser(user.getId());
        if (latestWeight > 0) {
            weightField.setText(String.valueOf(latestWeight));
        }
    }

    @FXML
    public void initialize() {
        saveButton.setOnAction(e -> saveProfile());
    }

    private void saveProfile() {
        try {
            int height = Integer.parseInt(heightField.getText().trim());
            double weight = Double.parseDouble(weightField.getText().trim());

            // salvăm înălțimea în tabela users
            UserDAO.updateHeight(loggedInUser.getId(), height);
            loggedInUser.setHeightCm(height);

            // salvăm greutatea în tabela progress
            UserDAO.insertWeight(loggedInUser.getId(), weight);

            feedbackLabel.setText("✔️ Date salvate cu succes!");
        } catch (Exception ex) {
            feedbackLabel.setText("️ Eroare la salvare: " + ex.getMessage());
        }
    }
}
