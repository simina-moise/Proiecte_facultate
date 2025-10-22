package com.healthtracker.controller;

import com.healthtracker.dao.StatisticsDAO;
import javafx.fxml.FXML;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;

import java.util.Map;

public class StatisticsController {

    @FXML
    private LineChart<String, Number> caloriesChart;

    @FXML
    public void initialize() {
        Map<String, Integer> caloriesIn = StatisticsDAO.getTotalCaloriesByDate();
        Map<String, Integer> caloriesOut = StatisticsDAO.getTotalBurnedByDate();

        XYChart.Series<String, Number> seriesIn = new XYChart.Series<>();
        seriesIn.setName("Consumate");

        XYChart.Series<String, Number> seriesOut = new XYChart.Series<>();
        seriesOut.setName("Arse");

        for (String date : caloriesIn.keySet()) {
            seriesIn.getData().add(new XYChart.Data<>(date, caloriesIn.get(date)));
        }

        for (String date : caloriesOut.keySet()) {
            seriesOut.getData().add(new XYChart.Data<>(date, caloriesOut.get(date)));
        }

        caloriesChart.getData().addAll(seriesIn, seriesOut);
    }
}
