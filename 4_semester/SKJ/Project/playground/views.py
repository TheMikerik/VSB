import random
from django.http import JsonResponse
from django.shortcuts import get_object_or_404, redirect, render
from django.urls import reverse

from playground.forms import CardForm, CuserForm, DeckForm, TagForm, UserSelectForm

from .models import Card, Cuser, Deck, Comment, Review

def home(request):
    return render(request, 'home.html')




def deck_list(request):
    decks = Deck.objects.all()
    return render(request, 'decks/deck_list.html', {'decks': decks})

def deck_add(request):
    if request.method == 'POST':
        form = DeckForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('deck_list')
    else:
        form = DeckForm()
    return render(request, 'decks/deck_add.html', {'form': form})

def deck_edit(request, deck_id):
    deck = get_object_or_404(Deck, id=deck_id)
    if request.method == 'POST':
        form = DeckForm(request.POST, instance=deck)
        if form.is_valid():
            form.save()
            return redirect('deck_list')
    else:
        form = DeckForm(instance=deck)
    return render(request, 'decks/deck_edit.html', {'form': form})

def deck_delete(request, deck_id):
    deck = get_object_or_404(Deck, id=deck_id)
    if request.method == 'POST':
        deck.delete()
        return redirect('deck_list')
    else:
        pass




def card_list(request, deck_id):
    deck = get_object_or_404(Deck, id=deck_id)
    cards = deck.card_set.all()
    return render(request, 'cards/card_list.html', {'deck': deck, 'cards': cards})

def card_edit(request, card_id):
    card = get_object_or_404(Card, id=card_id)
    if request.method == 'POST':
        form = CardForm(request.POST, instance=card)
        if form.is_valid():
            form.save()
            return redirect('card_list', deck_id=card.deck.id)
    else:
        form = CardForm(instance=card)
    return render(request, 'cards/card_edit.html', {'form': form})

def card_delete(request, card_id):
    card = get_object_or_404(Card, id=card_id)
    if request.method == 'POST':
        card.delete()
        return redirect('card_list', deck_id=card.deck.id)
    else:
        pass
    
def card_add(request, deck_id):
    deck = get_object_or_404(Deck, id=deck_id)
    if request.method == 'POST':
        form = CardForm(request.POST)
        if form.is_valid():
            card = form.save(commit=False)
            card.deck = deck
            card.save()
            return redirect('card_list', deck_id=deck_id)
    else:
        form = CardForm()
    return render(request, 'cards/card_add.html', {'form': form})




def comment_list(request, deck_id):
    deck = get_object_or_404(Deck, pk=deck_id)
    comments = deck.comment_set.all()
    return render(request, 'comments/comment_list.html', {'deck': deck, 'comments': comments})

def add_comment(request, deck_id):
    deck = get_object_or_404(Deck, pk=deck_id)
    if request.method == 'POST':
        nicname = request.POST.get('nicname')
        comment_text = request.POST.get('comment')
        if nicname and comment_text:
            Comment.objects.create(nicname=nicname, deck=deck, text=comment_text)
    return redirect(reverse('comment_list', args=[deck_id]))




def user_list(request):
    users = Cuser.objects.all()
    user_data = []

    for user in users:
        num_decks = Deck.objects.filter(user=user).count()
        num_comments = Comment.objects.filter(deck__user=user).count()

        user_data.append({
            'user': user,
            'num_decks': num_decks,
            'num_comments': num_comments,
        })

    return render(request, 'users/user_list.html', {'user_data': user_data})

def user_edit(request, user_id):
    user = get_object_or_404(Cuser, pk=user_id)
    if request.method == 'POST':
        form = CuserForm(request.POST, instance=user)
        if form.is_valid():
            form.save()
            return redirect(reverse('user_list'))
    else:
        form = CuserForm(instance=user)
    return render(request, 'users/user_edit.html', {'form': form, 'user': user})

def user_add(request):
    if request.method == 'POST':
        form = CuserForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('user_list')
    else:
        form = CuserForm()
    return render(request, 'users/user_add.html', {'form': form})

def user_delete(request, user_id):
    user = get_object_or_404(Cuser, pk=user_id)
    if request.method == 'POST':
        user.delete()
        return redirect('user_list')
    else:
        pass




def user_select(request, deck_id):
    deck = get_object_or_404(Deck, id=deck_id)
    
    if request.method == 'POST':
        form = UserSelectForm(request.POST)
        if form.is_valid():
            user = form.cleaned_data['user']
            Review.objects.create(user=user, deck=deck)
            return redirect('practice', deck_id=deck.id)
    else:
        form = UserSelectForm()
    
    return render(request, 'users/user_select.html', {'form': form, 'deck': deck})

def practice(request, deck_id):
    deck = get_object_or_404(Deck, id=deck_id)
    cards = list(deck.card_set.all())
    card = random.choice(cards) if cards else None
    return render(request, 'practice.html', {'deck': deck, 'card': card})

def review_list(request):
    reviews = Review.objects.select_related('user', 'deck').all()
    return render(request, 'reviews.html', {'reviews': reviews})

def add_tag(request):
    if request.method == 'POST':
        form = TagForm(request.POST)
        if form.is_valid():
            tag = form.save()
            return JsonResponse({'success': True, 'tag_id': tag.id, 'tag_name': tag.name})
    else:
        form = TagForm()
    return render(request, 'add_tag.html', {'form': form})