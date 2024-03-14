# -*- coding: utf-8 -*- 
import tkinter as tk
from tkinter import ttk

root = tk.Tk()
hlavniMenu = tk.Menu(root)

# vytvořit rozbalovací menu a přidat ho k hlavnímu menu
menuSoubor = tk.Menu(hlavniMenu, tearoff=0)
menuSoubor.add_command(label="Otevřít")
menuSoubor.add_command(label="Uložit")
menuSoubor.add_separator()
menuSoubor.add_command(label="Pryč", command=root.quit)
hlavniMenu.add_cascade(label="Soubor", menu=menuSoubor)

# další rozbalovací menu
menuUpravy = tk.Menu(hlavniMenu, tearoff=0)
menuUpravy.add_command(label="Vyjmout")
menuUpravy.add_command(label="Kopírovat")
menuUpravy.add_command(label="Vložit")
hlavniMenu.add_cascade(label="Upravit", menu=menuUpravy)

menuNapoveda = tk.Menu(hlavniMenu, tearoff=0)
menuNapoveda.add_command(label="O aplikaci")
hlavniMenu.add_cascade(label="Nápověda", menu=menuNapoveda)

# zobrazení menu
root.config(menu=hlavniMenu)

# TreeView
tree = ttk.Treeview(root, columns=('book_name', 'author', 'year_published'), 
                    show='headings')

tree.heading('book_name', text='Kniha')
tree.heading('author', text='Autor')
tree.heading('year_published', text='Publikovano')

tree.insert('', tk.END, values=("Atomic Habits", "J. Clear", "2011"))
tree.insert('', tk.END, values=("Jane", "Doe", "901121/7238"))

tree.grid(row=0, column=0, columnspan=2, sticky='nsew')

scrollbar = ttk.Scrollbar(root, orient=tk.VERTICAL, command=tree.yview)
tree.configure(yscroll=scrollbar.set)
scrollbar.grid(row=0, column=3, sticky='ns')

entries = []
# Kniha LABEL
ttk.Label(root, text="Kniha: ").grid(row=1, column=0, sticky='w')
entry = ttk.Entry(root)
entry.grid(row=1, column=1)
entries.append(entry)

# Autor LABEL
ttk.Label(root, text="Autor: ").grid(row=2, column=0, sticky='w')
entry = ttk.Entry(root)
entry.grid(row=2, column=1)
entries.append(entry)

# Publikovano LABEL
ttk.Label(root, text="Publikovano: ").grid(row=3, column=0, sticky='w')
entry = ttk.Entry(root)
entry.grid(row=3, column=1)
entries.append(entry)

def on_tree_select(event):
    # Get selected item
    selected_item = tree.selection()[0]
    values = tree.item(selected_item, 'values')

    # Update input fields
    for i in range(len(values)):
        entries[i].delete(0, tk.END)
        entries[i].insert(tk.END, values[i])

def save_changes():
    # Get selected item
    selected_item = tree.selection()[0]

    # Get input field values
    values = [entry.get() for entry in entries]

    # Update selected item
    tree.item(selected_item, values=values)

# Bind select event
tree.bind('<<TreeviewSelect>>', on_tree_select)

ttk.Button(root, text='Save Changes', command=save_changes).grid(row=4, column=0, columnspan=2)

# pages
notebook = ttk.Notebook(root)


root.mainloop()