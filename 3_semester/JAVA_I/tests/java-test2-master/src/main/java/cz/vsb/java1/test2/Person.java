package cz.vsb.java1.test2;

import cz.vsb.java1.test2.helpers.RandomGenarator;

import java.util.Objects;

public class Person {

    private String firstName;
    private String lastName;
    private int age;

    public static Person generate() {
        return new Person(
                RandomGenarator.selectRandom(RandomGenarator.NAMES),
                RandomGenarator.selectRandom(RandomGenarator.SURNAMES),
                RandomGenarator.random.nextInt(1, 120)
        );
    }

    public Person() {
    }

    public Person(String firstName, String lastName, int age) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }



    public String nicerText() {
        return String.format("%s %s (%3d)", firstName, lastName, age);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return age == person.age && Objects.equals(firstName, person.firstName) && Objects.equals(lastName, person.lastName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName, age);
    }


}
