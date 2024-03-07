# TAMZ
## CV2
- Homework
    - Birthday counter
        - Date, ion-datetime-button + modal ion-datetime, s2 = new Date("2024-02-29").toISOString()
        - Buttons
            - Name, date of birth, calculate
        - 3 states
            - "{name} has birthday in {XYZ} days and the day is {day (monday/tuesday, ...)}
            - {name} already has birthday this year and the next one is in {XYZ} days
            - Happy birthday {name}
        - How to get the number -> Number(new Date())
            - This way how to handle the date calculations is better, cause the the date is transfered to int number (such as 17091173782348). While comparing two dates, it can cause errors (so dont use "2024-01-15 < 2024-08-15")
        - State management
            - Choose one. Either numbers or dates. Dont mix it.
## CV3
- JSON
    - JavaScript Object Notation
    - https://www.json.org/json-en.html
- LocalStorage
    - localStorage.<name_of_variable> = <value>
    - ``localStorage.abc = 123``
    - ``localStorage["a.b.c"] = "abc"``
    - You can access it by ``localStorage``
        - ```Storage = $1
            a.b.c: "abc"
            abc: "123"
            length: 2
            Storage Prototype