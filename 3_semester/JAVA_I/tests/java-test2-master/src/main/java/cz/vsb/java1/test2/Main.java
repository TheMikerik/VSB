package cz.vsb.java1.test2;

import cz.vsb.java1.test2.task.*;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

public class Main {

    public static void main(String[] args) throws IOException, SQLException {

        System.out.println("Task1a");
        T1 t1 = new T1();
        List<Vector3D> v1 = t1.run();
        System.out.println("\n");

        System.out.println("Task1b");
        T1b t1b = new T1b();
        List<Vector3D> v1b = t1b.run();
        System.out.println("\n");

        System.out.println("Task2a");
        T2a t2a = new T2a();
        List<Vector3D> v2a = t2a.run(v1);
        System.out.println("\n");

//
//        System.out.println("\nTask1");
//        task1a t1 = new task1a();
//        List<Vector3D> vectors1a = t1.run();
//        System.out.println("\n\n");
//
//        System.out.println("\nTask1b");
//        task1b t1b = new task1b();
//        List<Vector3D> vectors1b = t1b.run();
//        System.out.println("\n");
//
//        System.out.println("\nTask2a");
//        Task2a t2a = new Task2a();
//        List<Vector3D> vectors2a = t2a.run(vectors1b);
//        System.out.println("\n");
//
//        System.out.println("\nTask2b");
//        Task2b t2b = new Task2b();
//        List<Vector3D> vectors2b = t2b.run(vectors1b);
//        System.out.println("\n");
//
//        System.out.println("\nTask2b");
//        Task3a t3a = new Task3a();
//        t3a.run();
//        System.out.println("\n");
    }

}
