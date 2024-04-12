# -*- coding: utf-8 -*-

from tkinter import *
from tkinter import ttk


class MyApp:

    def __init__(self, root):
        root.title('Root window')
        self.fra = ttk.Frame(root)
        self.fra.pack()
        self.x = ttk.Label(self.fra, text="Label")
        self.x.pack()
        self.but1 = ttk.Button(root, text="messagebox", command=root.quit)
        self.but1.pack()
        self.but2 = ttk.Button(root, text="filedialog", command=root.quit)
        self.but2.pack()
        self.but3 = ttk.Button(root, text="colorchooser", command=root.quit)
        self.but3.pack()
   
root = Tk()
#root.attributes("-alpha", 0.5) 
root.iconbitmap('book.ico')
style = ttk.Style()
style.configure('TButton', background='blue', foreground='red', font=('Helvetica', 12))
#style.theme_use('alt')
#root.tk.call('source', 'blue/blue.tcl')
#style.theme_use('blue')
app = MyApp(root)
root.mainloop()

