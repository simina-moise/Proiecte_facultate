package com.healthtracker.controller;

import com.healthtracker.dao.MealDAO;
import com.healthtracker.model.Meal;
import com.healthtracker.model.User;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.time.LocalDate;

public class AddMealController {

    @FXML private DatePicker mealDatePicker;
    @FXML private TextField descriptionField;
    @FXML private TextField caloriesField;
    @FXML private Button saveButton;

    private User loggedInUser;

    public void setLoggedInUser(User user) {
        this.loggedInUser = user;
    }

    @FXML
    public void initialize() {
        saveButton.setOnAction(e -> saveMeal());
    }

    @FXML
    private void saveMeal() {
        try {
            LocalDate date = mealDatePicker.getValue();
            String description = descriptionField.getText();
            int calories = Integer.parseInt(caloriesField.getText());

            if (calories > 10000) {
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Valoare suspectă");
                alert.setHeaderText("Calorii prea multe");
                alert.setContentText("️ Ai introdus o valoare nerealistă de calorii (> 10000).\nTe rugăm să verifici.");
                alert.showAndWait();
                return;
            }

            Meal meal = new Meal(
                    0,
                    loggedInUser.getId(),
                    date,
                    description,
                    calories
            );

            MealDAO.addMeal(meal);

            Alert success = new Alert(Alert.AlertType.INFORMATION);
            success.setTitle("Succes");
            success.setHeaderText(null);
            success.setContentText(" Masa a fost salvată cu succes!");
            success.showAndWait();

            ((Stage) saveButton.getScene().getWindow()).close();

        } catch (Exception ex) {
            String msg = ex.getMessage();
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Eroare la salvare");
            alert.setHeaderText("Masa nu a fost salvată");

            if (msg != null && msg.contains("limita admisă")) {
                alert.setContentText("️ Ai introdus prea multe calorii! Limita este 5000.");
            } else {
                alert.setContentText("!!!! " + msg);
            }

            alert.showAndWait();
        }
    }


}
