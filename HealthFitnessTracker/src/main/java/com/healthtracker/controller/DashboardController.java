package com.healthtracker.controller;

import com.healthtracker.dao.DatabaseManager;
import com.healthtracker.dao.MealDAO;
import com.healthtracker.model.Meal;
import com.healthtracker.model.User;
import com.healthtracker.util.ExerciseXMLExporter;
import com.healthtracker.util.MealXMLExporter;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Types;
import java.time.LocalDate;
import java.util.List;
import com.healthtracker.dao.ExerciseDAO;
import com.healthtracker.model.Exercise;

public class DashboardController {

    @FXML
    private Label welcomeLabel;

    @FXML
    private Button addMealButton;

    @FXML
    private Button deleteMealButton;

    @FXML
    private Button addExerciseButton;

    @FXML
    private Button deleteExerciseButton;



    @FXML
    private TableView<Meal> mealTable;

    @FXML
    private TableColumn<Meal, String> dateColumn;

    @FXML
    private TableColumn<Meal, String> descriptionColumn;

    @FXML
    private TableColumn<Meal, Integer> caloriesColumn;

    @FXML
    private TableView<Exercise> exerciseTable;
    @FXML
    private TableColumn<Exercise, String> exerciseDateColumn;
    @FXML
    private TableColumn<Exercise, String> typeColumn;
    @FXML
    private TableColumn<Exercise, Integer> durationColumn;
    @FXML
    private TableColumn<Exercise, Integer> caloriesBurnedColumn;

    @FXML
    private Button showStatsButton;
    @FXML
    private Button exportXmlButton;
    @FXML
    private Button exportExercisesButton;
    @FXML
    private DatePicker filterDatePicker;
    @FXML
    private Button checkCaloriesButton;


    @FXML
    private Button openRecommendationsButton;

    @FXML
    private Button openProfileButton;
    @FXML
    private Button openRecipesButton;


    private User loggedInUser;

    public void setLoggedInUser(User user) {
        this.loggedInUser = user;
        welcomeLabel.setText("Bine ai venit, " + user.getName() + "!");
        loadMeals();
        loadExercises();
    }

    @FXML
    public void initialize() {
        if (addMealButton != null) {
            addMealButton.setOnAction(e -> openAddMealWindow());
        }
        if (deleteMealButton != null) {
            deleteMealButton.setOnAction(e -> deleteSelectedMeal());
        }
        if (addExerciseButton != null) {
            addExerciseButton.setOnAction(e -> openAddExerciseWindow());
        }
        if (deleteExerciseButton != null) {
            deleteExerciseButton.setOnAction(e -> deleteSelectedExercise());
        }
        if (showStatsButton != null) {
            showStatsButton.setOnAction(e -> openStatisticsWindow());
        }
        if (exportXmlButton != null) {
            exportXmlButton.setOnAction(e -> exportMealsToXML());
        }
        if (exportExercisesButton != null) {
            exportExercisesButton.setOnAction(e -> exportExercisesToXML());
        }
        if (filterDatePicker != null) {
            filterDatePicker.setOnAction(e -> filterMealsByDate());
        }
        if (checkCaloriesButton != null) {
            checkCaloriesButton.setOnAction(e -> checkTotalCalories());
        }
        if (openRecommendationsButton != null) {
            openRecommendationsButton.setOnAction(e -> openRecommendationsWindow());
        }
        if (openProfileButton != null) {
            openProfileButton.setOnAction(e -> openProfileWindow());
        }
        if (openRecipesButton != null) {
            openRecipesButton.setOnAction(e -> openRecipesWindow());
        }


        if (dateColumn != null) dateColumn.setCellValueFactory(new javafx.scene.control.cell.PropertyValueFactory<>("mealDate"));
        if (descriptionColumn != null) descriptionColumn.setCellValueFactory(new javafx.scene.control.cell.PropertyValueFactory<>("description"));
        if (caloriesColumn != null) caloriesColumn.setCellValueFactory(new javafx.scene.control.cell.PropertyValueFactory<>("calories"));

        if (exerciseDateColumn != null) exerciseDateColumn.setCellValueFactory(new PropertyValueFactory<>("exerciseDate"));
        if (typeColumn != null) typeColumn.setCellValueFactory(new PropertyValueFactory<>("type"));
        if (durationColumn != null) durationColumn.setCellValueFactory(new PropertyValueFactory<>("durationMin"));
        if (caloriesBurnedColumn != null) caloriesBurnedColumn.setCellValueFactory(new PropertyValueFactory<>("caloriesBurned"));

    }

