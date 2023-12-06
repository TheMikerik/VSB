package cz.vsb.java1.test2.task;

import cz.vsb.java1.test2.Vector3D;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class task1a {
    private static boolean filterPositives(Vector3D obj){
        return obj.getX() > 0 && obj.getY() > 0 && obj.getZ() > 0;
    }

    public List<Vector3D> run() {
        var retVal = Stream.generate(Vector3D::generate).filter(task1a::filterPositives).limit(10).collect(Collectors.toList());
        retVal.forEach(System.out::println);
        return retVal;
    }
}
