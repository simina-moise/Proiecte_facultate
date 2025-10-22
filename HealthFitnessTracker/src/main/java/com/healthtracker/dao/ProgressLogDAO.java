package com.healthtracker.dao;

import com.healthtracker.model.ProgressLog;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ProgressLogDAO {
    public static List<ProgressLog> getLogsByUserId(int userId) {
        List<ProgressLog> logs = new ArrayList<>();

        String sql = "SELECT * FROM progress WHERE user_id = ? ORDER BY event_date DESC";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                logs.add(new ProgressLog(
                        rs.getInt("id"),
                        rs.getInt("user_id"),
                        rs.getString("event_type"),
                        rs.getTimestamp("event_date").toLocalDateTime()
                ));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return logs;
    }
}
