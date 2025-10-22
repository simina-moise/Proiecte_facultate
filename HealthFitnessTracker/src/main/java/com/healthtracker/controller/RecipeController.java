package com.healthtracker.controller;

import com.healthtracker.dao.MealDAO;
import com.healthtracker.dao.RecipeDAO;
import com.healthtracker.model.Meal;
import com.healthtracker.model.Recipe;
import com.healthtracker.model.User;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.time.LocalDate;

public class RecipeController {
    @FXML private TableView<Recipe> recipeTable;
    @FXML private TableColumn<Recipe, String> nameColumn;
    @FXML private TableColumn<Recipe, String> descColumn;
    @FXML private TableColumn<Recipe, Integer> caloriesColumn;
    @FXML private Button addToJournalButton;

    private User loggedInUser;

    public void setLoggedInUser(User user) {
        this.loggedInUser = user;
        loadRecipes();
    }

    @FXML
    public void initialize() {
        nameColumn.setCellValueFactory(data -> new javafx.beans.property.SimpleStringProperty(data.getValue().getName()));
        descColumn.setCellValueFactory(data -> new javafx.beans.property.SimpleStringProperty(data.getValue().getDescription()));
        caloriesColumn.setCellValueFactory(data -> new javafx.beans.property.SimpleIntegerProperty(data.getValue().getCalories()).asObject());

        addToJournalButton.setOnAction(e -> addSelectedRecipeToJournal());
    }

    private void loadRecipes() {
        recipeTable.setItems(FXCollections.observableArrayList(RecipeDAO.getAllRecipes()));
    }

    private void addSelectedRecipeToJournal() {
        Recipe selected = recipeTable.getSelectionModel().getSelectedItem();
        if (selected != null && loggedInUser != null) {
            Meal meal = new Meal(0, loggedInUser.getId(), LocalDate.now(), selected.getName(), selected.getCalories());
            MealDAO.addMeal(meal);

            Alert alert = new Alert(Alert.AlertType.INFORMATION, "Rețeta a fost adăugată în jurnal.");
            alert.showAndWait();
        }
    }
}
