# C++
## C++ Notes

### 1st class
- You dont have to write return in main, cause its called automatically
- NULL vs nullptr
    - null is not type safe
    - nullptr can be casted to different pointers, but not to numbers
- Struct vs class
    - Structure is implicitly public
    - Class is implicitly private
    - Structure is used when everything should be public and it contains only a few methods
    - Class is used for OOP, inheritance, ...
    - Overall its the same
- & vs &&
    - & l-value
        - can be located on the left side of the = oparator
        - it is not destroyed after usage
    - && r-value
        - can be only on the right side of the = operator
        - it is destroyed after usage (for example temp objects - objects without name)
- pointer vs reference
    - reference cannot be null, it has to point to valid object, otherwise its "unwanted behaviour"
- friend
    - can be assigned to method to access private data
- namespace
    - different libraries can have methods with the same name, thats why the namespace is used - it differs those methods
    - but its not good to import the whole namespace in the code, cause it can cast errors
    - better is to import them only in each method or to import just some parts from the library
        - ``using std::cout``
- typedef
    - Can wrap casual types with wanted label
    - ``typedef int AircraftId`` or ``using AircraftId = int`` (using is more C++like so use it)
    - It works just like the normal int, but its labeled as ``AircraftId``
- static_cast
    - Compiler checks if the cast is possible. If it is, it will cast it

### 2nd class
- Union
    - There are exactly two values and this object can aquire value only one of them
- Classes inherity
    - ``class B : public A ``
    - Pulbic: Everyone knows that B inherited from A & class B can be casted to class A
    - Protected: Only inherited classes knows, that the "parent" is class A
    - Private: Only the exact class knows what it inherited from & class B cannot be casted to class A
- RAII
    - Lifetime of each object
    - Calls destructor on every end of the scope
    - In comparision with garbage collector, we exaclty know when the object is created and when it is destroyed
