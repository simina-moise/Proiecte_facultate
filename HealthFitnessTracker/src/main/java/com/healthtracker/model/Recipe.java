package com.healthtracker.model;

public class Recipe {
    private int id;
    private String name;
    private String description;
    private int calories;

    public Recipe(int id, String name, String description, int calories) {
        this.id = id;
        this.name = name;
        this.description = description;
        this.calories = calories;
    }


    public int getId() { return id; }
    public String getName() { return name; }
    public String getDescription() { return description; }
    public int getCalories() { return calories; }
}
