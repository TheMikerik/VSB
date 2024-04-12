import tkinter as tk
from tkinter import ttk
from tkinter import messagebox

class FlashcardApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Flashcard App")

        self.data = [
            ("English", "Inquisitive", "Zvedavy", "Learned"),
            ("English", "Diminishing", "Zmensujici se", "Studied"),
            ("English", "Skidding", "Smyk", "Unlearned"),
            ("History", "Industrial Revolution", "Průmyslová revoluce", "Studied"),
            ("Mathematics", "Pythagorean theorem", "Pythagorova věta", "Studied"),
            ("Biology", "Mitochondria", "Mitochondrie", "Learned"),
            ("Geography", "Plate tectonics", "Tektonické desky", "Unlearned"),
            ("Literature", "Shakespeare", "Shakespear", "Studied"),
            ("Chemistry", "Periodic table", "Periodická tabulka", "Studied"),
            ("Physics", "Newton's laws", "Newtonovy zákony", "Learned"),
            ("Art", "Renaissance", "Renesance", "Unlearned"),
            ("Economics", "Supply and demand", "Poptávka a nabídka", "Studied"),
            ("Music", "Mozart", "Mozart", "Studied"),
            ("Psychology", "Pavlov's dog experiment", "Pavlovův experiment na psech", "Learned"),
            ("Sociology", "Social stratification", "Sociální stratifikace", "Unlearned"),
            ("Computer Science", "Algorithm", "Algoritmus", "Studied"),
            ("Political Science", "Democracy", "Demokracie", "Studied"),
            ("Engineering", "Mechanical Engineering", "Strojní inženýrství", "Learned"),
            ("Philosophy", "Socrates", "Sokrates", "Unlearned"),
            ("Languages", "French", "Francouzština", "Studied"),
            ("Medicine", "Vaccination", "Očkování", "Studied"),
            ("Architecture", "Gothic architecture", "Gotická architektura", "Learned"),
            ("Business", "Entrepreneurship", "Podnikání", "Unlearned")
        ]

        self.create_menu()
        self.create_treeview()
        self.create_entries()
        self.create_buttons()

        self.tree.bind('<<TreeviewSelect>>', self.on_tree_select)

    def create_menu(self):
        menu_bar = tk.Menu(self.root)
        file_menu = tk.Menu(menu_bar, tearoff=0)
        file_menu.add_command(label="Load")
        file_menu.add_command(label="Delete all", command=self.delete_all)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.root.quit)
        menu_bar.add_cascade(label="File", menu=file_menu)

        tools_menu = tk.Menu(menu_bar, tearoff=0)
        tools_menu.add_command(label="Extract")
        tools_menu.add_command(label="Copy")
        tools_menu.add_command(label="Paste")
        menu_bar.add_cascade(label="Adjust", menu=tools_menu)

        help_menu = tk.Menu(menu_bar, tearoff=0)
        help_menu.add_command(label="About", command=lambda: messagebox.showinfo("About", "Michal Ručka, RUC0066\nURO Tkinter Projekt\nFlashcards aplikace"))
        menu_bar.add_cascade(label="Help", menu=help_menu)

        self.root.config(menu=menu_bar)

    def delete_all(self):
        response = messagebox.askyesno("Confirm Deletion", "Are you sure you want to delete all flashcards?")
        if response:
            for item in self.tree.get_children():
                self.tree.delete(item)

    def create_treeview(self):
        self.tree = ttk.Treeview(self.root, columns=('deck_name', 'front_side', 'back_side', 'status'), show='headings')
        self.tree.heading('deck_name', text='Deck name')
        self.tree.heading('front_side', text='Front side')
        self.tree.heading('back_side', text='Back side')
        self.tree.heading('status', text='Status')

        for item in self.data:
            self.tree.insert('', tk.END, values=item, tags=(item[3],))

        self.tree.grid(row=0, column=0, columnspan=3, sticky='nsew')

        scrollbar = ttk.Scrollbar(self.root, orient=tk.VERTICAL, command=self.tree.yview)
        self.tree.configure(yscroll=scrollbar.set)
        scrollbar.grid(row=0, column=3, sticky='ns')

        self.tree.tag_configure('Learned', background='#005500')
        self.tree.tag_configure('Studied', background='#555500')
        self.tree.tag_configure('Unlearned', background='#550000')


    def create_entries(self):
        self.entries = []
        labels = ["Deck:", "Front side:", "Back side:", "Status:"]
        for i, label_text in enumerate(labels):
            ttk.Label(self.root, text=label_text).grid(row=i+1, column=0, sticky='w', padx=5)
            entry = ttk.Entry(self.root)
            entry.grid(row=i+1, column=1, sticky='we', padx=5)
            entry.insert(tk.END, "")
            self.entries.append(entry)

    def create_buttons(self):
        num_entries = len(self.entries)
        row = num_entries + 1

        ttk.Button(self.root, text='Delete', command=self.create_delete_dialog).grid(row=row, column=0, pady=4, padx=5, sticky='ew')
        ttk.Button(self.root, text='Save Changes', command=self.save_changes).grid(row=row, column=1, pady=4, padx=5, sticky='ew')
        ttk.Button(self.root, text='Highlight', command=self.highlight_flashcard).grid(row=row, column=2, pady=4, padx=5, sticky='ew')
        ttk.Button(self.root, text='Practise', command=self.practise).grid(row=row+1, column=0, columnspan=3, pady=4, padx=5, sticky='ew')
        ttk.Button(self.root, text='Add Flashcard', command=self.create_add_flashcard_section).grid(row=row+2, column=1, pady=4, padx=5, sticky='ew')

    def practise(self):
        self.practise_window = tk.Toplevel(self.root)
        self.practise_window.title("Practice Flashcards")

        self.current_flashcard_index = 0

        self.practise_window.grid_columnconfigure(0, weight=1)
        self.practise_window.grid_rowconfigure(0, weight=1)
        self.practise_window.grid_rowconfigure(1, weight=1)
        self.practise_window.configure(padx=20, pady=20)

        self.display_flashcard()

    def display_flashcard(self):
        for widget in self.practise_window.winfo_children():
            widget.destroy()

        flashcard_data = self.data[self.current_flashcard_index]

        front_label = ttk.Label(self.practise_window, text=flashcard_data[1], font=("Arial", 14))
        back_label = ttk.Label(self.practise_window, text=flashcard_data[2], font=("Arial", 14))

        front_label.grid(row=0, column=0, padx=10, pady=(0, 10))
        back_label.grid(row=0, column=1, padx=10, pady=(0, 10))
        back_label.grid_remove()

        prev_button = ttk.Button(self.practise_window, text="Previous", command=self.show_previous_flashcard)
        show_button = ttk.Button(self.practise_window, text="Show", command=lambda: self.toggle_back_side(back_label, show_button))
        next_button = ttk.Button(self.practise_window, text="Next", command=self.show_next_flashcard)

        prev_button.grid(row=2, column=0, pady=0)
        next_button.grid(row=2, column=1, pady=0)
        show_button.grid(row=3, column=0, columnspan=2, pady=0)

    def toggle_back_side(self, back_label, show_button):
        if back_label.winfo_viewable():
            back_label.grid_remove()
            show_button.config(text="Show")
        else:
            back_label.grid()
            show_button.config(text="Hide")

    def show_previous_flashcard(self):
        self.current_flashcard_index = (self.current_flashcard_index - 1) % len(self.data)
        self.display_flashcard()

    def show_next_flashcard(self):
        self.current_flashcard_index = (self.current_flashcard_index + 1) % len(self.data)
        self.display_flashcard()

    def create_delete_dialog(self):
        response = messagebox.askyesno("Confirm Deletion", "Are you sure you want to delete this flashcard?")
        if response:
            selected_item = self.tree.selection()[0]
            self.tree.delete(selected_item)
    
    def highlight_flashcard(self):
        selected_item = self.tree.selection()[0]
        tags = self.tree.item(selected_item, 'tags')
        
        if 'highlighted' in tags:
            self.tree.item(selected_item, tags=())
        else:
            self.tree.item(selected_item, tags=('highlighted',))
        self.tree.tag_configure('highlighted', background='red', foreground='white')

    def create_add_flashcard_section(self):
        add_flashcard_frame = ttk.Frame(self.root)
        add_flashcard_frame.grid(row=len(self.entries) + 3, column=0, columnspan=3, padx=5, pady=5, sticky='we')

        ttk.Label(add_flashcard_frame, text="Category:").grid(row=0, column=0, sticky='w', padx=5)
        self.category_entry = ttk.Entry(add_flashcard_frame)
        self.category_entry.grid(row=0, column=1, sticky='we', padx=5)

        ttk.Label(add_flashcard_frame, text="Front side:").grid(row=1, column=0, sticky='w', padx=5)
        self.front_entry = ttk.Entry(add_flashcard_frame)
        self.front_entry.grid(row=1, column=1, sticky='we', padx=5)

        ttk.Label(add_flashcard_frame, text="Back side:").grid(row=2, column=0, sticky='w', padx=5)
        self.back_entry = ttk.Entry(add_flashcard_frame)
        self.back_entry.grid(row=2, column=1, sticky='we', padx=5)

        ttk.Button(add_flashcard_frame, text='Add Flashcard', command=self.add_flashcard).grid(row=3, columnspan=2, pady=5, padx=50)

    def add_flashcard(self):
        category = self.category_entry.get()
        front_side = self.front_entry.get()
        back_side = self.back_entry.get()
        status = "Unlearned"

        self.tree.insert('', tk.END, values=(category, front_side, back_side, status))

    def on_tree_select(self, event):
        selected_item = self.tree.selection()[0]
        values = self.tree.item(selected_item, 'values')

        for entry, value in zip(self.entries, values):
            entry.delete(0, tk.END)
            entry.insert(tk.END, value)

    def save_changes(self):
        selected_item = self.tree.selection()[0]
        values = [entry.get() for entry in self.entries]
        self.tree.item(selected_item, values=values)

def main():
    root = tk.Tk()
    app = FlashcardApp(root)
    root.mainloop()

if __name__ == "__main__":
    main()