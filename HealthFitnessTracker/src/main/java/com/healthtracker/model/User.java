package com.healthtracker.model;

public class User {
    private int id;
    private String name;
    private String email;
    private String password;
    private int heightCm;


    public User(int id, String name, String email, String password, int heightCm) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.password = password;
    }


    public String getName() {
        return this.name;
    }

    public int getId() {
        return this.id;
    }
    public int getHeightCm() {
        return this.heightCm;
    }

    public void setHeightCm(int height) {
        this.heightCm=height;
    }
}
