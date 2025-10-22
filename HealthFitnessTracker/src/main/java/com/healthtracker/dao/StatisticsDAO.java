package com.healthtracker.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

public class StatisticsDAO {

    public static Map<String, Integer> getTotalCaloriesByDate() {
        Map<String, Integer> result = new HashMap<>();

        String sql = "SELECT meal_date, SUM(calories) AS total " +
                "FROM meals GROUP BY meal_date ORDER BY meal_date";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                String date = rs.getDate("meal_date").toString();
                int total = rs.getInt("total");
                result.put(date, total);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;
    }

    public static Map<String, Integer> getTotalBurnedByDate() {
        Map<String, Integer> result = new HashMap<>();

        String sql = "SELECT exercise_date, SUM(calories_burned) AS total " +
                "FROM exercises GROUP BY exercise_date ORDER BY exercise_date";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                String date = rs.getDate("exercise_date").toString();
                int total = rs.getInt("total");
                result.put(date, total);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;
    }
}
