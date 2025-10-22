package com.healthtracker.dao;

import com.healthtracker.model.Exercise;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ExerciseDAO {

    public static void addExercise(Exercise exercise) {
        String sql = "INSERT INTO exercises (user_id, exercise_date, type, duration_min, calories_burned) VALUES (?, ?, ?, ?, ?)";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, exercise.getUserId());
            stmt.setDate(2, Date.valueOf(exercise.getExerciseDate()));
            stmt.setString(3, exercise.getType());
            stmt.setInt(4, exercise.getDurationMin());
            stmt.setInt(5, exercise.getCaloriesBurned());

            stmt.executeUpdate();//trimite comanda insert catre baza de date
            System.out.println(" Exercițiu salvat cu succes.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static List<Exercise> getExercisesByUserId(int userId) {
        List<Exercise> list = new ArrayList<>();
        String sql = "SELECT * FROM exercises WHERE user_id = ? ORDER BY exercise_date DESC";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                Exercise exercise = new Exercise(
                        rs.getInt("id"),
                        rs.getInt("user_id"),
                        rs.getDate("exercise_date").toLocalDate(),
                        rs.getString("type"),
                        rs.getInt("duration_min"),
                        rs.getInt("calories_burned")
                );
                list.add(exercise);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static void deleteExerciseById(int id) {
        String sql = "DELETE FROM exercises WHERE id = ?";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, id);
            stmt.executeUpdate();
            System.out.println(" Exercițiu șters cu succes.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
