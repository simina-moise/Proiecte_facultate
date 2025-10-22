package com.healthtracker.dao;

import com.healthtracker.model.Progress;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class ProgressDAO {

    public static void addProgress(Progress progress) {
        String sql = "INSERT INTO progress (user_id, date_logged, weight_kg, notes) VALUES (?, ?, ?, ?)";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, progress.getUserId());
            stmt.setDate(2, Date.valueOf(progress.getDateLogged()));
            stmt.setDouble(3, progress.getWeightKg());
            stmt.setString(4, progress.getNotes());

            stmt.executeUpdate();
            System.out.println("✅ Progres salvat cu succes.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static List<Progress> getProgressByUserId(int userId) {
        List<Progress> progressList = new ArrayList<>();
        String sql = "SELECT * FROM progress WHERE user_id = ? ORDER BY date_logged DESC";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                progressList.add(new Progress(
                        rs.getInt("id"),
                        rs.getInt("user_id"),
                        rs.getDate("date_logged").toLocalDate(),
                        rs.getDouble("weight_kg"),
                        rs.getString("notes")
                ));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return progressList;
    }

    public static double getLatestWeight(int userId) {
        String sql = "SELECT weight_kg FROM progress WHERE user_id = ? ORDER BY date_logged DESC LIMIT 1";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("weight_kg");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -1; // în caz că nu există
    }
}
