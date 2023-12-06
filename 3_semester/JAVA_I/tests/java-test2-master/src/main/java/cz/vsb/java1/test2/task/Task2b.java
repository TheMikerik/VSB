package cz.vsb.java1.test2.task;

import cz.vsb.java1.test2.Vector3D;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Task2b {
    public List<Vector3D> run(List<Vector3D> input) throws IOException {
        var nameMap = input.stream().collect(Collectors.toMap(Vector3D::getName, v -> v));
        var sortedNames = nameMap.entrySet().stream().sorted(Map.Entry.comparingByKey()).map(Map.Entry::getKey).toList();

        try(PrintWriter out = new PrintWriter(new FileWriter("src.csv"))){
            sortedNames.forEach(v -> {
                var a = nameMap.get(v);
                System.out.println(a);
                out.printf("\n");
                out.printf(v + ";" + a.getX() + ";" + a.getY() + ";" + a.getZ());
                }
            );
        }

        return input;
    }
}
