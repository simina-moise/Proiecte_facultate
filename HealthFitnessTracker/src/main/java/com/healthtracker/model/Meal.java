package com.healthtracker.model;
import java.time.LocalDate;

public class Meal {
    private int id;
    private int userId;
    private LocalDate mealDate;
    private String description;
    private int calories;

    public Meal(int id, int userId, LocalDate mealDate, String description, int calories) {
        this.id = id;
        this.userId = userId;
        this.mealDate = mealDate;
        this.description = description;
        this.calories = calories;
    }

    public int getId() { return id; }
    public int getUserId() { return userId; }
    public LocalDate getMealDate() { return mealDate; }
    public String getDescription() { return description; }
    public int getCalories() { return calories; }

    public void setId(int id) { this.id = id; }
    public void setCalories(int calories) { this.calories = calories; }
}
