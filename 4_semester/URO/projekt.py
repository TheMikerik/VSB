import tkinter as tk
from tkinter import messagebox, filedialog

class FlashcardApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Flashcard App")
        
        # Flashcards
        self.flashcards = []
        self.current_flashcard_index = 0
        
        # Frame to hold flashcard
        self.flashcard_frame = tk.Frame(self.root)
        self.flashcard_frame.pack(pady=10)
        
        # Flashcard label
        self.flashcard_text = tk.StringVar()
        self.flashcard_label = tk.Label(self.flashcard_frame, textvariable=self.flashcard_text, font=("Helvetica", 18))
        self.flashcard_label.pack()
        
        # Frame to hold buttons
        self.button_frame = tk.Frame(self.root)
        self.button_frame.pack(pady=10)
        
        # Buttons
        self.show_answer_button = tk.Button(self.button_frame, text="Show Answer", command=self.show_answer)
        self.show_answer_button.grid(row=0, column=0, padx=10)
        
        self.next_card_button = tk.Button(self.button_frame, text="Next Card", command=self.next_card)
        self.next_card_button.grid(row=0, column=1, padx=10)
        
        self.add_card_button = tk.Button(self.button_frame, text="Add Card", command=self.add_card)
        self.add_card_button.grid(row=0, column=2, padx=10)
        
        self.edit_card_button = tk.Button(self.button_frame, text="Edit Card", command=self.edit_card)
        self.edit_card_button.grid(row=0, column=3, padx=10)
        
        self.save_button = tk.Button(self.button_frame, text="Save Cards", command=self.save_cards)
        self.save_button.grid(row=0, column=4, padx=10)
        
        self.load_button = tk.Button(self.button_frame, text="Load Cards", command=self.load_cards)
        self.load_button.grid(row=0, column=5, padx=10)
        
        # Initialize flashcards
        self.load_cards()
        self.show_flashcard()

    def show_flashcard(self):
        # Display the current flashcard
        if self.flashcards:
            self.flashcard_text.set(self.flashcards[self.current_flashcard_index])
        else:
            self.flashcard_text.set("No flashcards available")

    def show_answer(self):
        # Function to show the answer of the flashcard
        if self.flashcards:
            messagebox.showinfo("Answer", self.flashcards[self.current_flashcard_index])
        else:
            messagebox.showinfo("No Flashcard", "No flashcards available")

    def next_card(self):
        # Function to load the next flashcard
        if self.flashcards:
            self.current_flashcard_index = (self.current_flashcard_index + 1) % len(self.flashcards)
            self.show_flashcard()

    def add_card(self):
    # Function to add a new flashcard
        new_flashcard = simpledialog.askstring("Add Flashcard", "Enter the new flashcard:")
        if new_flashcard:
            self.flashcards.append(new_flashcard)
            self.show_flashcard()

    def edit_card(self):
        # Function to edit the current flashcard
        if self.flashcards:
            edited_flashcard = simpledialog.askstring("Edit Flashcard", "Edit the flashcard:", initialvalue=self.flashcards[self.current_flashcard_index])
            if edited_flashcard:
                self.flashcards[self.current_flashcard_index] = edited_flashcard
                self.show_flashcard()
                
    def save_cards(self):
        # Function to save flashcards to a file
        filename = filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[("Text files", "*.txt")])
        if filename:
            with open(filename, "w") as f:
                for flashcard in self.flashcards:
                    f.write(flashcard + "\n")
            messagebox.showinfo("Save Successful", "Flashcards saved successfully")

    def load_cards(self):
        # Function to load flashcards from a file
        filename = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
        if filename:
            with open(filename, "r") as f:
                self.flashcards = f.read().splitlines()
            self.current_flashcard_index = 0
            self.show_flashcard()
            messagebox.showinfo("Load Successful", "Flashcards loaded successfully")

if __name__ == "__main__":
    root = tk.Tk()
    app = FlashcardApp(root)
    root.mainloop()
