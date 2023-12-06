package cz.vsb.java1.test2;

import cz.vsb.java1.test2.Vector3D;
import cz.vsb.java1.test2.helpers.RandomGenarator;

import java.util.ArrayList;
import java.util.List;

public class TaskUtils {

    public static List<Vector3D> generateListOfVectors() {
        return generateListOfVectors(10 + RandomGenarator.random.nextInt(10));
    }

    public static List<Vector3D> generateListOfVectors(int length) {
        List<Vector3D> result = new ArrayList<>();
        for (int i = 0; i < length; i++) {
            result.add(Vector3D.generate());
        }
        return result;
    }


    public static List<Person> generateListOfPersons() {
        return generateListOfPersons(10 + RandomGenarator.random.nextInt(10));
    }

    public static List<Person> generateListOfPersons(int length) {
        List<Person> result = new ArrayList<>();
        for (int i = 0; i < length; i++) {
            result.add(Person.generate());
        }
        return result;
    }
}

