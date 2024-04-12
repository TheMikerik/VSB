from tkinter import *
from tkinter import ttk

class MyApp:
    def hello(self):
        print("Hello")

    def __init__(self, master):
        self.bu = Button(master, text="Quit", command=master.destroy)
        self.bu.pack()

root = Tk()
app = MyApp(root)
root.title("Hello Worls")
root.mainloop()




#--------- 1

# top = Tk() # vytvoří prázdné okno a přiřadí do proměnné top
# b = Button(top, text="Konec", command=top.quit) # vytvoří tlačítko v rámci okna top, s textem Konec a s příkazem pro
# # ukončení po kliknutí na toto tlačítko - v tuto chvíli se ale ještě nevykreslí, pouze se uloží do proměnné b
# b2 = Button(top, text="Konec2", command=top.quit)
# b3 = Button(top, text="Konec3", command=top.quit)
# b4 = Button(top, text="Konec4", command=top.quit)


# top.title("Button 1") # nastaví název okna


# b.pack(side="bottom") # vykreslí tlačítko do okna
# b2.pack(side="bottom")
# b3.pack(side="left")
# b4.pack(side="right")

# top.mainloop() # smyčka pro nekonečné vykreslování okna


