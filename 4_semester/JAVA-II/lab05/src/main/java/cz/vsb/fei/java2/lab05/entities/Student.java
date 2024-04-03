package cz.vsb.fei.java2.lab05.entities;

public class Student {
    
    private Long id;
    
    private String firstName;

    private String lastName;
    
    private Course course;

    public String toStringNoCourse() {
	return "Student [id=" + id + ", firstName=" + firstName + ", lastName=" + lastName + "]";
    }
}
