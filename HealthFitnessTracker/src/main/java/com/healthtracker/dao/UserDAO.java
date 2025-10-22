package com.healthtracker.dao;

import com.healthtracker.model.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDAO {
    public static User getUserByEmailAndPassword(String email, String password) {
        String sql = "SELECT * FROM users WHERE email = ? AND password = ?";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, email);
            stmt.setString(2, password);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return new User(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getString("email"),
                        rs.getString("password"),
                        rs.getInt("height_cm") // ← Adăugat!
                );

            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }

    public static double getLatestWeightForUser(int userId) {
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

        return 70.0;
    }
    public static void updateHeight(int userId, int heightCm) {
        String sql = "UPDATE users SET height_cm = ? WHERE id = ?";
        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, heightCm);
            stmt.setInt(2, userId);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void insertWeight(int userId, double weightKg) {
        String sql = "INSERT INTO progress (user_id, date_logged, weight_kg) VALUES (?, CURRENT_DATE, ?)";
        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, userId);
            stmt.setDouble(2, weightKg);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }


}
