from tkinter import *
from tkinter import ttk

class MyApp:

    def __init__(self, root):
        root.title('Root window')
        self.fra = ttk.Frame(root)
        self.fra.pack()
        self.x = ttk.Label(self.fra, text="Label")
        self.x.pack()
        self.but = ttk.Button(root, text="Label", command=lambda: self.show("label"))
        self.but.pack()
        self.but = ttk.Button(root, text="Entry", command=lambda: self.show("Entry"))
        self.but.pack()
       
    def show(self, typ):
        self.x.destroy()
        if typ == "label":
            self.x = ttk.Label(self.fra, text="Label")
            self.x.pack()
        else:
            self.x = ttk.Entry(self.fra, text="Entry")
            self.x.pack()

root = Tk()
app = MyApp(root)
root.mainloop()

