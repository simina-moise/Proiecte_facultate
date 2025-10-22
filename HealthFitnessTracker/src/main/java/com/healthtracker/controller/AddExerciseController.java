package com.healthtracker.controller;

import com.healthtracker.dao.ExerciseDAO;
import com.healthtracker.model.Exercise;
import com.healthtracker.model.User;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

public class AddExerciseController {


    @FXML private DatePicker exerciseDatePicker;
    @FXML private TextField typeField;
    @FXML private TextField durationField;
    @FXML private TextField caloriesField;
    @FXML private Button saveButton;

    private User loggedInUser;


    @FXML
    public void initialize() {
        saveButton.setOnAction(e -> saveExercise());
    }

    public void setLoggedInUser(User user) {
        this.loggedInUser = user;
    }


    private void saveExercise() {
        if (loggedInUser == null) return;
        try {
            Exercise exercise = new Exercise(
                    0,
                    loggedInUser.getId(),
                    exerciseDatePicker.getValue(),
                    typeField.getText(),
                    Integer.parseInt(durationField.getText()),
                    Integer.parseInt(caloriesField.getText())
            );
            ExerciseDAO.addExercise(exercise);

            ((Stage) saveButton.getScene().getWindow()).close();

        } catch (Exception ex) {
            System.out.println(" Eroare la salvarea exercițiului: " + ex.getMessage());
        }
    }
}
