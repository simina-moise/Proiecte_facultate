package com.healthtracker.model;
import java.time.LocalDate;

public class Exercise {
    private int id;
    private int userId;
    private LocalDate exerciseDate;
    private String type;
    private int durationMin;
    private int caloriesBurned;

    public Exercise(int id, int userId, LocalDate exerciseDate, String type, int durationMin, int caloriesBurned) {
        this.id = id;
        this.userId = userId;
        this.exerciseDate = exerciseDate;
        this.type = type;
        this.durationMin = durationMin;
        this.caloriesBurned = caloriesBurned;
    }

    public int getId() { return id; }
    public int getUserId() { return userId; }
    public LocalDate getExerciseDate() { return exerciseDate; }
    public String getType() { return type; }
    public int getDurationMin() { return durationMin; }
    public int getCaloriesBurned() { return caloriesBurned; }

    public void setId(int id) { this.id = id; }

}
