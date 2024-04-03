package cz.vsb.fei.java2.lab05.entities;

import java.util.List;

import lombok.ToString;

public class Course {

    private Long id;

    @ToString.Exclude
    private List<Student> students;

    private String code;

    private String name;

    public String toStringWithStudents() {
	return "Course [id=" + id + ", code=" + code + ", name=" + name + ", students=" + students + "]";
    }
}
