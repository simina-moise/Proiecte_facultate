package com.healthtracker.model;

public class ProgressLog {
    private int id;
    private int userId;
    private String eventType;
    private java.time.LocalDateTime eventDate;

    public ProgressLog(int id, int userId, String eventType, java.time.LocalDateTime eventDate) {
        this.id = id;
        this.userId = userId;
        this.eventType = eventType;
        this.eventDate = eventDate;
    }

    public int getId() { return id; }

}
