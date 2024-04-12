# -*- coding: utf-8 -*-
from tkinter import *
from tkinter import ttk

class MyApp:
    
    def new_win(self):
        # New instance Toplevel
        win = Toplevel()
        #win.grab_set()
        win.title('New window')
        new_label = Label(win, text="Quit!")
        new_label.pack()
        new_button = ttk.Button(win, text="Quit", command=win.quit)
        new_button.pack()

    def __init__(self, root):
        root.title('Root window')
        #Button
        new_button = ttk.Button(root, text="New window", command=self.new_win)
        new_button.pack()

root = Tk()
app = MyApp(root)
root.mainloop()

