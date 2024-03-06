# Lecture 1

# Polymorphism
class Animal:
    def __init__(self, name):
        self.name = name

class Dog:
    def __init__(self, name):
        self.name = name
    def make_sound(self):
        return f'Bark: {self.name}'

class Cat:
    def __init__(self, name):
        self.name = name
    def make_sound(self):
        return f'Mnau: {self.name}'
    
animals = [Dog('Azor'), Cat('Filemon'), Dog('Burek')]

for animal in animals:
    print(animal.make_sound(), type(animal))



class Document:
    no_of_documents = 0
    total_length = 0

    def __init__(self, content):
        self.content = content
        Document.no_of_documents += 1
        Document.total_length += len(self._content)

    @property
    def content(self):
        return self._content

    @staticmethod
    def average_length():
        return Document.total_length / Document.no_of_documents
    
    def __str__(self):
        return f'Document: {self.content[:10]}'
    
d1 = Document('abc')
print(Document.no_of_documents)

d2 = Document('Another one')
print(d1.no_of_documents)
print(d2.no_of_documents)

d1.content = 'xyz'
print(f'Average document lenght: {Document.average_length()}')