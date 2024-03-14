from tkinter import *
import tkinter.font



class myApp:

    
    def prevod(self, event=None):
        v = float(self.ent_in.get())
        if self.dir.get() == 1:
            output = (v * 1.8) + 32
        else:
            output = (v - 32) * 5/9
        self.ent_out.delete(0, END)
        self.ent_out.insert(0, str(round(output, 2)))


    def __init__(self, root):
        root.title('Převodník teplot')
        root.resizable(TRUE, TRUE)
        root.bind('<Return>', self.prevod)

        def_font = tkinter.font.nametofont("TkDefaultFont")
        def_font.config(size=30)

        self.left_frame = Frame(root)
        self.right_frame = Frame(root)
        self.left_section_frame = Frame(self.left_frame)
        
        self.dir = IntVar()
        self.dir.set(1)
        
        self.ent_frame = Frame(self.left_section_frame)
        self.lbl_in = Label(self.ent_frame, text="Vstup")
        self.ent_in = Entry(self.ent_frame, width=10, font=def_font)
        self.ent_in.insert(0, '0')
        
        
        self.output_frame = Frame(self.left_section_frame)
        self.lbl2_in = Label(self.output_frame, text = "Vystup")
        self.ent_out = Entry(self.output_frame, width=10, font=def_font)
        self.ent_out.insert(0, '0')
        
        self.title = Label(self.left_frame, text="Vyber převodník")
        
        self.options = Frame(self.left_frame)
        self.option1 = Checkbutton(self.options, text=" Celsius na Fahrenheit", variable=self.dir, onvalue=1, offvalue=2)
        self.option2 = Checkbutton(self.options, text=" Fahrenheit na Celsius", variable=self.dir, onvalue=2, offvalue=1)
        
        
        login = Label(root, text="Michal Ručka, RUC0066", fg="white", bg="black", font=("Helvetica", 20))
        login.pack(side=BOTTOM, fill=X)
        

        self.ca = Canvas(self.right_frame, width=400, height=400)
        self.photo = PhotoImage(file="th.png")
        self.ca.create_image(150, 200, image=self.photo)

        self.left_frame.pack(side="left", fill=Y)
        self.right_frame.pack(side="right")
        self.left_section_frame.pack(side="bottom")
        
        self.title.pack()
        self.options.pack()
        self.option1.pack(side=LEFT)
        self.option2.pack(side=LEFT)
        
        self.ent_frame.pack()
        self.lbl_in.pack()
        self.ent_in.pack()
        self.output_frame.pack()
        self.lbl2_in.pack()
        self.ent_out.pack()
        self.ca.pack()
        
        self.ent_in.focus_force()

root = Tk()
app = myApp(root)
root.mainloop()