package cz.vsb.java1.test2.task;

import cz.vsb.java1.test2.Vector3D;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class T1b {
    public static boolean positive(Vector3D inp){
        return inp.getX() > 0 && inp.getY() > 0 && inp.getZ() > 0;
    }

    public static boolean filterName(Vector3D inp){
        String name = inp.getName();
        return name.matches(".*-1.*");
    }

    public List<Vector3D> run(){
        var retVal = Stream.generate(Vector3D::generate).filter(T1b::positive).filter(T1b::filterName).limit(5).collect(Collectors.toList());
        for (var v : retVal){
            System.out.println(v);
        }
        return retVal;
    }
}
