package com.healthtracker.util;

import com.healthtracker.model.Meal;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.*;

import java.io.File;
import java.util.List;

public class MealXMLExporter {

    public static void exportMealsToXML(List<Meal> meals, String filePath) {
        try {
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.newDocument();

            Element rootElement = doc.createElement("meals");
            doc.appendChild(rootElement);

            for (Meal meal : meals) {
                Element mealElement = doc.createElement("meal");

                Element date = doc.createElement("date");
                date.appendChild(doc.createTextNode(meal.getMealDate().toString()));
                mealElement.appendChild(date);

                Element desc = doc.createElement("description");
                desc.appendChild(doc.createTextNode(meal.getDescription()));
                mealElement.appendChild(desc);

                Element calories = doc.createElement("calories");
                calories.appendChild(doc.createTextNode(String.valueOf(meal.getCalories())));
                mealElement.appendChild(calories);

                rootElement.appendChild(mealElement);
            }

            // Scriere în fișier
            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(new File(filePath));

            transformer.transform(source, result);
            System.out.println(" Export XML complet: " + filePath);

        } catch (ParserConfigurationException | TransformerException e) {
            e.printStackTrace();
        }
    }
}