    private void openAddMealWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/add_meal.fxml"));
            Scene scene = new Scene(loader.load());
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());

            AddMealController controller = loader.getController();
            controller.setLoggedInUser(loggedInUser);

            Stage stage = new Stage();
            stage.setTitle("Adaugă Masă");
            stage.setScene(scene);
            stage.show();

            stage.setOnHidden(e -> loadMeals());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }



    private void loadMeals() {
        if (loggedInUser == null || mealTable == null) return;

        List<Meal> meals = MealDAO.getMealsByUserId(loggedInUser.getId());

        meals = meals.stream()
                .sorted((m1, m2) -> Integer.compare(m2.getCalories(), m1.getCalories()))
                .toList();

        ObservableList<Meal> observableMeals = FXCollections.observableArrayList(meals);
        mealTable.setItems(observableMeals);
    }

    private void deleteSelectedMeal() {
        Meal selectedMeal = mealTable.getSelectionModel().getSelectedItem();

        if (selectedMeal != null) {
            MealDAO.deleteMealById(selectedMeal.getId());
            loadMeals();
        } else {
            System.out.println("️ Nicio masă selectată pentru ștergere.");
        }
    }
    private void openAddExerciseWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/add_exercise.fxml"));
            Scene scene = new Scene(loader.load());
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());


            AddExerciseController controller = loader.getController();
            controller.setLoggedInUser(loggedInUser);

            Stage stage = new Stage();
            stage.setTitle("Adaugă Exercițiu");
            stage.setScene(scene);
            stage.show();

            stage.setOnHidden(e -> loadExercises());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void loadExercises() {
        if (loggedInUser == null || exerciseTable == null) return;

        List<Exercise> exercises = ExerciseDAO.getExercisesByUserId(loggedInUser.getId());
        ObservableList<Exercise> observableExercises = FXCollections.observableArrayList(exercises);
        exerciseTable.setItems(observableExercises);
    }

    private void deleteSelectedExercise() {
        Exercise selectedExercise = exerciseTable.getSelectionModel().getSelectedItem();
        if (selectedExercise != null) {
            ExerciseDAO.deleteExerciseById(selectedExercise.getId());
            loadExercises();
        } else {
            System.out.println("️ Niciun exercițiu selectat pentru ștergere.");
        }
    }
    private void openStatisticsWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/statistics.fxml"));
            Scene scene = new Scene(loader.load());
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());


            Stage stage = new Stage();
            stage.setTitle("Statistici: Calorii pe Zile");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void exportMealsToXML() {
        if (loggedInUser == null) return;

        List<Meal> meals = MealDAO.getMealsByUserId(loggedInUser.getId());
        String path = "meals_" + loggedInUser.getName().replace(" ", "_") + ".xml";

        MealXMLExporter.exportMealsToXML(meals, path);
    }
    private void exportExercisesToXML() {
        if (loggedInUser == null) return;

        List<Exercise> exercises = ExerciseDAO.getExercisesByUserId(loggedInUser.getId());
        String path = "exercises_" + loggedInUser.getName().replace(" ", "_") + ".xml";

        ExerciseXMLExporter.exportExercisesToXML(exercises, path);
    }
    private void filterMealsByDate() {
        if (loggedInUser == null || mealTable == null) return;

        LocalDate selectedDate = filterDatePicker.getValue();
        if (selectedDate == null) {
            loadMeals(); // dacă e gol, afișăm tot
            return;
        }

        List<Meal> meals = MealDAO.getMealsByUserId(loggedInUser.getId());

        List<Meal> filtered = meals.stream()
                .filter(m -> m.getMealDate().equals(selectedDate))
                .toList();

        mealTable.setItems(FXCollections.observableArrayList(filtered));
    }
    private void checkTotalCalories() {
        try (Connection conn = DatabaseManager.getConnection();
             CallableStatement stmt = conn.prepareCall("{ ? = call total_calories_for_day(?, ?) }")) {

            stmt.registerOutParameter(1, Types.INTEGER);
            stmt.setInt(2, loggedInUser.getId());
            stmt.setDate(3, java.sql.Date.valueOf(LocalDate.now()));

            stmt.execute();
            int total = stmt.getInt(1);

            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Calorii consumate");
            alert.setHeaderText(null);
            alert.setContentText("Astăzi ai consumat " + total + " calorii.");
            alert.showAndWait();

        } catch (SQLException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Eroare");
            alert.setHeaderText("Nu s-a putut calcula totalul");
            alert.setContentText("!!! " + e.getMessage());
            alert.showAndWait();
        }
    }
    private void openRecommendationsWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/recommendations.fxml"));
            Scene scene = new Scene(loader.load());
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());


            RecommendationController controller = loader.getController();
            controller.setLoggedInUser(loggedInUser);

            Stage stage = new Stage();
            stage.setTitle("Sugestii");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void openProfileWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/profile.fxml"));
            Scene scene = new Scene(loader.load());
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());


            ProfileController controller = loader.getController();
            controller.setLoggedInUser(loggedInUser);

            Stage stage = new Stage();
            stage.setTitle("Date Profil");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private void openRecipesWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/recipes.fxml"));
            Scene scene = new Scene(loader.load());
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());


            RecipeController controller = loader.getController();
            controller.setLoggedInUser(loggedInUser);

            Stage stage = new Stage();
            stage.setTitle("Rețete sănătoase");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }



}
