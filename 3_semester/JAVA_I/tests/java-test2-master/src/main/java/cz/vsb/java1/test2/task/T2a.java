package cz.vsb.java1.test2.task;

import cz.vsb.java1.test2.Vector3D;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class T2a {

    public List<Vector3D> run(List<Vector3D> input){
        List<Vector3D> output = input.stream().sorted(Comparator.comparingDouble(Vector3D::getLength)).collect(Collectors.toList());
        for(Vector3D v : output){
            System.out.println(v.getLength());
        }
        return output;
    }
}
