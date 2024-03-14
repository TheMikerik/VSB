import tkinter as tk
from tkinter import ttk

class FlashcardApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Flashcard App")

        self.create_menu()
        self.create_treeview()
        self.create_entries()
        self.create_save_button()

        self.tree.bind('<<TreeviewSelect>>', self.on_tree_select)

    def create_menu(self):
        menu_bar = tk.Menu(self.root)
        file_menu = tk.Menu(menu_bar, tearoff=0)
        file_menu.add_command(label="Open")
        file_menu.add_command(label="Save")
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.root.quit)
        menu_bar.add_cascade(label="File", menu=file_menu)

        tools_menu = tk.Menu(menu_bar, tearoff=0)
        tools_menu.add_command(label="Extract")
        tools_menu.add_command(label="Copy")
        tools_menu.add_command(label="Paste")
        menu_bar.add_cascade(label="Adjust", menu=tools_menu)

        help_menu = tk.Menu(menu_bar, tearoff=0)
        help_menu.add_command(label="About")
        menu_bar.add_cascade(label="Help", menu=help_menu)

        self.root.config(menu=menu_bar)

    def create_treeview(self):
        self.tree = ttk.Treeview(self.root, columns=('deck_name', 'front_side', 'back_side', 'status'), show='headings')
        self.tree.heading('deck_name', text='Deck name')
        self.tree.heading('front_side', text='Front side')
        self.tree.heading('back_side', text='Back side')
        self.tree.heading('status', text='Status')

        data = [
            ("English", "Inquisitive", "Zvedavy", "Nauceno"),
            ("English", "Diminishing", "Zmensujici se", "Procviceno"),
            ("English", "Skidding", "Smyk", "Nenauceno"),
            ("IT", "Transakce v databazi", "Databázová transakce je skupina příkazů, které převedou databázi z jednoho konzistentního stavu do druhého.", "Nenauceno")
        ]

        for item in data:
            self.tree.insert('', tk.END, values=item)

        self.tree.grid(row=0, column=0, columnspan=2, sticky='nsew')

        scrollbar = ttk.Scrollbar(self.root, orient=tk.VERTICAL, command=self.tree.yview)
        self.tree.configure(yscroll=scrollbar.set)
        scrollbar.grid(row=0, column=2, sticky='ns')

    def create_entries(self):
        self.entries = []
        labels = ["Deck:", "Front side:", "Back side:", "Status:"]
        for i, label_text in enumerate(labels):
            ttk.Label(self.root, text=label_text).grid(row=i+1, column=0, sticky='w', padx=5)
            entry = ttk.Entry(self.root)
            entry.grid(row=i+1, column=1, sticky='we', padx=5)
            entry.insert(tk.END, "")
            self.entries.append(entry)

    def create_save_button(self):
        ttk.Button(self.root, text='Save Changes', command=self.save_changes).grid(row=6, column=0, columnspan=2, pady=5)

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
