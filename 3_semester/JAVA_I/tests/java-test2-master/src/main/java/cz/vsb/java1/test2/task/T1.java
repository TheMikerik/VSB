package cz.vsb.java1.test2.task;

import cz.vsb.java1.test2.Vector3D;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class T1 {

    public static boolean positive(Vector3D inp){
        return inp.getX() > 0 && inp.getY() > 0 && inp.getZ() > 0;
    }

    public List<Vector3D> run(){
        var retVal = Stream.generate(Vector3D::generate).filter(T1::positive).limit(10).collect(Collectors.toList());
        for (var v : retVal){
            System.out.println(v);
        }
        return retVal;
    }
}
