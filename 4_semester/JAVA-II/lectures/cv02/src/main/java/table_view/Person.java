package table_view;

import javafx.beans.property.SimpleStringProperty;

public class Person {

	private final Long id;
    private final SimpleStringProperty firstName;
    private final SimpleStringProperty lastName;
    private final SimpleStringProperty email;

    Person(String fName, String lName, String email) {
    	this(null, fName, lName, email);
    }
    
    Person(Long id, String fName, String lName, String email) {
    	this.id = id;
        this.firstName = new SimpleStringProperty(fName);
        this.lastName = new SimpleStringProperty(lName);
        this.email = new SimpleStringProperty(email);
    }
    
    Person(Long id, Person p) {
    	this(id, p.getFirstName(), p.getLastName(), p.getEmail());
    }

    public String getFirstName() {
        return firstName.get();
    }

    public void setFirstName(String fName) {
        firstName.set(fName);
    }

    public String getLastName() {
        return lastName.get();
    }

    public void setLastName(String fName) {
        lastName.set(fName);
    }

    public String getEmail() {
        return email.get();
    }

    public void setEmail(String fName) {
        email.set(fName);
    }

	public Long getId() {
		return id;
	}
    
}