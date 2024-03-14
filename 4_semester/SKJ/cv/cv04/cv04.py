class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def greet(self):
        print(f'hello {self.name}')


p = Person('Filip', 20)
p.greet()

class Student(Person):
    def __init__(self, name, age, id):
        super().__init__(name, age)
        self.id = id