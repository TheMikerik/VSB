# -*- coding: utf-8 -*-

from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
from tkinter import colorchooser
from tkinter import ttk


class MyApp:

    def test_messagebox(self):
        end = messagebox.showinfo("Uživatelská rozhraní", "©2024 URO \nUkázka použití komponenty messagebox.")
        if end: 
            print(end)

    def test_filedialog(self):
        soubor = filedialog.askopenfile(parent=None, title='Choose your file', filetypes=[('all files', '.*'), ('gif files', '*.gif')])
        if soubor:
            print(soubor.name)

    def test_colorchooser(self):
        barva = colorchooser.askcolor(parent=None, title="Color", initialcolor="#000000")
        if barva:
            print("Vybrána barva:", barva)
        else:
            print("Barva nevybrána.")

    def __init__(self, root):
        root.title('Root window')
        self.fra = ttk.Frame(root)
        self.fra.pack()
        self.x = ttk.Label(self.fra, text="Label")
        self.x.pack()
        self.but1 = ttk.Button(root, text="messagebox", command=self.test_messagebox)
        self.but1.pack()
        self.but2 = ttk.Button(root, text="filedialog", command=self.test_filedialog)
        self.but2.pack()
        self.but3 = ttk.Button(root, text="colorchooser", command=self.test_colorchooser)
        self.but3.pack()


root = Tk()
app = MyApp(root)
root.mainloop()

