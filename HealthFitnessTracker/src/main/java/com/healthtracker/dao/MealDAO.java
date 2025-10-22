package com.healthtracker.dao;

import com.healthtracker.model.Meal;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
public class MealDAO {

    public static void addMeal(Meal meal) {
        String sql = "INSERT INTO meals (user_id, meal_date, description, calories) VALUES (?, ?, ?, ?)";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, meal.getUserId());
            stmt.setDate(2, java.sql.Date.valueOf(meal.getMealDate()));
            stmt.setString(3, meal.getDescription());
            stmt.setInt(4, meal.getCalories());

            stmt.executeUpdate();
            System.out.println("Masa a fost adăugată cu succes.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }


    public static List<Meal> getMealsByUserId(int userId) {
        List<Meal> meals = new ArrayList<>();
        String sql = "SELECT * FROM meals WHERE user_id = ? ORDER BY meal_date DESC";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                Meal meal = new Meal(
                        rs.getInt("id"),
                        rs.getInt("user_id"),
                        rs.getDate("meal_date").toLocalDate(),
                        rs.getString("description"),
                        rs.getInt("calories")
                );
                meals.add(meal);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return meals;
    }
    public static void deleteMealById(int id) {
        String sql = "DELETE FROM meals WHERE id = ?";

        try (Connection conn = DatabaseManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, id);
            stmt.executeUpdate();
            System.out.println("Masa a fost ștearsă cu succes.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }


}
