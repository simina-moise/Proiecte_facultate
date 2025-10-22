package com.healthtracker.controller;

import com.healthtracker.dao.UserDAO;
import com.healthtracker.model.User;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.scene.control.Button;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {

    @FXML private TextField emailField;
    @FXML private PasswordField passwordField;
    @FXML private Button loginButton;

    @FXML
    public void initialize() {
        loginButton.setOnAction(e -> handleLogin());
    }

    private void handleLogin() {
        String email = emailField.getText().trim();
        String password = passwordField.getText().trim();

        System.out.println("Email introdus: " + email);
        System.out.println("Parolă introdusă: " + password);

        //cauta in baza de date
        User user = UserDAO.getUserByEmailAndPassword(email, password);

        if (user != null) {
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/views/dashboard.fxml"));
                Scene scene = new Scene(loader.load());


                DashboardController controller = loader.getController();
                controller.setLoggedInUser(user);

                Stage stage = (Stage) loginButton.getScene().getWindow();
                stage.setScene(scene);
                stage.show();
            } catch (IOException e) {
                e.printStackTrace();
            }


        } else {
            System.out.println("Email sau parolă incorecte.");
        }
    }



}
