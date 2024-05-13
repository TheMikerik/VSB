from django.shortcuts import get_object_or_404, redirect, render

from playground.forms import DeckForm

from .models import Deck

def home(request):
    return render(request, 'home.html')

def deck_list(request):
    decks = Deck.objects.all()
    return render(request, 'decks/deck_list.html', {'decks': decks})

def deck_edit(request, deck_id):
    deck = get_object_or_404(Deck, pk=deck_id)
    return render(request, 'decks/deck_edit.html', {'deck': deck})

def deck_delete(request, deck_id):
    deck = get_object_or_404(Deck, pk=deck_id)
    if request.method == 'POST':
        deck.delete()
        return redirect('deck_list')
    return render(request, 'decks/deck_delete.html', {'deck': deck})

def deck_add(request):
    if request.method == 'POST':
        form = DeckForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('deck_list')
    else:
        form = DeckForm()
    return render(request, 'decks/deck_add.html', {'form': form})
