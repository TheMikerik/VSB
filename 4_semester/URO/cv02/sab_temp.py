# -*- coding: utf-8 -*-

import tkinter as tk
from tkinter import font
from tkinter import *
import tkinter.font

class myApp:

    def prevod(self, event=None):
            v = float(self.ent_in.get())
            print(self.dir.get())
            self.ent_out.delete(0, END)
            self.ent_out.insert(0, str(round(v, 2)))

    def __init__(self, root):
        root.title('Převodník teplot')
        root.resizable(False, False)
        root.bind('<Return>', self.prevod) 

        def_font = tkinter.font.nametofont("TkDefaultFont")
        def_font.config(size=16)

        self.left_frame = tk.Frame(root)
        self.right_frame = tk.Frame(root)
        self.direction_frame = tk.Frame(self.left_frame)
        self.entries_frame = tk.Frame(self.left_frame)

        self.dir = IntVar()
        self.dir.set(1) 

        self.ent_frame = Frame(self.left_frame)
        self.lbl_in = Label(self.ent_frame, text="Vstup")
        self.ent_in = Entry(self.ent_frame, width=10, font=def_font)
        self.ent_in.insert(0, '0')

        self.direction_label = tk.Label(self.direction_frame, text="Conversion Direction")
        self.check_frame = tk.Frame(self.direction_frame)
        self.check_1 = tk.Checkbutton(self.check_frame, text="Celsius to Fahrenheit", variable=self.direction_var, onvalue=1, offvalue=2)
        self.check_2 = tk.Checkbutton(self.check_frame, text="Fahrenheit to Celsius", variable=self.direction_var, onvalue=2, offvalue=1)

        self.info_label = tk.Label(root, text="Jan Piperek, PIP0016", fg="yellow", bg="black", font=("Times New Roman", 16))

        self.ca = Canvas(self.right_frame, width=400, height=400)
        self.photo = tk.PhotoImage(file="th_empty.png")
        self.ca.create_image(150, 200, image=self.photo)
        self.rectangle = self.canvas.create_rectangle(146, 292, 152, 80, fill="yellow")

        self.direction_frame.pack(side="top")
        self.left_frame.pack(side="left", fill=tk.Y)
        self.right_frame.pack(side="right", fill=tk.BOTH, expand=True)
        self.entries_frame.pack(side="bottom")
        
        self.check_frame.pack()
        self.direction_label.pack()
        self.check_1.pack(side=tk.LEFT)
        self.check_2.pack(side=tk.LEFT)
        
        self.ent_frame.pack()
        self.lbl_in.pack()
        self.ent_in.pack()
        
        self.left_frame.pack(side="left", fill=Y)
        self.right_frame.pack(side="right")
        self.ent_frame.pack()
        self.lbl_in.pack()  
        self.ent_in.pack()
        
        self.canvas.pack()
        
        self.ent_in.focus_force()

root = Tk()
app = myApp(root)
root.mainloop()