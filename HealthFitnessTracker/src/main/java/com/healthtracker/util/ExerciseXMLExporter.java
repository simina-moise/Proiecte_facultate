package com.healthtracker.util;

import com.healthtracker.model.Exercise;
import org.w3c.dom.*;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.List;

public class ExerciseXMLExporter {

    public static void exportExercisesToXML(List<Exercise> exercises, String filePath) {
        try {
            DocumentBuilder docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
            Document doc = docBuilder.newDocument();

            Element root = doc.createElement("exercises");
            doc.appendChild(root);

            for (Exercise ex : exercises) {
                Element e = doc.createElement("exercise");

                Element date = doc.createElement("date");
                date.appendChild(doc.createTextNode(ex.getExerciseDate().toString()));
                e.appendChild(date);

                Element type = doc.createElement("type");
                type.appendChild(doc.createTextNode(ex.getType()));
                e.appendChild(type);

                Element duration = doc.createElement("duration");
                duration.appendChild(doc.createTextNode(String.valueOf(ex.getDurationMin())));
                e.appendChild(duration);

                Element calories = doc.createElement("calories");
                calories.appendChild(doc.createTextNode(String.valueOf(ex.getCaloriesBurned())));
                e.appendChild(calories);

                root.appendChild(e);
            }

            Transformer t = TransformerFactory.newInstance().newTransformer();
            t.setOutputProperty(OutputKeys.INDENT, "yes");
            t.transform(new DOMSource(doc), new StreamResult(new File(filePath)));

            System.out.println(" Exercițiile au fost exportate cu succes în " + filePath);

        } catch (ParserConfigurationException | TransformerException e) {
            e.printStackTrace();
        }
    }
}
