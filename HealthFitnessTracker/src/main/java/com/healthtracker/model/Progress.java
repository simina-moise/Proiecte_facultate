package com.healthtracker.model;

import java.time.LocalDate;

public class Progress {

    private int id;
    private int userId;
    private LocalDate dateLogged;
    private double weightKg;
    private String notes;

    public Progress(int id, int userId, LocalDate dateLogged, double weightKg, String notes) {
        this.id = id;
        this.userId = userId;
        this.dateLogged = dateLogged;
        this.weightKg = weightKg;
        this.notes = notes;
    }

    // Getters
    public int getId() {
        return id;
    }

    public int getUserId() {
        return userId;
    }

    public LocalDate getDateLogged() {
        return dateLogged;
    }

    public double getWeightKg() {
        return weightKg;
    }

    public String getNotes() {
        return notes;
    }

    // Setters (dacă ai nevoie)
    public void setId(int id) {
        this.id = id;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public void setDateLogged(LocalDate dateLogged) {
        this.dateLogged = dateLogged;
    }

    public void setWeightKg(double weightKg) {
        this.weightKg = weightKg;
    }

    public void setNotes(String notes) {
        this.notes = notes;
    }
}
